
#include "my_gfx.h"

/**
 * @brief         
 * 
 * @param gfx     annotation
 * @param w       annotation
 * @param h       annotation
 */
void MyGFX_init(My_GFX *gfx, int16_t w, int16_t h) {
    uint32_t size = sizeof(pixel_t) * w * h;
    if (gfx->buffer = (pixel_t *) malloc(size)) {
        memset(gfx->buffer, 0, size);

        gfx->width = w;
        gfx->height = h;
    }
}

void MyGFX_deinit(My_GFX *gfx) {
    if (gfx->buffer) {
        free(gfx);
    }
}

void MyGFX_draw_pixel(My_GFX *gfx, uint16_t x, uint16_t y, pixel_t color) {
    if (gfx->buffer) {
        if ((x >= gfx->width) || (y >= gfx->height)) {
            return;
        }

        gfx->buffer[x + y * gfx->width] = color;
    }
}

void MyGFX_fill_screen(My_GFX *gfx, pixel_t color) {
    if (gfx->buffer) {
        uint32_t i;
        uint32_t num = gfx->height * gfx->width;

        for (i = 0; i < num; i++) {
            gfx->buffer[i] = color;
        }
    }
}

void MyGFX_draw_vline(My_GFX *gfx, uint16_t x, uint16_t y, uint16_t h, pixel_t color) {
    if ((x >= gfx->width) || (y >= gfx->height) || )
}