#ifndef SCENE_CONFIG_H
#define SCENE_CONFIG_H

#include <memory>

#include "../common/camera.h"

using std::shared_ptr;

class scene_config {
   public:
    double aspect_ratio;
    shared_ptr<camera> cam;

   public:
    scene_config();
    ~scene_config();
};

scene_config::scene_config() {}
scene_config::~scene_config() {}

#endif