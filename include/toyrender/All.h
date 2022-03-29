#ifndef _B_ALL_H_B_
#define _B_ALL_H_B_

#include "common/camera.h"
#include "common/color.h"
#include "common/onb.h"
#include "common/ray.h"
#include "common/vec3.h"
#include "material/dielectric.h"
#include "material/diffuse_light.h"
#include "material/isotropic.h"
#include "material/lambertian.h"
#include "material/material.h"
#include "material/metal.h"
#include "object/aabb.h"
#include "object/box.h"
#include "object/box_compare.h"
#include "object/bvh_node.h"
#include "object/constant_medium.h"
#include "object/flip_face.h"
#include "object/hit_record.h"
#include "object/hittable.h"
#include "object/hittable_list.h"
#include "object/moving_sphere.h"
#include "object/rotate_y.h"
#include "object/sphere.h"
#include "object/translate.h"
#include "object/xy_rect.h"
#include "object/xz_rect.h"
#include "object/yz_rect.h"
#include "pdf/cosine_pdf.h"
#include "pdf/hittable_pdf.h"
#include "pdf/mixture_pdf.h"
#include "pdf/pdf.h"
#include "scene_models/scene_config.h"
#include "scene_models/scene_model.h"
#include "texture/checker_texture.h"
#include "texture/image_texture.h"
#include "texture/perlin.h"
#include "texture/perlin_noise_texture.h"
#include "texture/solid_color.h"
#include "texture/texture.h"
#include "utils/h_help.h"
#include "utils/rtw_stb_image.h"
// #include "utils/rtweekend.h"

#endif