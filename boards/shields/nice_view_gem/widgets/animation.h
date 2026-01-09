#pragma once

#include <lvgl.h>

#if IS_ENABLED(CONFIG_NICE_VIEW_GEM_ANIMATION)
#define WALLPAPER_OFFSET 36
#else
#define WALLPAPER_OFFSET 0
#endif

struct zmk_widget_animation {
    sys_snode_t node;
    lv_obj_t *obj;
};

int zmk_widget_animation_init(struct zmk_widget_animation *widget, lv_obj_t *parent);
lv_obj_t *zmk_widget_animation_obj(struct zmk_widget_animation *widget);
