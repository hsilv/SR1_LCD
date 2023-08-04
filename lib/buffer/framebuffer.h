#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <vector>
#include <iostream>
#include "vertex3.h"
#include "color.h"
#include <TFT_eSPI.h>

#include <ArduinoEigenDense.h>

using namespace Eigen;


extern Color clearColor;
extern Color currentColor;
extern TFT_eSPI tft;

void clearBuffer();
void pointBuffer(const Vertex3& vertex, size_t width, size_t height);
void setClearColorBuffer(Color newColor);
void setCurrentColorBuffer(Color newColor);
void lineBuffer(Vector3d start, Vector3d end);
void triangleBuffer(Vector3d A, Vector3d B, Vector3d C);
struct Face;

#endif  // FRAMEBUFFER_H