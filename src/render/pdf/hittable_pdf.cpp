#include <toyrender/pdf/hittable_pdf.h>

hittable_pdf::hittable_pdf(shared_ptr<hittable> _ptr, const point3 &_origin)
    : ptr(_ptr), origin(_origin) {}

hittable_pdf::~hittable_pdf() {}

vec3 hittable_pdf::generate() const {
  return ptr->random(origin); // 从点 origin 朝着 ptr 指向的对象进行采样
}

double hittable_pdf::value(const vec3 &direction) const {
  return ptr->pdf_value(origin, direction);
}