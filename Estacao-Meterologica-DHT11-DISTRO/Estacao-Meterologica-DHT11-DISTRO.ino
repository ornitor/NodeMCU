
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>

const char* ssid =  "ssid da sua rede";   
const char* password =  "sua senha";
const char* mqttServer = "broker.hivemq.com";
const int mqttPort = 1883;
const char* mqttUser = "" ; //Usuário no broker se o broker exigir
const char* mqttPassword = "" ; //Senha
const char* clientId = "";  // cliente se broker exigir precisar
String rtopico = "estacao/local";

#define  INTERVALO  20000

WiFiClient espClient;
PubSubClient client(espClient);
DHT dht(D3, DHT22); // sensor DHT montado no pino D3
long lastMsg = 0;


void setup()
{
          delay(1000);
          Serial.begin(115200);
          delay(2000);
          setup_wifi();
          setup_broker();
          dht.begin();
          Serial.println("\n\n\n**********************************\nEstação metereológica DHT11");
          Serial.println("Bom dia!\n");

}


void loop()
{
          if (!client.connected())   // caso perder conexão reconecta
                setup_broker();
          long now = millis();
          if (now - lastMsg > INTERVALO) {
                lastMsg = now;
                float umidade = dht.readHumidity();
                float temperatura = dht.readTemperature();
                publica(temperatura, umidade);
                serialEcho(temperatura, umidade);
          }

}

void setup_wifi()
{
          delay(10);
          Serial.print("\n\n\n\nConectando rede ");
          Serial.println(ssid);
          WiFi.begin(ssid, password);
          for (int i = 0; WiFi.status() != WL_CONNECTED; i++) {
              delay(500);
              Serial.print(".");
              if (i % 80 == 79)
                  Serial.println("\nConexão mal sucedida. Retentando...");
                  
             }
          Serial.print("\nWiFi conectado IP: ");
          Serial.println(WiFi.localIP());
}

void setup_broker()
{
          client.setServer(mqttServer, mqttPort);
          delay(500);
          Serial.print("Conectando a ");
          Serial.print(mqttServer);
          Serial.print(":");
          Serial.println(mqttPort);
          for (int i = 0; !client.connected() && i < 30; i++) {    // tenta ate 30 vezes
                    if (client.connect(clientId, mqttUser, mqttPassword )) {
                        Serial.println("Conectado ao broker");
                    } else {
                              Serial.print("Falhou conexao com o broker ");
                              Serial.println(client.state());
                              delay(2000);
                    }
          }
}



void publica(float temperatura, float umidade)
{
          String topic ;
          String msg ;
          topic = rtopico + (String)"/umidade";
          msg = (String)umidade;
          client.publish(topic.c_str(), msg.c_str());
          topic = rtopico + (String)"/temperatura";
          msg = (String)temperatura;
          client.publish(topic.c_str(), msg.c_str());
}

void serialEcho(float temperatura, float umidade)
{
          Serial.print(rtopico);
          Serial.print(": ");
          Serial.print(umidade);
          Serial.print(" :: ");
          Serial.println(temperatura);
}
