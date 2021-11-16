#ifndef COLOR_H
#define COLOR_H
#include <iostream>

#include "vec3.h"

using color = vec3;  // RGB color

// 输出一行颜色值 "R G B"
void write_color(std::ostream &out, color pixel_color, int spp);

#endif