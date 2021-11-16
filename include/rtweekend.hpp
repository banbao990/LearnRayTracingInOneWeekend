#ifndef RTWEEKEND_H
#define RTWEEKEND_H

#include <cmath>
#include <limits>
#include <memory>
#include <random>

// !!!important!!!
// 为了防止出现循环包含导致的未定义问题, 不允许包含其他自定义头文件

// Usings

using std::make_shared;
using std::shared_ptr;
using std::sqrt;
using std::string;
using std::to_string;

// Constants

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// Utility Functions

// 角度制转弧度制
inline double degrees_to_radians(double degrees) {
    return degrees * pi / 180.0;
}

// 返回一个随机数 [0, 1)
inline double random_double() {
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static std::mt19937 generator;
    return distribution(generator);
    // return rand() / (RAND_MAX + 1.0);
}

// 返回一个随机数 [min_v, max_v)
inline double random_double(double min_v, double max_v) {
    return min_v + (max_v - min_v) * random_double();
}

// 将 v 截断到 [min_v, max_v]
inline double clamp(double v, double min_v, double max_v) {
    if (v < min_v) {
        return min_v;
    }
    if (v > max_v) {
        return max_v;
    }
    return v;
}

// 返回一个数字(a)字符串表示形式, 不够左边补字符指定字符(c), 太多了则直接返回(不截断)
// TODO 不声明为 inline 会出现重复包含的问题
inline string left_append(int a, int num = 2, char c = '0') {
    string str = to_string(a);
    int len = str.length();
    if (len < num) {
        str = string(num - len, c) + str;
    }
    return str;
}

#endif