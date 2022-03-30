#ifndef XY_RECT_H
#define XY_RECT_H

#include "hittable.h"

// xy 平面长方形
class xy_rect : public hittable {
private:
  shared_ptr<material> mat_ptr;
  double x0, x1, y0, y1, k; // z = k

public:
  xy_rect();
  xy_rect(double _x0, double _x1, double _y0, double _y1, double _k,
          shared_ptr<material> mat);
  ~xy_rect();

  virtual bool hit(const ray &r, double t_min, double t_max,
                   hit_record &rec) const override;
  virtual bool bounding_box(double time0, double time1,
                            aabb &output_box) const override;
};

#endif