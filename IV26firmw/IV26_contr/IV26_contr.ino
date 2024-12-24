/* Модуль управления лампой ИВ26
 *  
 *  © CYBEREX Tech, 2024
 * 
 */

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPUpdateServer.h>
#include <DNSServer.h>
#include <ESP8266mDNS.h>
#include <EEPROM.h>
#include <ESP8266SSDP.h>
#include <PubSubClient.h>
#include <Wire.h>
#include <TimeLib.h>
#include <pgmspace.h>
#include <ArduinoJson.h>
#include "const_js.h"

//NTP
#include <WiFiUdp.h>
unsigned int localPort = 2390;
const int NTP_PACKET_SIZE = 48;                     // NTP time stamp is in the first 48 bytes of the message
byte packetBuffer[NTP_PACKET_SIZE];                 // buffer to hold incoming and outgoing packets
IPAddress timeServerIP;                             // time.nist.gov NTP server address
WiFiUDP udp;
unsigned long epoch = 0;


#define A 14               // Пин подключения А
#define B 1                // Пин подключения Б
#define V 2                // Пин подключения В
#define G 3                // Пин подключения Г
#define D 4                // Пин подключения Д
#define E 5                // Пин подключения Е
#define J 12               // Пин подключения Ж
#define heat 13            // Накал лампы 


// WEBs
ESP8266WebServer server(80);
WiFiClient espClient;
PubSubClient client(espClient);
IPAddress apIP(10, 10, 20, 1);
IPAddress netMsk(255, 255, 255, 0);
ESP8266HTTPUpdateServer httpUpdater;

// DNS server
const byte             DNS_PORT = 53;
DNSServer              dnsServer;

// Текущий статус WLAN
unsigned int status = WL_IDLE_STATUS;

// Переменные для хранения статуса сетевого подключения
boolean connect, stind, heat_st;
boolean wi_fi_st, wi_fi_st2;

boolean stat_reboot, stat_wifi, stat, switch_h; 

// Переменные используемые для CaptivePortal
String ch_id_h = String(ESP.getChipId());
const char *myHostname  =  ch_id_h.c_str();               // Имя создаваемого хоста hostname.local 
const char *softAP_ssid = "CYBEREX-IV26IND";              // Имя создаваемой точки доступа Wi-Fi

String version_code = "IV26-1.19.12.24";

//timers
uint32_t  prevMills, lastMsg, reboot_t, lastConnectTry, tpm, tpm2;
int count_rf;
int counfl = 1;
int sw_count;
uint32_t NTP_t = 10000;


// Структура для хранения токенов сессий 
struct Token {
    String value;
    long created;
    long lifetime;
};

Token   tokens[20];                    // Длина массива структур хранения токенов 

#define TOKEN_LIFETIME 6000000         // время жизни токена в секундах

#define MAX_STRING_LENGTH 30           // Максимальное количество символов для хранения в конфигурации

String temp_j = "0";

// Структура для хранения конфигурации устройства
struct {
     boolean mqtt_en;
     int     statteeprom; 
     int     led_level;
     char    mySSID[MAX_STRING_LENGTH];
     char    myPW[MAX_STRING_LENGTH];
     char    mqtt_serv[MAX_STRING_LENGTH];
     char    mqtt_user[MAX_STRING_LENGTH];
     char    mqtt_passw[MAX_STRING_LENGTH];
     char    mqtt_topic[MAX_STRING_LENGTH];
     char    passwd[MAX_STRING_LENGTH]; 
     char    API_key[MAX_STRING_LENGTH];
     char    ntp_serv[MAX_STRING_LENGTH];
     int     time_zone;
     int     time_cycle;
     boolean ntp_en = false;
     boolean auto_on;
     float   data_min;
     float   data_max;
     char    time_on[MAX_STRING_LENGTH];
     char    time_off[MAX_STRING_LENGTH];
  } settings;

  int set_delay = 5000;

