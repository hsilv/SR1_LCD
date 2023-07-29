#include <Arduino.h>
#include <iostream>
#include "framebuffer.cpp"

const byte led_gpio = 17;
int SCREEN_WIDTH;
int SCREEN_HEIGHT;
int offset = 0;
bool xy = false;
Vector3d A;
Vector3d B;
Vector3d C;

template <typename T>
std::string toString(const T &value)
{
  std::stringstream stream;
  stream << value;
  return stream.str();
}

void setup()
{
  Serial.begin(115200);
  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);
  pinMode(led_gpio, OUTPUT);
  digitalWrite(led_gpio, HIGH);
  SCREEN_WIDTH = tft.getViewportX();
  SCREEN_HEIGHT = tft.getViewportY();
}

void loop()
{
  xy = !xy;
  if (xy)
  {
    setCurrentColorBuffer(Color(255, 0, 0));
    Vector3d A(0, 0, 0);
    Vector3d B(160, 72, 0);
    Vector3d C(20, 115, 55);
    triangleBuffer(A, B, C);
  }
  else
  {
    setCurrentColorBuffer(Color(0, 255, 0));
    Vector3d A(0, 0, 0);
    Vector3d B(56, 79, 10);
    Vector3d C(20, 55, 55);
    triangleBuffer(A, B, C);
  }
}
