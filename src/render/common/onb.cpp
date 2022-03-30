#include <toyrender/common/onb.h>
#include <toyrender/utils/rtweekend.h>

onb::onb() {}

inline vec3 onb::operator[](int i) const { return axis[i]; }

vec3 onb::u() const { return axis[0]; }
vec3 onb::v() const { return axis[1]; }
vec3 onb::w() const { return axis[2]; }

// 局部坐标转化为世界坐标
vec3 onb::local(double a, double b, double c) const {
  return a * u() + b * v() + c * w();
}

// 局部坐标转化为世界坐标
vec3 onb::local(const vec3 &a) const {
  return a.x() * u() + a.y() * v() + a.z() * w();
}

void onb::build_from_w(const vec3 &n) {
  axis[2] = n.unit_vector();
  vec3 a = (fabs(w().x()) > 0.9) ? vec3(0, 1, 0) : vec3(1, 0, 0);
  axis[1] = w().cross(a).unit_vector();
  axis[0] = w().cross(v());
}