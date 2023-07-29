#include <iostream>
#include <sstream>
#include <iomanip>
#include <cstdint>

class Color
{
public:
    Color() : r(0), g(0), b(0) {}
    Color(uint8_t red, uint8_t green, uint8_t blue) : r(red), g(green), b(blue) {}

    uint8_t &getBlue()
    {
        return b;
    }

    const uint8_t &getBlue() const
    {
        return b;
    }

    uint8_t &getGreen()
    {
        return g;
    }

    const uint8_t &getGreen() const
    {
        return g;
    }

    uint8_t &getRed()
    {
        return r;
    }

    const uint8_t &getRed() const
    {
        return r;
    }

    Color operator+(const Color &other) const
    {
        return Color(static_cast<uint8_t>(r + other.r), static_cast<uint8_t>(g + other.g), static_cast<uint8_t>(b + other.b));
    }

    Color operator*(float scalar) const
    {
        return Color(static_cast<uint8_t>(r * scalar), static_cast<uint8_t>(g * scalar), static_cast<uint8_t>(b * scalar));
    }

    friend std::ostream &operator<<(std::ostream &os, const Color &color)
    {
        os << "\033[1;97mColor ->\033[0m ";
        os << "\033[1;31mR:" << static_cast<int>(color.r) << "\033[0m, ";
        os << "\033[1;32mG:" << static_cast<int>(color.g) << "\033[0m, ";
        os << "\033[1;34mB:" << static_cast<int>(color.b) << "\033[0m";
        return os;
    }

    // Método para convertir el color a formato hexadecimal
    uint16_t toHex() const
    {
        return ((r & 0x1F) << 11) | ((g & 0x3F) << 5) | (b & 0x1F);
    }

    // Método para leer un color en formato hexadecimal y actualizar los componentes de la clase
    void fromHex(uint32_t hexColor)
    {
        r = (hexColor >> 16) & 0xFF;
        g = (hexColor >> 8) & 0xFF;
        b = hexColor & 0xFF;
    }

private:
    uint8_t r, g, b;
};