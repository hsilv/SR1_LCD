#include <Arduino.h>
#include <iostream>
#include "framebuffer.cpp"
#include <SPI.h>

#include <FS.h>
#include <SD.h>

int SCREEN_WIDTH;
int SCREEN_HEIGHT;
int offset = 0;
bool xy = false;
Vector3d A;
Vector3d B;
Vector3d C;

std::vector<Vector3d> vertices;

template <typename T>
std::string toString(const T &value)
{
  std::stringstream stream;
  stream << value;
  return stream.str();
}

void printDirectory(File dir, int numTabs);

File root;

void setup()
{
  Serial.begin(115200);
  digitalWrite(15, HIGH);
  digitalWrite( 5, HIGH); 
  tft.begin();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);
  SCREEN_WIDTH = tft.getViewportX();
  SCREEN_HEIGHT = tft.getViewportY();

  if (!SD.begin(5)) {
    Serial.println("Card Mount Failed");
    return;
  }
  uint8_t cardType = SD.cardType();

  if (cardType == CARD_NONE) {
    Serial.println("No SD card attached");
    return;
  }

  Serial.print("SD Card Type: ");
  if (cardType == CARD_MMC) {
    Serial.println("MMC");
  } else if (cardType == CARD_SD) {
    Serial.println("SDSC");
  } else if (cardType == CARD_SDHC) {
    Serial.println("SDHC");
  } else {
    Serial.println("UNKNOWN");
  }

  uint64_t cardSize = SD.cardSize() / (1024 * 1024);
  Serial.printf("SD Card Size: %lluMB\n", cardSize);

  Serial.println("initialisation done.");

  root = SD.open("/");

  printDirectory(root, 0);

  Serial.println("done!");
}

void loop()
{
  setCurrentColorBuffer(Color(255, 0, 0)); // Color rojo

  Vector3d A(0, 0, 0);
  Vector3d B(0, -50, 0);
  Vector3d C(45, -30, 0);
  Vector3d D(45, 20, 0);
  Vector3d E(0, 40, 0);
  Vector3d G(-45, -30, 0);
  Vector3d H(-45, 20, 0);

  triangleBuffer(A, B, C);
  triangleBuffer(A, C, D);
  triangleBuffer(A, D, E);
  triangleBuffer(A, B, G);
  triangleBuffer(A, G, H);
  triangleBuffer(A, H, E);
}


void printDirectory(File dir, int numTabs) {
  while (true) {

    File entry =  dir.openNextFile();
    if (! entry) {
      // no more files
      break;
    }
    for (uint8_t i = 0; i < numTabs; i++) {
      Serial.print('\t');
    }
    Serial.print(entry.name());
    if (entry.isDirectory()) {
      Serial.println("/");
      printDirectory(entry, numTabs + 1);
    } else {
      // files have sizes, directories do not
      Serial.print("\t\t");
      Serial.println(entry.size(), DEC);
    }
    entry.close();
  }
}