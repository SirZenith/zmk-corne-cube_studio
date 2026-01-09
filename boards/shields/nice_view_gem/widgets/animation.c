#include <stdlib.h>
#include <zephyr/kernel.h>

#include "animation.h"

LV_IMG_DECLARE(crystal_01);
LV_IMG_DECLARE(crystal_02);
LV_IMG_DECLARE(crystal_03);
LV_IMG_DECLARE(crystal_04);
LV_IMG_DECLARE(crystal_05);
LV_IMG_DECLARE(crystal_06);
LV_IMG_DECLARE(crystal_07);
LV_IMG_DECLARE(crystal_08);
LV_IMG_DECLARE(crystal_09);
LV_IMG_DECLARE(crystal_10);
LV_IMG_DECLARE(crystal_11);
LV_IMG_DECLARE(crystal_12);
LV_IMG_DECLARE(crystal_13);
LV_IMG_DECLARE(crystal_14);
LV_IMG_DECLARE(crystal_15);
LV_IMG_DECLARE(crystal_16);

LV_IMG_DECLARE(wallpaper);

const lv_image_dsc_t *anim_imgs[] = {
    &crystal_01, &crystal_02, &crystal_03, &crystal_04, &crystal_05, &crystal_06,
    &crystal_07, &crystal_08, &crystal_09, &crystal_10, &crystal_11, &crystal_12,
    &crystal_13, &crystal_14, &crystal_15, &crystal_16,
};

static sys_slist_t widgets = SYS_SLIST_STATIC_INIT(&widgets);

int zmk_widget_animation_init(struct zmk_widget_animation *widget, lv_obj_t *parent) {
#if IS_ENABLED(CONFIG_NICE_VIEW_GEM_ANIMATION)
    lv_obj_t *obj = lv_animimg_create(parent);
    lv_obj_center(obj);

    lv_animimg_set_src(obj, (const void **)anim_imgs, 16);
    lv_animimg_set_duration(obj, CONFIG_NICE_VIEW_GEM_ANIMATION_MS);
    lv_animimg_set_repeat_count(obj, LV_ANIM_REPEAT_INFINITE);
    lv_animimg_start(obj);
#else
    lv_obj_t *obj = lv_img_create(parent);

    // int length = sizeof(anim_imgs) / sizeof(anim_imgs[0]);
    // srand(k_uptime_get_32());
    // int random_index = rand() % length;

    lv_img_set_src(obj, &wallpaper);
#endif

    widget->obj = obj;
    sys_slist_append(&widgets, &widget->node);

    return 0;
}

lv_obj_t *zmk_widget_animation_obj(struct zmk_widget_animation *widget) { return widget->obj; }