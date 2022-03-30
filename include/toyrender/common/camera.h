#ifndef CAMERA_H
#define CAMERA_H

#include "ray.h"
#include "vec3.h"

// 相机类
class camera {
private:
  double aspect_ratio;
  point3 origin;
  vec3 horizontal;
  vec3 vertical;
  point3 lower_left_corner;
  vec3 u, v, w;
  double lens_radius;
  double time1, time2; // 快门开闭的时间(time1-time2之间接受光线)

public:
  camera();
  camera(double _vfov, double _aspect_ratio);
  // _vfov: vertical field-of-view(角度制)
  // _aperture=0: 光圈
  // _focus_distance=1: 最近成像距离(像距)
  camera(double _vfov, double _aspect_ratio, point3 _lookfrom, point3 _lookat,
         vec3 _vup, double _aperture = 0, double _focus_distance = 1,
         double _time1 = 0, double _time2 = 0);
  ~camera();
  ray get_ray(double _u, double _v) const;
};

#endif