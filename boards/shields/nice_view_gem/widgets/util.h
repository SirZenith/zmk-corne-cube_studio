#pragma once

#include <lvgl.h>
#include <zmk/endpoints.h>

#define SCREEN_WIDTH 160
#define SCREEN_HEIGHT 68

#define FONT_SIZE 16

#define BUFFER_SIZE 68
#define BUFFER_OFFSET_MIDDLE -44
#define BUFFER_OFFSET_BOTTOM -129

#define COLOR_BACKGROUND                                                                           \
    IS_ENABLED(CONFIG_NICE_VIEW_WIDGET_INVERTED) ? lv_color_black() : lv_color_white()
#define COLOR_FOREGROUND                                                                           \
    IS_ENABLED(CONFIG_NICE_VIEW_WIDGET_INVERTED) ? lv_color_white() : lv_color_black()

void rotate_canvas(lv_obj_t *canvas, int rotation);
