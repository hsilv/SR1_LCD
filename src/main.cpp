#include <Arduino.h>
#include <iostream>
#include "framebuffer.cpp"
#include <SPI.h>
#include <FS.h>
#include <SD.h>

int SCREEN_WIDTH;
int SCREEN_HEIGHT;

File root;
File obj;
std::vector<Vector3d> vertices;
std::vector<Face> faces;

void printDirectory(File dir, int numTabs);

bool loadOBJ(const std::string &path, std::vector<Vector3d> &out_vertices, std::vector<Face> &out_faces)
{
  out_vertices.clear();
  out_faces.clear();

  File obj = SD.open(path.c_str());
  if (!obj)
  {
    Serial.println("error opening " + String(path.c_str()));
    return false;
  }

  std::vector<Vector3d> temp_vertices;

  char buffer[128];

  while (obj.available())
  {
    String line = obj.readStringUntil('\n');
    line.trim();

    strncpy(buffer, line.c_str(), sizeof(buffer) - 1);
    buffer[sizeof(buffer) - 1] = '\0';

    char type[3];
    int result = sscanf(buffer, "%2s", type);

    if (result == 1)
    {
      if (strcmp(type, "v") == 0)
      {
        double x, y, z;
        if (sscanf(buffer, "v %lf %lf %lf", &x, &y, &z) == 3)
        {
          Vector3d temp(x, y, z);
          temp_vertices.push_back(temp);
        }
      }
      else if (strcmp(type, "f") == 0)
      {
        std::vector<std::array<int, 3>> temp_faces;
        std::array<int, 3> face_indices;
        std::array<int, 3> face_indices2;
        std::array<int, 3> face_indices3;
        sscanf(buffer, "f %d/%d/%d %d/%d/%d %d/%d/%d", &face_indices[0], &face_indices[1], &face_indices[2], &face_indices2[0], &face_indices2[1], &face_indices2[2], &face_indices3[0], &face_indices3[1], &face_indices3[2]);
        if (sscanf(buffer, "f %d/%d/%d %d/%d/%d %d/%d/%d", &face_indices[0], &face_indices[1], &face_indices[2], &face_indices2[0], &face_indices2[1], &face_indices2[2], &face_indices3[0], &face_indices3[1], &face_indices3[2]) == 9)
        {
          for (int i = 0; i < 3; i++)
          {
            face_indices[i] -= 1;
            face_indices2[i] -= 1;
            face_indices3[i] -= 1;
          }
          temp_faces.push_back(face_indices);
          temp_faces.push_back(face_indices2);
          temp_faces.push_back(face_indices3);
          Face temp_face;
          temp_face.vertices = temp_faces;
          out_faces.push_back(temp_face);
        }
      }
    }
  }
  out_vertices = std::move(temp_vertices);

  obj.close();
  return true;
}

std::vector<Vector3d> setupVertexArray(const std::vector<Vector3d> &vertexes, const std::vector<Face> &facesVector){
  std::vector<Vector3d> vertexArray;

  for(Face face: facesVector){
    for(std::array<int, 3> arr: face.vertices){
      Vector3d vertex = vertexes[arr[0]];
      vertexArray.push_back(vertex);
    }
  }

  return vertexArray;
}

void setup()
{
  Serial.begin(115200);
  digitalWrite(15, HIGH);
  digitalWrite(5, HIGH);
  tft.begin();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);
  SCREEN_WIDTH = tft.getViewportX();
  SCREEN_HEIGHT = tft.getViewportY();

  if (!SD.begin(5))
  {
    Serial.println("Montaje de Tarjeta SD Fallido");
    return;
  }
  uint8_t cardType = SD.cardType();

  if (cardType == CARD_NONE)
  {
    Serial.println("No has insertado ninguna Tarjeta SD");
    return;
  }

  Serial.print("Tipo de Tarjeta SD: ");
  if (cardType == CARD_MMC)
  {
    Serial.println("MMC");
  }
  else if (cardType == CARD_SD)
  {
    Serial.println("SDSC");
  }
  else if (cardType == CARD_SDHC)
  {
    Serial.println("SDHC");
  }
  else
  {
    Serial.println("FORMATO DE TARJETA DESCONOCIDO");
  }

  uint64_t cardSize = SD.cardSize() / (1024 * 1024);
  Serial.printf("Tamaño de Tarjeta SD: %lluMB\n", cardSize);

  Serial.println("Inicialización de SD completa!");

  tft.println("Leyendo tarjeta SD...");

  loadOBJ("/cube.obj", vertices, faces);

  tft.fillScreen(TFT_BLACK);

  root = SD.open("/");

  printDirectory(root, 0);

  Serial.println("Hecho! :D");
}

void loop()
{
  setCurrentColorBuffer(Color(0,255,0));
  const std::vector<Vector3d> vertexArray = setupVertexArray(vertices, faces);
  for(int i = 0; i < vertexArray.size(); i = i+3){
    triangleBuffer(vertexArray[i]*30 , vertexArray[i+1]*30, vertexArray[i+2]*30);
  }
}

void printDirectory(File dir, int numTabs)
{
  while (true)
  {

    File entry = dir.openNextFile();
    if (!entry)
    {
      break;
    }
    for (uint8_t i = 0; i < numTabs; i++)
    {
      Serial.print('\t');
    }
    Serial.print(entry.name());
    if (entry.isDirectory())
    {
      Serial.println("/");
      printDirectory(entry, numTabs + 1);
    }
    else
    {
      Serial.print("\t\tBytes: ");
      Serial.println(entry.size(), DEC);
    }
    entry.close();
  }
}