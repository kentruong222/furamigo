#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
#include <Servo.h>

// constants won't change
const int TRIG_PIN  = 6;  // Arduino pin connected to Ultrasonic Sensor's TRIG pin
const int ECHO_PIN  = 7;  // Arduino pin connected to Ultrasonic Sensor's ECHO pin
const int SERVO_PIN = 9; // Arduino pin connected to Servo Motor's pin
const int DISTANCE_THRESHOLD = 25; // centimeters

static const uint8_t PIN_MP3_TX = 2; // Connects to module's RX
static const uint8_t PIN_MP3_RX = 3; // Connects to module's TX
SoftwareSerial softwareSerial(PIN_MP3_RX, PIN_MP3_TX);

// Create the Player object
DFRobotDFPlayerMini player;

Servo servo; // create servo object to control a servo


int sensorPin=8;
boolean val =0;


// variables will change:
float duration_us, distance_cm;

void setup() {
  pinMode(sensorPin, INPUT); //What soundsensor pin is
  Serial.begin (9600);       // initialize serial port
  pinMode(TRIG_PIN, OUTPUT); // set arduino pin to output mode
  pinMode(ECHO_PIN, INPUT);  // set arduino pin to input mode
  softwareSerial.begin(9600); //dfplayer begins
  servo.attach(SERVO_PIN);   // attaches the servo on pin 9 to the servo object
  servo.write(0);
}

void loop() {
  // generate 10-microsecond pulse to TRIG pin
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // measure duration of pulse from ECHO pin
  duration_us = pulseIn(ECHO_PIN, HIGH);
  // calculate the distance
  distance_cm = 0.017 * duration_us;

  if(distance_cm < DISTANCE_THRESHOLD)
    servo.write(0); // rotate servo motor to 90 degree
  else
    servo.write(90);  // rotate servo motor to 0 degree

  // print the value to Serial Monitor
  Serial.print(distance_cm);
  Serial.println(" cm");

  //sound+dfplayer
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

  delay(500);
}
