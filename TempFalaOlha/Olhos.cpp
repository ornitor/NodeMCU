#include <MD_MAX72xx.h>
//#include <SPI.h>

#include "RobotEyes.h"




// NOTE: These pin numbers will probably not work with your hardware and may
// need to be adapted
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW  
#define MAX_DEVICES 4
#define DATA_PIN D0  
#define CS_PIN  D5  
#define CLK_PIN   D6  

MD_MAX72XX M = MD_MAX72XX(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);

RobotEyes E;


void initOlhos()
{
      M.begin();
      E.begin(&M);
      E.setText("RobotEyes");
      do { } while (!E.runAnimation()); // wait for the text to finish
} 
typedef struct
{
  char name[8];
  RobotEyes::emotion_t e;
  uint16_t timePause;  // in milliseconds
} sampleItem_t;

const sampleItem_t eSeq[] =
{
  { "Neutral", RobotEyes::E_NEUTRAL, 20000 },
  { "Blink" , RobotEyes::E_BLINK, 1000 },
  { "Wink"  , RobotEyes::E_WINK, 1000 },
  { "Left"  , RobotEyes::E_LOOK_L, 1000 },
  { "Right" , RobotEyes::E_LOOK_R, 1000 },
  { "Up"    , RobotEyes::E_LOOK_U, 1000 },
  { "Down"  , RobotEyes::E_LOOK_D, 1000 },
  { "Angry" , RobotEyes::E_ANGRY, 1000 },
  { "Sad"   , RobotEyes::E_SAD, 1000 },
  { "Evil"  , RobotEyes::E_EVIL, 1000 },
  { "Evil2" , RobotEyes::E_EVIL2, 1000 },
  { "Squint", RobotEyes::E_SQUINT, 1000 },
  { "Dead"  , RobotEyes::E_DEAD, 1000 },
  { "ScanV" , RobotEyes::E_SCAN_UD, 1000 },
  { "ScanH" , RobotEyes::E_SCAN_LR, 1000 },
};



enum  stateLst  state = S_IDLE;

void execute(int com)
{
  static uint32_t timeStartDelay;
  static uint8_t index = ARRAY_SIZE(eSeq);

  bool b = E.runAnimation();    // always run the animation
  
  switch (state)
  {
  case S_STOP:
    break;
  case S_IDLE:
    E.setText(eSeq[com].name);
    state = S_TEXT;
    break;
  case S_TEXT: // wait for the text to finish
    if (b)  // text animation is finished
    {
      E.setAnimation(eSeq[com].e, true);
      state = S_ANIM;
    }
    break;

  case S_ANIM:  // checking animation is completed
    if (b)  // animation is finished
    {
      timeStartDelay = millis();
      state = S_PAUSE;
    }
    break;
  
  case S_PAUSE: // non blocking waiting for a period between animations
    if (millis() - timeStartDelay >= eSeq[com].timePause)
      state = S_STOP;
    break;

  default:
    state = S_STOP;
    break;
  }
}
