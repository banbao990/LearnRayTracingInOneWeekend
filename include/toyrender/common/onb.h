#ifndef OBN_H
#define OBN_H

#include "vec3.h"

class onb {
public:
  onb();
  inline vec3 operator[](int i) const;

  vec3 u() const;
  vec3 v() const;
  vec3 w() const;

  // 局部坐标转化为世界坐标
  vec3 local(double a, double b, double c) const;

  // 局部坐标转化为世界坐标
  vec3 local(const vec3 &a) const;

  // 以 n 为法向构建局部坐标系(在世界坐标系中的表示)
  void build_from_w(const vec3 &n);

public:
  vec3 axis[3];
};

#endif