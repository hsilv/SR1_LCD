#include <iostream>
#include <vector>
#include <cmath>
#include <SPI.h>
#include <TFT_eSPI.h>
#include "framebuffer.h"

TFT_eSPI tft = TFT_eSPI();

Color clearColor(0, 0, 0); // Color base o por defecto del framebuffer
Color currentColor(0, 0, 0);

void setClearColor(Color newColor)
{
    clearColor = newColor;
}

void setCurrentColor(Color newColor)
{
    currentColor = newColor;
}

// Función para llenar el framebuffer con el clearColor
void clear()
{
    tft.fillScreen(clearColor.toHex());
}

void point(const Vertex2 &vertex, size_t width, size_t height)
{
    // Redondear las coordenadas a enteros
    int x = static_cast<int>(vertex.x);
    int y = static_cast<int>(vertex.y);

    // Verificar si las coordenadas están dentro del rango del framebuffer
    if (x >= 0 && x < static_cast<int>(width) && y >= 0 && y < static_cast<int>(height))
    {
        tft.drawPixel(x, y, currentColor.toHex());
    }
}

void drawLine(int x0, int y0, int x1, int y1, size_t width, size_t height)
{
    int dx = std::abs(x1 - x0);
    int dy = std::abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;

    while (true)
    {
        point(Vertex2(x0, y0), width, height);
        if (x0 == x1 && y0 == y1)
            break;

        int e2 = 2 * err;
        if (e2 > -dy)
        {
            err -= dy;
            x0 += sx;
        }

        if (e2 < dx)
        {
            err += dx;
            y0 += sy;
        }
    }
}