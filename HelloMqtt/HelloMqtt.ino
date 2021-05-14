#include <OneWire.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#include "broker.h"

void setup() 
{
      delay(1000);
      pinMode(BUILTIN_LED, OUTPUT);     // Inicializa pino BUILTIN_LED como output
      Serial.begin(115200);
      Serial.println("\r\n\r\n***************************\r\nHello,MQTT  world! \r\nBom dia!\r\n");
      setup_wifi();
      setup_broker();

}


long iteration = 1;

void loop()    /// loop faz muito pouco: reconecta se necessario e chama o loop() do cliente mqtt
{
        if (!client.connected()) {
        conectaBroker(mqttUser, mqttPassword , 5) ;
        client.subscribe("sesisteam/#");    

        }
        client.loop();   
        iteration++;
        if( iteration%100000 == 0)
            client.publish("sesisteam", "Vivo!");
}
