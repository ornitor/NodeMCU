
/*
 *   Alterna estado do LED da placa do NodeMCU ESP8266
 *   atraves de um broker MQTT
 * 
 */
 
 
#include <ESP8266WiFi.h>
#include <PubSubClient.h>


#ifdef MASTER_BROKER


char* ssid =  "ssis";   
char* password =  "senha-de-rede"; 
char* mqttServer = "url.do.broker";
int mqttPort = 1883;
char* mqttUser = "" ; //Usuário
char* mqttPassword = "" ; //Senha


//Variáveis de wifi e broker mqtt
WiFiClient espClient;
PubSubClient client(espClient);

unsigned int fgPub = 0;
unsigned int fgVerbose = 1;

#else
// configure a tua rede wireless
extern const char* ssid ; 
extern const char* password ; 

// Configure o teu broker e a instancia
extern char* mqttServer;
extern const int mqttPort ;
extern char* mqttUser;
extern char* mqttPassword ;

//Variáveis de wifi e broker mqtt
extern WiFiClient espClient;
extern PubSubClient client;

extern unsigned int fgPub;
extern unsigned int fgVerbose;
#endif


void setup_wifi() ;
void setup_broker() ;
void minhaFuncaoSubscritora(char* topic, byte* payload, unsigned int length);
void conectaBroker(char* user, char* password, int n) ;
