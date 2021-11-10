#ifndef SHAPE_H
#define SHAPE_H

#include "ray.hpp"

class shape {
   public:
    virtual double hit(const ray& r) const = 0;
};

#endif