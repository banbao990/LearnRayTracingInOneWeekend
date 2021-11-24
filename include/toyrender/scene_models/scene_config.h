#ifndef SCENE_CONFIG_H
#define SCENE_CONFIG_H

#include <memory>

#include "../common/camera.h"

using std::shared_ptr;

// 包含了整个场景的若干信息
// 相机位置、整个场景的信息、长宽比、背景颜色(环境光)
class scene_config {
   public:
    double aspect_ratio;
    double image_width;
    shared_ptr<camera> cam;
    shared_ptr<hittable_list> world;  // 整个场景
    color background_color;           // 默认背景色为全黑

   public:
    scene_config();
    ~scene_config();
};

scene_config::scene_config() {}
scene_config::~scene_config() {}

#endif