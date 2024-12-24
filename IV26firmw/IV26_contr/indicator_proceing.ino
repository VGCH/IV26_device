void indicator_light(int percent){
  int brl = 255;
   if (settings.auto_on){
      brl = BRReadData();                             // Автоматическая яркость
   }else if(settings.led_level > 0){
      brl = map(settings.led_level, 0, 100, 0, 255);  // Ручная яркость
   }
  switch (percent) {
    case 0 ... 14: 
        analogWrite(A, brl);
        analogWrite(B, 0);
        analogWrite(V, 0);
        analogWrite(G, 0);
        analogWrite(D, 0);
        analogWrite(E, 0);
        analogWrite(J, 0);
      break;
    case 15 ... 28:
        analogWrite(A, brl);
        analogWrite(B, brl);
        analogWrite(V, 0);
        analogWrite(G, 0);
        analogWrite(D, 0);
        analogWrite(E, 0);
        analogWrite(J, 0);
      break;
    case 29 ... 42:
        analogWrite(A, brl);
        analogWrite(B, brl);
        analogWrite(V, brl);
        analogWrite(G, 0);
        analogWrite(D, 0);
        analogWrite(E, 0);
        analogWrite(J, 0);
      break;
    case 43 ... 56:
        analogWrite(A, brl);
        analogWrite(B, brl);
        analogWrite(V, brl);
        analogWrite(G, brl);
        analogWrite(D, 0);
        analogWrite(E, 0);
        analogWrite(J, 0);
      break;
    case 57 ... 70:
        analogWrite(A, brl);
        analogWrite(B, brl);
        analogWrite(V, brl);
        analogWrite(G, brl);
        analogWrite(D, brl);
        analogWrite(E, 0);
        analogWrite(J, 0);
      break;
    case 71 ... 84:
        analogWrite(A, brl);
        analogWrite(B, brl);
        analogWrite(V, brl);
        analogWrite(G, brl);
        analogWrite(D, brl);
        analogWrite(E, brl);
        analogWrite(J, 0);
      break;
    case 85 ... 100:
        analogWrite(A, brl);
        analogWrite(B, brl);
        analogWrite(V, brl);
        analogWrite(G, brl);
        analogWrite(D, brl);
        analogWrite(E, brl);
        analogWrite(J, brl);
      break;
  }

}

void get_gata(){
     unsigned long ctime = millis();
   if(tpm - ctime > 1000){
        if(WiFi.status() == WL_CONNECTED){               // Отображаем уровень сигнала Wi-fi если прием данных не настроен
           if(settings.mqtt_en && temp_j != "0"){
             int min = int(settings.data_min);
             int max = int(settings.data_max);
             int data = temp_j.toInt();
             indicator_light(map(data, min, max, 0, 100));
             shedule_time(epoch);
           }else{
              int level = abs(WiFi.RSSI());
              indicator_light(map(level, 80, 30, 0, 100));
           }
           wi_fi_st2 = false;
        }else{
           wi_fi_st2 = true;
      }
     tpm = ctime;
  }
}

void no_wi_fi(){
  if(wi_fi_st2){
    unsigned long nows = millis();
    if (nows - tpm2 > 10) {
       if(counfl == 1){ stind = true; }
       if(counfl == 254){ stind = false; }
       if(stind){ counfl++; }else{ counfl--; }
        analogWrite(A, 0);
        analogWrite(B, 0);
        analogWrite(V, counfl);
        analogWrite(G, counfl);
        analogWrite(D, counfl);
        analogWrite(E, 0);
        analogWrite(J, 0);
       tpm2 = nows;
     }
   }
  }