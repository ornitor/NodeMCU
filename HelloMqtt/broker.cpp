
/*
 *   Alterna estado do LED da placa do NodeMCU ESP8266
 *   atraves de um broker MQTT
 * 
 */
 
 
#include <ESP8266WiFi.h>
#include <PubSubClient.h>


#define MASTER_BROKER
#include "broker.h"



void setup_wifi() 
{
        WiFi.begin(ssid, password);
        Serial.println("Conectando WiFi:");
        for(int i=1; WiFi.status() != WL_CONNECTED; i++) {
                  delay(500);
                  if(i%80==0)
                          Serial.println(i);
                  Serial.print(".");
                  }
        Serial.print("\nWiFi conectado IP: ");
        Serial.println(WiFi.localIP());
}


void setup_broker() 
{
        delay(100);
        client.setServer(mqttServer, mqttPort);
        delay(100);
        client.setCallback(minhaFuncaoSubscritora);
        Serial.print("Conectando ");
        Serial.print(mqttServer);
        Serial.print(":");
        Serial.println(mqttPort);
        conectaBroker(mqttUser, mqttPassword , 5) ;
        client.subscribe("sesisteam/#");  //  "#" significa subscribe todas as mensagens
}


void minhaFuncaoSubscritora(char* qtopico, byte* qmensagem, unsigned int tamanho)
{
      String strTopico =  String(qtopico);
      qmensagem[tamanho] = '\0';
      String strMensagem = String((char*)qmensagem);
      strMensagem.toLowerCase();
      Serial.print(strTopico);
      Serial.print(": ");
      Serial.println(strMensagem);
      if(strTopico == "sesisteam/led"){ 
            if( strMensagem == "on") {
                        digitalWrite(BUILTIN_LED, LOW);   // Liga o LED da placa (no NodeMCU nivel Low liga o led))
                }
                else {
                        digitalWrite(BUILTIN_LED, HIGH);  // Desiga o LED da placa (no NodeMCU nivel High liga o led))
                }

      }
      if(strTopico == "sesisteam/print"){ 
            Serial.println(strMensagem);

      }


}



void conectaBroker(char* user, char* password, int n) 
{
     for(int i=0;  i<n && !client.connected();  i++) {   // fica em loop ate conectar
            Serial.print("... ");
            String clientId = "ETH0";
            clientId += String(random(0xffff), HEX);
            if (client.connect(clientId.c_str(), user,password)) {
                Serial.println("Conectado.");
            } else {
                Serial.print("Falhou, rc=");
                Serial.print(client.state());
                Serial.println(" retentando em 5 seconds");
                delay(5000);  // espere 5 segundos antes de retentar
            } 
        }
}
