#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include <memory>
#include <vector>

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

    virtual bool hit(const ray& r, double t_min, double t_max,
                     hit_record& rec) const override;
};

#endif