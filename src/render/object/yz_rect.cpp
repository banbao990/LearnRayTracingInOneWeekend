#include <toyrender/object/yz_rect.h>

yz_rect::yz_rect() {}
yz_rect::yz_rect(double _y0,
                 double _y1,
                 double _z0,
                 double _z1,
                 double _k,
                 shared_ptr<material> mat)
    : y0(_y0), y1(_y1), z0(_z0), z1(_z1), k(_k), mat_ptr(mat) {}
yz_rect::yz_rect::~yz_rect() {}

bool yz_rect::hit(const ray& r,
                  double t_min,
                  double t_max,
                  hit_record& rec) const {
    // 求出和 x=k 平面的交点
    // 可能是 inf
    // 0.0/0.0, nan(任意比较都返回 false)
    double t = (k - r.get_origin().x()) / r.get_direction().x();
    if (t < t_min || t > t_max) {
        return false;
    }

    double y = r.get_origin().y() + t * r.get_direction().y();
    double z = r.get_origin().z() + t * r.get_direction().z();

    // 边界上、边界外都不算相交
    if (y <= y0 || y >= y1 || z <= z0 || z >= z1) {
        return false;
    }

    // 击中, 保存 hit_record
    rec.u = (y - y0) / (y1 - y0);
    rec.v = (z - z0) / (z1 - z0);
    rec.t = t;
    vec3 outward_normal(1.0, 0, 0);
    rec.set_face_normal(r, outward_normal);
    rec.mat_ptr = mat_ptr;
    rec.p = r.at(t);

    return true;
}

bool yz_rect::bounding_box(double time0, double time1, aabb& output_box) const {
    // 在 x 方向上增加一段小的包围
    output_box = aabb(point3(k - 1e-4, y0, z0), point3(k + 1e-4, y1, z1));
    return true;
}
