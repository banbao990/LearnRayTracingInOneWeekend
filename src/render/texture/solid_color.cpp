#include <toyrender/texture/solid_color.h>

solid_color::solid_color() {}
solid_color::solid_color(color color_value) : color_value(color_value) {}
solid_color::solid_color(double r, double g, double b) : color_value(r, g, b) {}

solid_color::~solid_color() {}

color solid_color::value(double u, double v, const point3 &p) const {
  return color_value;
}