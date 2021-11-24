#include <toyrender/object/zx_rect.h>

zx_rect::zx_rect() {}
zx_rect::zx_rect(double _z0,
                 double _z1,
                 double _x0,
                 double _x1,
                 double _k,
                 shared_ptr<material> mat)
    : z0(_z0), z1(_z1), x0(_x0), x1(_x1), k(_k), mat_ptr(mat) {}
zx_rect::zx_rect::~zx_rect() {}

bool zx_rect::hit(const ray& r,
                  double t_min,
                  double t_max,
                  hit_record& rec) const {
    // 求出和 y=k 平面的交点
    // 可能是 inf
    // 0.0/0.0, nan(任意比较都返回 false)
    double t = (k - r.get_origin().y()) / r.get_direction().y();
    if (t < t_min || t > t_max) {
        return false;
    }

    double x = r.get_origin().x() + t * r.get_direction().x();
    double z = r.get_origin().z() + t * r.get_direction().z();

    // 边界上、边界外都不算相交
    if (z <= z0 || z >= z1 || x <= x0 || x >= x1) {
        return false;
    }

    // 击中, 保存 hit_record
    // 注意这里的纹理坐标 (z, x)
    rec.u = (z - z0) / (z1 - z0);
    rec.v = (x - x0) / (x1 - x0);
    rec.t = t;
    vec3 outward_normal(0, 1.0, 0);
    rec.set_face_normal(r, outward_normal);
    rec.mat_ptr = mat_ptr;
    rec.p = r.at(t);

    return true;
}

bool zx_rect::bounding_box(double time0, double time1, aabb& output_box) const {
    // 在 y 方向上增加一段小的包围
    output_box = aabb(point3(x0, k - 1e-4, z0), point3(x1, k + 1e-4, z1));
    return true;
}
