#include <Arduino.h>
#include "framebuffer.cpp"

TFT_eSPI tft = TFT_eSPI();
const byte led_gpio = 17;
int offset= 0;

void setup() {
  Serial.begin(115200);
  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_RED);
  pinMode(led_gpio, OUTPUT);
  digitalWrite(led_gpio, HIGH);
}

void loop() {
  tft.println("DAMA");
  delay(1000);
}
