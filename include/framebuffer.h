#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <vector>
#include <iostream>
#include "vertex2.h"
#include "color.h"

extern Color clearColor;
extern Color currentColor;

void clear();
void point(const Vertex2& vertex, size_t width, size_t height);
void setClearColor(Color newColor);
void setCurrentColor(Color newColor);

#endif  // FRAMEBUFFER_H