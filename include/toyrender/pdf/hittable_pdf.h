#ifndef HITTABLE_PDF_H
#define HITTABLE_PDF_H

#include "../object/hittable.h"
#include "../utils/h_help.h"
#include "../utils/rtweekend.h"
#include "pdf.h"

class hittable_pdf : public pdf {
public:
  hittable_pdf(shared_ptr<hittable> _ptr, const point3 &_origin);
  ~hittable_pdf();
  virtual vec3 generate() const override;
  virtual double value(const vec3 &direction) const override;

public:
  shared_ptr<hittable> ptr;
  point3 origin;
};

#endif