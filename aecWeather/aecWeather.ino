/******************************************************
  AEC Weather Station
  RMUTL Senior Project
  Author  : ArduinoSiam
  Date    : 29/04/2560

  // pin connecting
  Module Pin      Arduino Mega2560
  Dot matrix 8x8
  DIN           12
  CLK           11
  CS            10
  VCC           5V
  GND           GND

  SD CARD
  SS            53
  MOSI          51
  MISO          50
  SCK           52
  VCC           5V
  GND           GND

  Push Button
  Button 1      22    
  Button 2      24    
  Button 3      26    
  Button 4      28    
  Button 5      30    
  Button 6      32    
  Button 7      34    
  Button 8      36    
  Button 9      38    
  Button 10     40    
  Button 11     42    

  DHT sensor
  VCC           5V
  GND           GND
  Signal        2

  Signal Speaker
  Speaker       6 
  Speaker GND   GND
*/

#include "DHT.h"
#include <SdFat.h>
#include <TMRpcm.h>
#include "LedControlMS.h"

#define DHTPIN 2
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

SdFat sd;
TMRpcm tmrpcm;

#define NBR_MTX 4
LedControl lc = LedControl(12, 11, 10, 4);

#define SPEAKER  6

int t;
String lang;
const int buttonPin[12] = {A0, 22, 24, 26, 28, 30, 32, 34, 36, 38, 40, 42};
int buttonState[12];
int lastButtonState[12];

String m_str;
char ch0, ch1, ch2, ch3;

byte cc[8] = {B00000011,
              B00000011,
              B00000000,
              B01111110,
              B10000001,
              B10000001,
              B10000001,
              B01000010,
             };

/************** Sub function **************/
void printCelsius() {
  lc.setRow(2, 0, cc[0]);
  lc.setRow(2, 1, cc[1]);
  lc.setRow(2, 2, cc[2]);
  lc.setRow(2, 3, cc[3]);
  lc.setRow(2, 4, cc[4]);
  lc.setRow(2, 5, cc[5]);
  lc.setRow(2, 6, cc[6]);
  lc.setRow(2, 7, cc[7]);
}

/************** Main function **************/
void setup() {
  //  initial serial
  Serial.begin(9600);

  //  temperature sensor
  dht.begin();

  //  sound output
  tmrpcm.speakerPin = SPEAKER; 

  //  sd card
  if (!sd.begin(53, SPI_FULL_SPEED)) {
    return;
    Serial.println("Failed");
  } else {
    Serial.println("SD OK");
  }
  delay(1000);


  //  set input button
  for (int i = 1; i <= 11; i++) {
    pinMode(buttonPin[i], INPUT_PULLUP);
  }

  //  dot matrix
  for (int i = 0; i < NBR_MTX; i++) {
    lc.shutdown(i, false);
    lc.setIntensity(i, 1);
    lc.clearDisplay(i);
  }
  delay(100);
  lc.clearAll();

}

void loop() {
  //  read press button
  buttonState[1] = digitalRead(buttonPin[1]);
  buttonState[2] = digitalRead(buttonPin[2]);
  buttonState[3] = digitalRead(buttonPin[3]);
  buttonState[4] = digitalRead(buttonPin[4]);
  buttonState[5] = digitalRead(buttonPin[5]);
  buttonState[6] = digitalRead(buttonPin[6]);
  buttonState[7] = digitalRead(buttonPin[7]);
  buttonState[8] = digitalRead(buttonPin[8]);
  buttonState[9] = digitalRead(buttonPin[9]);
  buttonState[10] = digitalRead(buttonPin[10]);
  buttonState[11] = digitalRead(buttonPin[11]);

  //  read temperature
  t = dht.readTemperature();
  Serial.println(t);


  //  show dot matrix
  if (t == 0) {
    ch0 = 0;
  } else {
    ch0 = String(t)[0];
  }
  ch1 = String(t)[1];
  ch2 = scrollString[0];
  lc.displayChar(0, lc.getCharArrayPosition(ch0));
  lc.displayChar(1, lc.getCharArrayPosition(ch1));
  printCelsius();
  delay(100);

  //  press button for select language
  for (int i = 1; i <= 11; i++) {
    if (buttonState[i] != lastButtonState[i]) {
      if (buttonState[i] == LOW) {
        lang = String(i);
        //        play_wid(String(t));

        tmrpcm.quality(1);
        m_str = "" + lang + "/" + String(t) + ".wav";
        char *m_play = &m_str[0u];
        tmrpcm.play(m_play);

        Serial.print("m_play = ");
        Serial.println(m_play);
        Serial.print("Button");
        Serial.println(i);
        delay(2000);
      }
      lastButtonState[i] = buttonState[i];
    }
  }
} //  end loop


