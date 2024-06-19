

#include <MD_Parola.h>
#include <MD_MAX72xx.h>

#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 4  // 4 blocks
#define CS_PIN 9

// create an instance of the MD_Parola class
MD_Parola ledMatrix = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);
String text;

void setup() {
  Serial.begin(9600);
  ledMatrix.begin();          // initialize the object
  ledMatrix.setIntensity(0);  // set the brightness of the LED matrix display (from 0 to 15)
  ledMatrix.displayClear();   // clear LED matrix display
  text.reserve(30);
}

void loop() {
  if (Serial.available()) {               // if there is data comming
    text = Serial.readStringUntil('\n');  // read string until meet newline character

    ledMatrix.displayClear();  // clear led matrix display
    ledMatrix.displayScroll(text.c_str(), PA_CENTER, PA_SCROLL_LEFT, 100);
    Serial.print("LED Matrix displayed: ");  // reports action to smartphone app
    Serial.println(text);
  }

  if (ledMatrix.displayAnimate()) {
    ledMatrix.displayReset();
  }
}
