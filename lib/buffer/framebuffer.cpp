#include <iostream>
#include <vector>
#include <cmath>
#include <SPI.h>
#include <TFT_eSPI.h>
#include "framebuffer.h"

#include <ArduinoEigenDense.h>

using namespace Eigen;


Color clearColor(0, 0, 0); // Color base o por defecto del framebuffer
Color currentColor(0, 0, 0);

TFT_eSPI tft = TFT_eSPI();

void setClearColorBuffer(Color newColor)
{
    clearColor = newColor;
}

void setCurrentColorBuffer(Color newColor)
{
    currentColor = newColor;
}

// Función para llenar el framebuffer con el clearColor
void clearBuffer()
{
    tft.fillScreen(clearColor.toHex());
}

void pointBuffer(const Vertex3& vertex)
{
    // Redondear las coordenadas x, y, y z a enteros
    int x = static_cast<int>(vertex.x);
    int y = static_cast<int>(vertex.y);
    int z = static_cast<int>(vertex.z);

    // Verificar si las coordenadas x e y están dentro del rango del framebuffer
    if (x >= 0 && x < static_cast<int>(tft.width()) && y >= 0 && y < static_cast<int>(tft.height()))
    {
        tft.drawPixel(x, y, currentColor.toHex());
    }
}

void lineBuffer(Vector3d start, Vector3d end) {
    int x0 = start.x();
    int y0 = start.y();
    int x1 = end.x();
    int y1 = end.y();

    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;

    if (dx > dy) {
        int err = dx / 2;
        while (x0 != x1) {
            pointBuffer(Vertex3(x0, y0, 0)); // Llamar a la función pixel para dibujar un píxel en (x0, y0)
            if (x0 == x1 && y0 == y1) break;
            int e2 = err;
            if (e2 > -dx) { err -= dy; x0 += sx; }
            if (e2 < dy) { err += dx; y0 += sy; }
        }
    } else {
        int err = dy / 2;
        while (y0 != y1) {
            pointBuffer(Vertex3(x0, y0, 0));  // Llamar a la función pixel para dibujar un píxel en (x0, y0)
            if (x0 == x1 && y0 == y1) break;
            int e2 = err;
            if (e2 > -dy) { err -= dx; y0 += sy; }
            if (e2 < dx) { err += dy; x0 += sx; }
        }
    }
}

void triangleBuffer(Vector3d A, Vector3d B, Vector3d C){
    lineBuffer(A, B);
    lineBuffer(B, C);
    lineBuffer(C, A);
}