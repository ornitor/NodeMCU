#include <SoftwareSerial.h>
#include <DFPlayerMini_Fast.h>

DFPlayerMini_Fast myMP3;

enum Fala { NEUTRAL, VOID, SAUDA, SAUDA2, SAUDA3, DESPEDE, ENCAMINHA};

void initVoice(int volume)
{
      Serial.begin(9600);
      Serial.swap();    //   TX D8 RX D7... swap muda  uart0 da USB para este pinos
      myMP3.begin(Serial);
      myMP3.wakeUp();
      myMP3.volume(volume);
      delay(300);
      pinMode(LED_BUILTIN, OUTPUT);

}


void blink(int n)
{
  for(int i=0;i<n;i++){
      digitalWrite(LED_BUILTIN,LOW);
      delay(300);
      digitalWrite(LED_BUILTIN,HIGH);
      delay(300);
  } 
  delay(600);
}


void play(enum Fala fala)
{
        myMP3.play((int)fala);
        //blink((int)fala);
}
