#include "Color.h"

RGB::RGB()
    : B(0)
    , G(0)
    , R(0)
{
}

RGB::RGB(const uint32_t raw)
{
    B = raw & 0xFF;
    G = (raw >> 8) & 0xFF;
    R = (raw >> 16) & 0xFF;
}

RGB::RGB(const Color rgb)
{
    B = rgb & 0xFF;
    G = (rgb >> 8) & 0xFF;
    R = (rgb >> 16) & 0xFF;
}

RGB::RGB(const uint8_t r, const uint8_t g, const uint8_t b)
    : B(b)
    , G(g)
    , R(r)
{
}

RGB::operator uint32_t() const
{
    uint32_t v = 0;
    v |= B;
    v |= G << 8;
    v |= R << 16;
    v |= 0xFF << 24;

    return v;
}

RGB operator*(const float l, const RGB& r)
{
    RGB c;
    c.B = r.B * l;
    c.G = r.G * l;
    c.R = r.R * l;

    return c;
}

RGB operator*(const RGB& r, const float l)
{
    return operator*(l, r);
}

RGB operator+(const RGB& l, const RGB& r)
{
    RGB c;
    c.B = l.B + r.B;
    c.G = l.G + r.G;
    c.R = l.R + r.R;

    return c;
}

RGB operator-(const RGB& l, const RGB& r)
{
    RGB c;
    c.B = l.B - r.B;
    c.G = l.G - r.G;
    c.R = l.R - r.R;

    return c;
}

ARGB::ARGB()
    : B(0)
    , G(0)
    , R(0)
    , A(255)
{
}

ARGB::ARGB(const RGB& rgb)
    : B(rgb.B)
    , G(rgb.G)
    , R(rgb.R)
    , A(255)
{
}

ARGB::ARGB(const Color argb)
    : Raw(argb)
{
}

ARGB::ARGB(const uint8_t a, const uint8_t r, const uint8_t g, const uint8_t b)
    : B(b)
    , G(g)
    , R(r)
    , A(a)
{
}

ARGB::ARGB(const uint8_t r, const uint8_t g, const uint8_t b)
    : B(b)
    , G(g)
    , R(r)
    , A(255)
{
}

ARGB operator*(const float l, const ARGB& r)
{
    ARGB c;
    c.B = r.B * l;
    c.G = r.G * l;
    c.R = r.R * l;

    return c;
}

ARGB operator*(const ARGB& l, const float r)
{
    return operator*(r, l);
}

ARGB operator+(const ARGB& l, const ARGB& r)
{
    ARGB c;
    c.A = l.A + r.A;
    c.B = l.B + r.B;
    c.G = l.G + r.G;
    c.R = l.R + r.R;

    return c;
}

ARGB operator-(const ARGB& l, const ARGB& r)
{
    ARGB c;
    c.A = l.A - r.A;
    c.B = l.B - r.B;
    c.G = l.G - r.G;
    c.R = l.R - r.R;

    return c;
}