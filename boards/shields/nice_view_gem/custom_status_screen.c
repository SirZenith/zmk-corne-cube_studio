#include <zephyr/logging/log.h>
#include <zmk/display/widgets/layer_status.h>

#include "assets/fonts/custom_fonts.h"
#include "widgets/animation.h"
#include "widgets/image.h"
#include "widgets/util.h"

#if IS_ENABLED(CONFIG_NICE_VIEW_GEM_INFO_CENTRAL)
static struct zmk_widget_animation w_animation;
static struct zmk_widget_layer_status w_layer_status;
static struct zmk_widget_image w_image;

void init_central_screen_info(lv_obj_t *screen) {
    zmk_widget_layer_status_init(&w_layer_status, screen);
    lv_obj_align(zmk_widget_layer_status_obj(&w_layer_status), LV_ALIGN_TOP_RIGHT, 0, 0);

    // zmk_widget_image_init(&w_image, screen);
    // lv_obj_align(zmk_widget_image_obj(&w_image), LV_ALIGN_TOP_RIGHT, 0, 0);

    zmk_widget_animation_init(&w_animation, screen);
    lv_obj_align(zmk_widget_animation_obj(&w_animation), LV_ALIGN_TOP_LEFT, 36, 0);
}
#elif IS_ENABLED(CONFIG_NICE_VIEW_GEM_INFO_PERIPHERAL)
static struct zmk_widget_animation w_animation;

void init_peripheral_screen_info(lv_obj_t *screen) {
    zmk_widget_animation_init(&w_animation, screen);
    lv_obj_align(zmk_widget_animation_obj(&w_animation), LV_ALIGN_TOP_LEFT, 36, 0);
}
#endif

lv_style_t global_style;

void init_screen(lv_obj_t *screen) {
    lv_style_init(&global_style);
    lv_style_set_bg_color(&global_style, COLOR_BACKGROUND);
    lv_style_set_bg_opa(&global_style, LV_OPA_COVER);
    lv_style_set_text_color(&global_style, COLOR_FOREGROUND);
    lv_style_set_text_font(&global_style, &pixel_operator_mono);
    lv_style_set_text_letter_space(&global_style, 1);
    lv_style_set_text_line_space(&global_style, 1);
    lv_obj_add_style(screen, &global_style, LV_PART_MAIN);

#if IS_ENABLED(CONFIG_NICE_VIEW_GEM_INFO_CENTRAL)
    init_central_screen_info(screen);
#elif IS_ENABLED(CONFIG_NICE_VIEW_GEM_INFO_PERIPHERAL)
    init_peripheral_screen_info(screen);
#endif
}

lv_obj_t *zmk_display_status_screen() {
    lv_obj_t *screen;
    screen = lv_obj_create(NULL);

#if IS_ENABLED(CONFIG_ZMK_DISPLAY)
    init_screen(screen);
#endif

    return screen;
}
