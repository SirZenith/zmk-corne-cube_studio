#pragma once

#include <lvgl.h>

struct zmk_widget_animation {
    sys_snode_t node;
    lv_obj_t *obj;
};

int zmk_widget_animation_init(struct zmk_widget_animation *widget, lv_obj_t *parent);
lv_obj_t *zmk_widget_animation_obj(struct zmk_widget_animation *widget);
