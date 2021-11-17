#ifndef SCENE_MODEL_H
#define SCENE_MODEL_H

#include "../object/hittable_list.h"
#include "scene_config.h"

hittable_list basis_scene1(shared_ptr<scene_config> config);
hittable_list random_scene1(shared_ptr<scene_config> config);

#endif