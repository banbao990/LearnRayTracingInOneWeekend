#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include <memory>
#include <vector>

#include "aabb.h"
#include "hittable.h"

using std::shared_ptr;

// 场景中物体的链表
class hittable_list : public hittable {
private:
  std::vector<shared_ptr<hittable>> objects;

public:
  hittable_list();
  hittable_list(shared_ptr<hittable> obj);
  ~hittable_list();

  void clear();
  void add(shared_ptr<hittable> obj);
  // 获取 objects, 返回了一个复制品
  std::vector<shared_ptr<hittable>> get_objects() const;
  // 获取 objects 的个数
  int get_count() const;

  virtual bool hit(const ray &r, double t_min, double t_max,
                   hit_record &rec) const override;
  virtual bool bounding_box(double time0, double time1,
                            aabb &output_box) const override;

  // PDF
  virtual vec3 random(const point3 &origin) const override;
  virtual double pdf_value(const point3 &origin,
                           const vec3 &direction) const override;
};

#endif