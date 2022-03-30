#ifndef H_HELP_H
#define H_HELP_H
// 只会包含一些标准的库文件、自定义常量等

// Libs
#include <cmath>
#include <limits>
#include <memory>

// Usings

using std::make_shared;
using std::shared_ptr;
using std::sqrt;
using std::string;
using std::to_string;

// Constants

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;
const double pi2 = 2 * pi;
const double eps = 0.0001;

// defines
#define CHECK_OVERRIDE(class_name, function_name)                              \
  static volatile bool _maybe_false = true;                                    \
  if (_maybe_false) {                                                          \
    _maybe_false = false;                                                      \
    std::cerr << class_name << "::" << function_name                           \
              << ": It shoulde be override" << std::endl;                      \
  }

#endif