#include <toyrender/common/vec3.h>

#include <cmath>
#include <toyrender/util/rtweekend.hpp>

// 构造函数
vec3::vec3() : e{0, 0, 0} {}
vec3::vec3(double e0, double e1, double e2) : e{e0, e1, e2} {}

// 析构函数
vec3::~vec3() {}

// 取元素
double vec3::x() const { return e[0]; }
double vec3::y() const { return e[1]; }
double vec3::z() const { return e[2]; }

// 功能函数: 自身
double vec3::length_squared() const {
    return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
}

double vec3::length() const { return sqrt(length_squared()); }

vec3 vec3::operator-() const { return vec3(-e[0], -e[1], -e[2]); }

double vec3::operator[](int i) const { return e[i]; }

double& vec3::operator[](int i) { return e[i]; }

vec3& vec3::operator+=(const vec3& v) {
    e[0] += v.e[0];
    e[1] += v.e[1];
    e[2] += v.e[2];
    return *this;
}

vec3& vec3::operator-=(const vec3& v) {
    e[0] -= v.e[0];
    e[1] -= v.e[1];
    e[2] -= v.e[2];
    return *this;
}

vec3& vec3::operator*=(const double t) {
    e[0] *= t;
    e[1] *= t;
    e[2] *= t;
    return *this;
}

vec3& vec3::operator/=(const double t) { return *this *= 1 / t; }

// 功能函数: 其他

vec3 vec3::operator+(const vec3& v) const {
    return vec3(e[0] + v.e[0], e[1] + v.e[1], e[2] + v.e[2]);
}

vec3 vec3::operator-(const vec3& v) const {
    return vec3(e[0] - v.e[0], e[1] - v.e[1], e[2] - v.e[2]);
}

vec3 vec3::operator*(const vec3& v) const {
    return vec3(e[0] * v.e[0], e[1] * v.e[1], e[2] * v.e[2]);
}

double vec3::dot(const vec3& v) const {
    return e[0] * v.e[0] + e[1] * v.e[1] + e[2] * v.e[2];
}

vec3 vec3::cross(const vec3& v) const {
    return vec3(e[1] * v.e[2] - v.e[1] * e[2], e[2] * v.e[0] - v.e[2] * e[0],
                e[0] * v.e[1] - v.e[0] * e[1]);
}

vec3 operator+(double t, const vec3& v) {
    return vec3(v.e[0] + t, v.e[1] + t, v.e[2] + t);
}

vec3 vec3::operator+(double t) const { return t + (*this); }
vec3 vec3::operator-(double t) const { return -t + (*this); }

vec3 operator*(double t, const vec3& v) {
    return vec3(v.e[0] * t, v.e[1] * t, v.e[2] * t);
}

vec3 vec3::operator*(double t) const { return t * (*this); }
vec3 vec3::operator/(double t) const { return (1 / t) * (*this); }

// TODO 没有处理 0 向量
vec3 vec3::unit_vector() const { return *this / length(); }

bool vec3::near_zero() const {
    static double _eps = 1e-8;
    return (std::fabs(e[0]) < _eps) && (std::fabs(e[1]) < _eps) &&
           (std::fabs(e[2]) < _eps);
}

std::ostream& operator<<(std::ostream& out, const vec3& v) {
    return out << '(' << v.e[0] << ", " << v.e[1] << ", " << v.e[2] << ')';
}

//
// static 函数
//

vec3 vec3::random() {
    return vec3(random_double(), random_double(), random_double());
}

vec3 vec3::random(int min_v, int max_v) {
    return vec3(random_double(min_v, max_v), random_double(min_v, max_v),
                random_double(min_v, max_v));
}

vec3 vec3::random_in_unit_sphere() {
    // 在一个正方体中采样, 判断长度是否落在球体内部
    while (true) {
        vec3 v = random(-1, 1);
        if (v.length_squared() < 1) {
            return v;
        }
    }
}

vec3 vec3::random_in_unit_sphere_to_surface() {
    return random_in_unit_sphere().unit_vector();
}

vec3 vec3::random_on_unit_sphere_surface() {
    // 如何在一个球面上均匀采样 ? 单位球上的面积(r=1)
    // dA = \sin{\theta}d{\theta}d{\phi} = \cos{\theta}d{\phi}
    // 应该是对 \phi, \cos{\theta} 均匀采样
    double phi = random_double(0, 2 * pi);
    double z = random_double(-1, 1);
    double r = std::sqrt(1 - z * z);
    return vec3(r * std::cos(phi), r * std::sin(phi), z);
}

vec3 vec3::random_in_unit_hemisphere(const vec3& normal) {
    vec3 dir = random_in_unit_sphere();
    if (normal.dot(dir) <= 0) {
        dir = -dir;
    }
    return dir;
}

vec3 vec3::random_in_unit_disk() {
    while (true) {
        vec3 p = vec3(random_double(-1, 1), random_double(-1, 1), 0);
        if (p.length_squared() < 1) {
            return p;
        }
    }
}

vec3 vec3::reflect(const vec3& ray_in, const vec3& normal) {
    return ray_in - 2 * normal.dot(ray_in) * normal;
}

vec3 vec3::refract(const vec3& ray_in, const vec3& normal,
                   double refraction_ratio) {
    double cos_theta = std::fmin(ray_in.dot(normal), 1.0);
    vec3 pers = refraction_ratio * (ray_in - cos_theta * normal);
    vec3 para = -std::sqrt(1 - pers.length_squared()) * normal;
    return pers + para;
}