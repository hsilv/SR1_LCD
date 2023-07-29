#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <vector>
#include <iostream>
#include "vertex3.h"
#include "color.h"

extern Color clearColor;
extern Color currentColor;

void clearBuffer();
void pointBuffer(const Vertex3& vertex, size_t width, size_t height);
void setClearColorBuffer(Color newColor);
void setCurrentColorBuffer(Color newColor);

#endif  // FRAMEBUFFER_H