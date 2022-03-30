#ifndef YZ_RECT_H
#define YZ_RECT_H

#include "hittable.h"

// yz 平面长方形
class yz_rect : public hittable {
private:
  shared_ptr<material> mat_ptr;
  double y0, y1, z0, z1, k; // x = k

public:
  yz_rect();
  yz_rect(double _y0, double _y1, double _z0, double _z1, double _k,
          shared_ptr<material> mat);
  ~yz_rect();

  virtual bool hit(const ray &r, double t_min, double t_max,
                   hit_record &rec) const override;
  virtual bool bounding_box(double time0, double time1,
                            aabb &output_box) const override;
};

#endif