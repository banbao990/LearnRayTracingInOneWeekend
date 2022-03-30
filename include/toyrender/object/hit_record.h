#ifndef HIT_RECORD_H
#define HIT_RECORD_H

#include <memory>

#include "../common/ray.h"
#include "../common/vec3.h"
#include "../material/material.h"

class material;
using std::shared_ptr;

// 保存光线击中的点的信息
struct hit_record {
  point3 p;
  vec3 normal;
  double t;
  double u, v;     // 记录纹理位置
  bool front_face; // true: 外面往里, false: 里面往外
  shared_ptr<material> mat_ptr;

  // 设置 front_face, 判定是内部还是外部
  void set_face_normal(const ray &r, const vec3 &outward_normal);
};

#endif