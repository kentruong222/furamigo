/*
 * Rui Santos 
 * Complete Project Details https://randomnerdtutorials.com/guide-for-microphone-sound-sensor-with-arduino/
 * 
 * replace with keenwes mp3
*/

#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

static const uint8_t PIN_MP3_TX = 2; // Connects to module's RX
static const uint8_t PIN_MP3_RX = 3; // Connects to module's TX
SoftwareSerial softwareSerial(PIN_MP3_RX, PIN_MP3_TX);

// Create the Player object
DFRobotDFPlayerMini player;

int sensorPin=8;
boolean val =0;

void setup(){
  pinMode(sensorPin, INPUT);
  Serial.begin (9600);
  softwareSerial.begin(9600);
}
  
void loop (){
  val = digitalRead(sensorPin);
  Serial.println (val);
  // when the sensor detects a signal above the threshold value, 0001.mp3 plays
  if (val==HIGH) {
    player.begin(softwareSerial);
   // Set volume to maximum (0 to 30).
   player.volume(15);
  // Play the "0001.mp3" in the "mp3" folder on the SD card
   player.playMp3Folder(1);
  }

}
