#ifndef XZ_RECT_H
#define XZ_RECT_H

#include "hittable.h"

// xy 平面长方形
class xz_rect : public hittable {
private:
  shared_ptr<material> mat_ptr;
  double x0, x1, z0, z1, k; // y = k

public:
  xz_rect();
  xz_rect(double _x0, double _x1, double _z0, double _z1, double _k,
          shared_ptr<material> mat);
  ~xz_rect();

  virtual bool hit(const ray &r, double t_min, double t_max,
                   hit_record &rec) const override;
  virtual bool bounding_box(double time0, double time1,
                            aabb &output_box) const override;

  virtual vec3 random(const vec3 &origin) const override;
  virtual double pdf_value(const point3 &origin,
                           const vec3 &direction) const override;
};

#endif