void setup() {
    EEPROM.begin(sizeof(settings));                                 // Инициализация EEPROM в соответствии с размером структуры конфигурации      
    pinMode(A, OUTPUT);                                             // Инициализация пина А
    pinMode(B, OUTPUT);                                             // Инициализация пина Б
    pinMode(V, OUTPUT);                                             // Инициализация пина В
    pinMode(G, OUTPUT);                                             // Инициализация пина Г
    pinMode(D, OUTPUT);                                             // Инициализация пина Д
    pinMode(E, OUTPUT);                                             // Инициализация пина Е
    pinMode(J, OUTPUT);                                             // Инициализация пина Ж
    pinMode(heat, OUTPUT);                                          // Инициализация пина накала
    read_config();                                                  // Чтение конфигурации из EEPROM
    check_clean();                                                  // Провека на запуск устройства после первичной прошивки
                                               
     if(String(settings.passwd) == ""){   
                                                                    // Если  переменная settings.passwd пуста, то назначаем пароль по умолчанию
         strncpy(settings.passwd, "admin", MAX_STRING_LENGTH);
     }
     analogWrite(heat, 255);
     heat_st = true;

     WiFi.mode(WIFI_STA);                                           // Выбираем режим клиента для сетевого подключения по Wi-Fi                
     WiFi.hostname("IV26 CYBEREX TECH");                            // Указываеем имя хоста, который будет отображаться в Wi-Fi роутере, при подключении устройства
     if(WiFi.status() != WL_CONNECTED) {                            // Инициализируем подключение, если устройство ещё не подключено к сети
           WiFi.begin(settings.mySSID, settings.myPW);
      }

     for(int x = 0; x < 160; x ++){                                  // Цикл ожидания подключения к сети (80 сек)
          if (WiFi.status() == WL_CONNECTED){ 
                stat_wifi = true;
                break;
           }
               indicator_light(map(x, 0, 160, 0, 100));
               delay(500); 
      
          }

      for(int x = 0; x < 160; x ++){                                  // Выводим анимацию загрузки
            indicator_light(map(x, 0, 160, 0, 100));
            delay(10); 
          }

     if(WiFi.status() != WL_CONNECTED) {                             // Если подключение не удалось, то запускаем режим точки доступа Wi-Fi для конфигурации устройства
            WiFi.mode(WIFI_AP_STA);
            WiFi.softAPConfig(apIP, apIP, netMsk);
            WiFi.softAP(softAP_ssid);
            stat_wifi = false;
        }
        delay(2000);
        // Запускаем DNS сервер
        dnsServer.setErrorReplyCode(DNSReplyCode::NoError);
        dnsServer.start(DNS_PORT, "*", apIP);
        // WEB страницы
        server.on("/", page_process);
        server.on("/login", handleLogin);
        server.on("/script.js", reboot_devsend);
        server.on("/style.css", css);
        server.on("/index.html", HTTP_GET, [](){
        server.send(200, "text/plain", "IoT CYBEREX IV26"); });
        server.on("/description.xml", HTTP_GET, [](){SSDP.schema(server.client());});
        server.on("/inline", []() {
        server.send(200, "text/plain", "this works without need of authentification");
        });
        server.onNotFound(handleNotFound);
        // Здесь список заголовков для записи
        const char * headerkeys[] = {"User-Agent", "Cookie"} ;
        size_t headerkeyssize = sizeof(headerkeys) / sizeof(char*);
        // Запускаем на сервере отслеживание заголовков 
        server.collectHeaders(headerkeys, headerkeyssize);
        server.begin();
        udp.begin(localPort);                                                             // NTP time
        connect = strlen(settings.mySSID) > 0;                                            // Статус подключения к Wi-Fi сети, если есть имя сети
        SSDP_init();
          
}

void loop() {
        portals();
        dnsServer.processNextRequest();
        server.handleClient();  
        reboot_dev_delay();
        MQTT_send(); 
        get_TIME_data();
        get_gata();
        no_wi_fi();
}

void reboot_devsend(){
   String rb = FPSTR(reb_d);
   server.send(200, "text", rb);
}
