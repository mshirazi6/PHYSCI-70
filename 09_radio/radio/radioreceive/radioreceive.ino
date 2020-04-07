
/*
* Simple sketch for nRF24L01+ radios  Receive side.
* 
* Updated: Dec 2014 by TMRh20. Simplified Mar 2019 RMH.
*/

#include <Servo.h>
#include <SPI.h>
#include "RF24.h"

Servo myservo;

/* Hardware configuration: Set up nRF24L01 radio on SPI bus plus pins 7 & 8 */
RF24 radio(5,6);


byte addresses[][6] = {"1Node","2Node"};
int angle;
void setup() {

  //myservo.attach(9);
  Serial.begin(0);
  Serial.println(F("RF24example:  simple receive"));
  
  
  radio.begin();

  // Set the PA Level low to prevent power supply related issues since this is a
 // getting_started sketch, and the likelihood of close proximity of the devices. RF24_PA_MAX is default.
  radio.setPALevel(RF24_PA_LOW);
  
 
    radio.openWritingPipe(addresses[1]);
    radio.openReadingPipe(1,addresses[0]);
 
  
  // Start the radio listening for data
  radio.startListening();
}

void loop() {
    Serial.println("test");
    byte rec_data;
    Serial.println(radio.available());
    if( radio.available()){
                                                                    // Variable for the received timestamp
      while (radio.available()) {                                   // While there is data ready
        radio.read( &rec_data, 1 );             // Get the payload
      }
     
      
      Serial.print("received ");
      Serial.println(rec_data); 
      angle = map(rec_data, 0, 255, 0, 180); 
      myservo.write(angle);
      //Serial.println(rec_data); 
   }



} // Loop
