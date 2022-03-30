#include <toyrender/object/translate.h>

translate::translate() {}
translate::translate(shared_ptr<hittable> _ptr, point3 _offset)
    : ptr(_ptr), offset(_offset) {}
translate::~translate() {}

bool translate::hit(const ray &r, double t_min, double t_max,
                    hit_record &rec) const {
  ray move_r(r.get_origin() - offset, r.get_direction(), r.get_time());
  if (!ptr->hit(move_r, t_min, t_max, rec)) {
    return false;
  }

  // 需要修正位置
  rec.p += offset;
  rec.set_face_normal(move_r, rec.normal);
  return true;
}

bool translate::bounding_box(double time0, double time1,
                             aabb &output_box) const {
  if (!ptr->bounding_box(time0, time1, output_box)) {
    return false;
  }
  // 平移修正
  output_box =
      aabb(output_box.get_min() + offset, output_box.get_max() + offset);
  return true;
}