#include "util.h"

void rotate_canvas(lv_obj_t *canvas, int rotation) {
    static uint8_t
        buffer[LV_CANVAS_BUF_SIZE(BUFFER_SIZE, BUFFER_SIZE, 1, LV_DRAW_BUF_STRIDE_ALIGN)];

    lv_image_dsc_t *img_src = lv_canvas_get_image(canvas);
    memcpy(buffer, img_src->data, sizeof(buffer));

    lv_image_dsc_t img;
    img.data = buffer;
    img.header.cf = img_src->header.cf;
    img.header.w = img_src->header.w;
    img.header.h = img_src->header.h;

    // lv_canvas_fill_bg(canvas, COLOR_BACKGROUND, LV_OPA_COVER);

    lv_layer_t layer;
    lv_canvas_init_layer(canvas, &layer);

    lv_draw_image_dsc_t img_dsc;
    lv_draw_image_dsc_init(&img_dsc);
    img_dsc.rotation = rotation;
    img_dsc.src = &img;
    img_dsc.pivot.x = BUFFER_SIZE / 2;
    img_dsc.pivot.y = BUFFER_SIZE / 2;
    // img_dsc.pivot.x = 0;
    // img_dsc.pivot.y = 0;

    lv_area_t coords;
    lv_obj_get_coords(canvas, &coords);
    lv_draw_image(&layer, &img_dsc, &coords);

    lv_canvas_finish_layer(canvas, &layer);
}
