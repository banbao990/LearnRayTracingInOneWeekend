#ifndef BVH_NODE_H
#define BVH_NODE_H

#include "hittable.h"
#include "hittable_list.h"

class bvh_node : public hittable {
private:
  aabb box;
  // 这个神奇的设计, 子结点不是 bvh_node, 而是 hittable
  shared_ptr<hittable> left, right;

public:
  bvh_node();
  // TODO 构建 BVH 的不同方式
  // 在构造函数中生成 bvh
  bvh_node(const hittable_list list, double time0, double time1);
  // 在构造函数中生成 bvh
  // [start, end)
  bvh_node(const std::vector<shared_ptr<hittable>> src_object, size_t start,
           size_t end, double time0, double time1);
  ~bvh_node();

  // 主要返回是否击中物体, rec 保存的纪录有效吗
  virtual bool hit(const ray &r, double t_min, double t_max,
                   hit_record &rec) const override;
  virtual bool bounding_box(double time0, double time1,
                            aabb &output_box) const override;
};

#endif