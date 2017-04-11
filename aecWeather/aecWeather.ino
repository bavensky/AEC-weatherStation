/******************************************************
  AEC Weather Station
  RMUTL Senior Project
  Author  : ArduinoSiam
  Date   : 10/04/2560

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
  Button 1      A1
  Button 2      A2
  Button 3      A3
  Button 4      A4
  Button 5      A5
  Button 6      A6
  Button 7      A7
  Button 8      A8
  Button 9      A9
  Button 10     A10
  Button 11     A11

  DHT sensor
  VCC           5V
  GND           GND
  Signal        2

  Signal Speaker
  Speaker       6 //46
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

int t;
String lang;
const int buttonPin[12] = {0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11};
int buttonState[12];
int lastButtonState[12];

String m_str;
char ch0, ch1, ch2, ch3;
String scrollString = "C";


/************** Sub function **************/
void play_wid(String wid) {
  tmrpcm.quality(1);
  if (wid.toInt() < 10) {
    one_word(wid.toInt());
  } else if (wid.toInt() >= 10 && wid.toInt() <= 99) {
    two_word((wid.substring(0, 1)).toInt());
    delay(1000);
    one_word((wid.substring(1, 2)).toInt());
  }
  delay(800);
  m_str = "" + lang + "/""021.wav" ;    //  sound degree Celsius

  tmrpcm.play(&m_str[0u]);
  delay(1300);
}


void one_word(int num) {
  tmrpcm.quality(1);
  if (num == 1) {
    m_str = "" + lang + "/""001.wav" ;
    char *m_play = &m_str[0u];
    tmrpcm.play(m_play);
  } else if (num == 2) {
    m_str = "" + lang + "/""002.wav" ;
    char *m_play = &m_str[0u];
    tmrpcm.play(m_play);
  } else if (num == 3) {
    m_str = "" + lang + "/""003.wav" ;
    char *m_play = &m_str[0u];
    tmrpcm.play(m_play);
  } else if (num == 4) {
    m_str = "" + lang + "/""004.wav" ;
    char *m_play = &m_str[0u];
    tmrpcm.play(m_play);
  } else if (num == 5) {
    m_str = "" + lang + "/""005.wav" ;
    char *m_play = &m_str[0u];
    tmrpcm.play(m_play);
  } else if (num == 6) {
    m_str = "" + lang + "/""006.wav" ;
    char *m_play = &m_str[0u];
    tmrpcm.play(m_play);
  } else if (num == 7) {
    m_str = "" + lang + "/""007.wav" ;
    char *m_play = &m_str[0u];
    tmrpcm.play(m_play);
  } else if (num == 8) {
    m_str = "" + lang + "/""008.wav" ;
    char *m_play = &m_str[0u];
    tmrpcm.play(m_play);
  } else if (num == 9) {
    m_str = "" + lang + "/""009.wav" ;
    char *m_play = &m_str[0u];
    tmrpcm.play(m_play);
  }
}


void two_word(int num) {
  tmrpcm.quality(1);
  if (num == 1) {
    m_str = "" + lang + "/""010.wav" ;
    char *m_play = &m_str[0u];
    tmrpcm.play(m_play);
  } else if (num == 2) {
    m_str = "" + lang + "/""011.wav" ;
    char *m_play = &m_str[0u];
    tmrpcm.play(m_play);
  } else if (num == 3) {
    m_str = "" + lang + "/""012.wav" ;
    char *m_play = &m_str[0u];
    tmrpcm.play(m_play);
  } else if (num == 4) {
    m_str = "" + lang + "/""013.wav" ;
    char *m_play = &m_str[0u];
    tmrpcm.play(m_play);
  } else if (num == 5) {
    m_str = "" + lang + "/""014.wav" ;
    char *m_play = &m_str[0u];
    tmrpcm.play(m_play);
  } else if (num == 6) {
    m_str = "" + lang + "/""015.wav" ;
    char *m_play = &m_str[0u];
    tmrpcm.play(m_play);
  } else if (num == 7) {
    m_str = "" + lang + "/""016.wav" ;
    char *m_play = &m_str[0u];
    tmrpcm.play(m_play);
  } else if (num == 8) {
    m_str = "" + lang + "/""017.wav" ;
    char *m_play = &m_str[0u];
    tmrpcm.play(m_play);
  } else if (num == 9) {
    m_str = "" + lang + "/""018.wav" ;
    char *m_play = &m_str[0u];
    tmrpcm.play(m_play);
  }
}



/************** Main function **************/
void setup() {
  //  initial serial
  Serial.begin(9600);

  //  temperature sensor
  dht.begin();

  //  sound output
  tmrpcm.speakerPin = 46;

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
    pinMode(buttonPin[i], INPUT);
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
  //Serial.println(t);


  //  show dot matrix
  if(t == 0) {
    ch0 = 0;
  } else {
    ch0 = String(t)[0];
  }
  ch1 = String(t)[1];
  ch2 = scrollString[0];
  lc.displayChar(0, lc.getCharArrayPosition(ch0));
  lc.displayChar(1, lc.getCharArrayPosition(ch1));
  lc.displayChar(2, lc.getCharArrayPosition(ch2));
  

  //  press button for select language
  for (int i = 1; i <= 11; i++) {
    if (buttonState[i] != lastButtonState[i]) {
      if (buttonState[i] == HIGH) {
        lang = String(i);
        play_wid(String(t));
        Serial.print("Button");
        Serial.println(i);
      }
      delay(50);
      lastButtonState[i] = buttonState[i];
    }
  }
} //  end loop


