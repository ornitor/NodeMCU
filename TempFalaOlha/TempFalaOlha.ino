#include <Wire.h>
#include <Adafruit_MLX90614.h>
#include "RobotEyes.h"

/*
 * interface robo panda olhos e voice
 * necesario gerar arquivios numnerado sequenciaklemte no microSD
 * usa matri de LED  em D0, D5, D6 data, cs e clock
 * usa serial em swap em D8 e D9  Tx Rx
 * Libraries: MLX90614, MD_MAX72xx, DFPlayerMini
 */

enum Fala { VOID, SAUDA, SAUDA2, SAUDA3, DESPEDE, ENCAMINHA};
void initOlhos();
void initVoice(int volume);
void execute(int com);
void play(enum Fala fala);


Adafruit_MLX90614 mlx = Adafruit_MLX90614();

void setup()
{
   initOlhos();
   initVoice(10);
   mlx.begin();
}

int com = 0;
extern enum stateLst state ;//state
float tempTesta, tempAmb;
int sensorIV;

void loop()
{
   if(state == S_STOP){
      com = 99;
      state = S_TEXT;
      tempAmb = mlx.readAmbientTempC(); 
      tempTesta = mlx.readObjectTempC();
      sensorIV = random(10);
      if (sensorIV <9)
          com = 0;
      if (tempTesta > 35 && tempTesta <= 37 )
          com = 3;
      if (tempTesta > 37)
          com = 4;
   }   
   
   switch(com%8){
    case 0:    if(state == S_TEXT)play(SAUDA);
               execute(RobotEyes::E_BLINK);
               break;
    case 1:    if(state == S_TEXT)play(SAUDA2);
               execute(RobotEyes::E_WINK);
               break;
    case 2:    if(state == S_TEXT)play(SAUDA3);
               execute(RobotEyes::E_LOOK_L);
               break;
    case 3:    if(state == S_TEXT)play(DESPEDE);
               execute(RobotEyes::E_LOOK_R);
               break;
    case 4:    if(state == S_TEXT)play(ENCAMINHA);
               execute(RobotEyes::E_LOOK_U);
               break;
    default:   execute(RobotEyes::E_NONE);
               break;

   }
}

/*  E_NONE,     
    E_NEUTRAL,  
    E_BLINK,    
    E_WINK,  
    E_LOOK_L,  
    E_LOOK_R,  
    E_LOOK_U,  
    E_LOOK_D, 
    E_ANGRY,   
    E_SAD,  
    E_EVIL,  
    E_EVIL2, 
    E_SQUINT,
    E_DEAD,    
    E_SCAN_UD,  
    E_SCAN_LR,  
    */
