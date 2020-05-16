#include <SoftwareSerial.h>
#include <DFPlayerMini_Fast.h>
/*
  Serial object works much the same way as on a regular Arduino. Apart from hardware FIFO (128 bytes for TX and RX)
  Serial has additional 256-byte TX and RX buffers. Both transmit and receive is interrupt-driven. 
  Write and read functions only block the sketch execution when the respective FIFO/buffers are full/empty. 
  Note that the length of additional 256-bit buffer can be customized.
  
  Serial uses UART0, which is mapped to pins GPIO1 (TX) and GPIO3 (RX). 
  Serial may be remapped to GPIO15 (TX) and GPIO13 (RX) by calling Serial.swap() 
  after Serial.begin. Calling swap again maps UART0 back to GPIO1 and GPIO3.
  
  Serial1 uses UART1, TX pin is GPIO2. UART1 can not be used to receive data because normally 
  it’s RX pin is occupied for flash chip connection. To use Serial1, call Serial1.begin(baudrate).
  
  If Serial1 is not used and Serial is not swapped - TX for UART0 
  can be mapped to GPIO2 instead by calling Serial.set_tx(2) after Serial.begin or directly 
  with Serial.begin(baud, config, mode, 2).
*/
// Ligue o TX RX em D8 D7 que e o swap da usart0

DFPlayerMini_Fast myMP3;

void setup()
{
      Serial.begin(9600);
      Serial.swap();    //   TX D8 RX D7... swap muda  uart0 da USB para este pinos
      myMP3.begin(Serial);
      myMP3.wakeUp();
      myMP3.volume(30);
      delay(20);
      myMP3.play(1);
      delay(3000);
      myMP3.play(2);
      delay(4000);
}

void loop()
{
      myMP3.play(3);
      delay(2000);
      myMP3.sleep();
      delay(2000);
      myMP3.wakeUp();
    
      myMP3.play(4);
      delay(5000);
      myMP3.sleep();
      delay(2000);
      myMP3.wakeUp();
      
      myMP3.play(5);
      delay(2000);
      myMP3.sleep();
      delay(2000);
      myMP3.wakeUp();
    
      myMP3.play(2);
      delay(4000);
      myMP3.sleep();
      delay(2000);
      myMP3.wakeUp();
      
      myMP3.play(1);
      delay(3000);
      myMP3.sleep();
      delay(2000);
      myMP3.wakeUp();


}
