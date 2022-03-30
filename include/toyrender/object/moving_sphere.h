#ifndef MOVING_SPHERE_H
#define MOVING_SPHERE_H

#include "aabb.h"
#include "hittable.h"

class moving_sphere : public hittable {
private:
  point3 center1, center2;
  double time1, time2;
  double radius;
  shared_ptr<material> mat_ptr;

public:
  moving_sphere(point3 _center1, point3 _center2, double _time1, double _time2,
                double _radius, shared_ptr<material> _matrial_ptr);
  ~moving_sphere();

  point3 get_center(double t) const;

  virtual bool hit(const ray &r, double t_min, double t_max,
                   hit_record &rec) const override;

  virtual bool bounding_box(double time0, double time1,
                            aabb &output_box) const override;
};

#endif