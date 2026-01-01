#include <string.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zmk/display.h>
#include <zmk/display/widgets/layer_status.h>
#include <zmk/endpoints.h>
#include <zmk/event_manager.h>
#include <zmk/events/layer_state_changed.h>
#include <zmk/keymap.h>

#include "../assets/fonts/custom_fonts.h"
#include "util.h"

static sys_slist_t widgets = SYS_SLIST_STATIC_INIT(&widgets);

struct layer_status_state {
    uint8_t index;
    const char *label;
};

static void update_layer_name(lv_obj_t *canvas, struct layer_status_state state) {
    char text[13] = {};
    if (state.label == NULL) {
        sprintf(text, "%i", state.index);
    } else {
        snprintf(text, sizeof(text), "%s", state.label);
    }

    lv_canvas_fill_bg(canvas, COLOR_BACKGROUND, LV_OPA_COVER);

    lv_layer_t layer;
    lv_canvas_init_layer(canvas, &layer);

    lv_draw_label_dsc_t dsc;
    lv_draw_label_dsc_init(&dsc);
    dsc.color = COLOR_FOREGROUND;
    dsc.font = &pixel_operator_mono;
    dsc.text = text;

    lv_area_t coords = {0, 0, BUFFER_SIZE - 1, BUFFER_SIZE - 1};
    lv_draw_label(&layer, &dsc, &coords);
    lv_canvas_finish_layer(canvas, &layer);
}

static void layer_status_update_cb(struct layer_status_state state) {
    struct zmk_widget_layer_status *widget;
    SYS_SLIST_FOR_EACH_CONTAINER(&widgets, widget, node) { update_layer_name(widget->obj, state); }
}

static struct layer_status_state layer_status_get_state(const zmk_event_t *eh) {
    uint8_t index = zmk_keymap_highest_layer_active();
    return (struct layer_status_state){.index = index, .label = zmk_keymap_layer_name(index)};
}

ZMK_DISPLAY_WIDGET_LISTENER(widget_layer_status, struct layer_status_state, layer_status_update_cb,
                            layer_status_get_state)
ZMK_SUBSCRIPTION(widget_layer_status, zmk_layer_state_changed);

static uint8_t draw_buf[LV_CANVAS_BUF_SIZE(SCREEN_WIDTH, SCREEN_HEIGHT, LV_COLOR_FORMAT_I1,
                                           LV_DRAW_BUF_STRIDE_ALIGN)];

int zmk_widget_layer_status_init(struct zmk_widget_layer_status *widget, lv_obj_t *parent) {
    LV_DRAW_BUF_DEFINE_STATIC(draw_buf, BUFFER_SIZE, BUFFER_SIZE, LV_COLOR_FORMAT_NATIVE);
    LV_DRAW_BUF_INIT_STATIC(draw_buf);

    widget->obj = lv_canvas_create(parent);
    lv_canvas_set_draw_buf(widget->obj, &draw_buf);
    lv_obj_center(widget->obj);

    lv_canvas_set_palette(widget->obj, 0, lv_color32_make(0, 0, 0, 0));
    lv_canvas_set_palette(widget->obj, 1, lv_color32_make(255, 255, 255, 255));

    sys_slist_append(&widgets, &widget->node);

    widget_layer_status_init();

    return 0;
}

lv_obj_t *zmk_widget_layer_status_obj(struct zmk_widget_layer_status *widget) {
    return widget->obj;
}