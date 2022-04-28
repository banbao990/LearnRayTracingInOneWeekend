#ifndef SCENE_MODEL_H
#define SCENE_MODEL_H

#include "../object/hittable_list.h"
#include "scene_config.h"

// 一些默认参数的设置
// void scene_deault_setting(shared_ptr<scene_config>& config);

//
// 无光源, 使用背景光
//

void basis_scene1(shared_ptr<scene_config> &config);
void random_scene1(shared_ptr<scene_config> &config);
void two_spheres(shared_ptr<scene_config> &config);
void two_perlin_spheres(shared_ptr<scene_config> &config);
void earth(shared_ptr<scene_config> &config);

//
// 光源, 背景漆黑
//

void simple_light(shared_ptr<scene_config> &config);
void simple_light2(shared_ptr<scene_config> &config);
void cornell_box_origin(shared_ptr<scene_config> &config);
void cornell_box(shared_ptr<scene_config> &config);
void cornell_box_specular(shared_ptr<scene_config> &config);
void cornell_box_smoke(shared_ptr<scene_config> &config);
void rtnw_final_scene(shared_ptr<scene_config> &config);

void toy_scene1(shared_ptr<scene_config> &config);

#endif