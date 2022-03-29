#ifndef PDF_H
#define PDF_H

#include "../common/vec3.h"

class pdf {
   public:
    pdf() {}
    ~pdf() {}

    // 按照给定的 pdf 返回一个方向
    virtual vec3 generate() const = 0;

    // 返回 pdf(direction)
    virtual double value(const vec3& direction) const = 0;
};

#endif