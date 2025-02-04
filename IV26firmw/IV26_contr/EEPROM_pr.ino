// Функция очистка памяти при первой прошивке
void check_clean(){
       if(settings.statteeprom != 28){ 
          for (int i = 0; i < sizeof(settings); ++i) {
              EEPROM.write(i, 0); 
            }      
              EEPROM.commit();
             settings.statteeprom = 28;
        }
   }
   
// Функция чтения конфигурации из EEPROM
void read_config(){
        EEPROM.get(0, settings);
   }
   
// Функция записи конфигурации в EEPROM
void save_config(){
        EEPROM.begin(sizeof(settings));
        EEPROM.put(0, settings);                 // Сохранение конфигурации в EEPROM 
        EEPROM.commit();
   }
