#include <toyrender/object/aabb.h>

#include <cmath>

aabb::aabb() {}
aabb::aabb(point3 _min, point3 _max) : mininum(_min), maxinum(_max) {}
aabb::~aabb() {}

aabb aabb::operator+(const aabb& box) const {
    point3 small(fmin(mininum[0], box.mininum[0]),
                 fmin(mininum[1], box.mininum[1]),
                 fmin(mininum[2], box.mininum[2]));
    point3 big(fmin(maxinum[0], box.maxinum[0]),
               fmin(maxinum[1], box.maxinum[1]),
               fmin(maxinum[2], box.maxinum[2]));
    return aabb(small, big);
}

aabb& aabb::operator+=(const aabb& box) {
    point3 small(fmin(mininum[0], box.mininum[0]),
                 fmin(mininum[1], box.mininum[1]),
                 fmin(mininum[2], box.mininum[2]));
    point3 big(fmin(maxinum[0], box.maxinum[0]),
               fmin(maxinum[1], box.maxinum[1]),
               fmin(maxinum[2], box.maxinum[2]));
    mininum = small;
    maxinum = big;
    return *this;
}

point3 aabb::get_min() const { return mininum; }
point3 aabb::get_max() const { return maxinum; }

bool aabb::hit(const ray& r, double t_min, double t_max) const {
    point3 ori = r.get_origin();
    point3 dir = r.get_direction();
    for (int dim = 0; dim < 3; ++dim) {
        // 乘法比除法快
        double invD = 1.0 / dir[dim];
        double t0 = (mininum[dim] - ori[dim]) * invD;
        double t1 = (maxinum[dim] - ori[dim]) * invD;
        if (invD < 0.0) {
            std::swap(t0, t1);
        }
        // 更新 t_min, t_max
        t_min = t0 < t_min ? t0 : t_min;
        t_max = t1 > t_max ? t1 : t_max;
        if (t_min >= t_max) {
            return false;
        }
    }
    return true;
}