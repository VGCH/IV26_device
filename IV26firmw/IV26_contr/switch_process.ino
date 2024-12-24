void callback(char* topic, byte* payload, unsigned int length) {
    String top_temp = get_topic(settings.mqtt_topic,   false);

        if(String(topic) == top_temp){
          String message;
          for (int i = 0; i < length; i++){
             message = message + (char)payload[i];
           }
           String key = get_topic(settings.mqtt_topic,   true);
           if(key.length() > 0){
              temp_j = json_decode(message, key);
           }else{
              temp_j = message;
           }
        }
 }

String json_decode(String text, String key){
       StaticJsonDocument<200> doc;
          deserializeJson(doc, text);
          String data = doc[key];

          return data; 
}