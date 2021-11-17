#ifndef SOLID_COLOR_H
#define SOLID_COLOR_H

#include "../common/color.h"
#include "texture.h"

class solid_color : public texture {
   private:
    color color_value;

   public:
    solid_color();
    solid_color(color &c);
    solid_color(double r, double g, double b);
    ~solid_color();

    virtual color value(double u, double v, const point3 &p) const override;
};

#endif