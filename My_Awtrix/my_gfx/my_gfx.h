



/**
 */

#ifndef _MY_GFX_H
#define _MY_GFX_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <malloc.h>

/**
 * @brief     annotation
 * 
 */
typedef struct {
    uint8_t r;
    uint8_t g;
    uint8_t b;
} pixel_t;

/**
 * @brief     annotation
 * 
 */
typedef struct {
    int16_t width;
    int16_t height;
    int16_t cursor_x;
    int16_t cursor_y;
    pixel_t* buffer;
} My_GFX;

void MyGFX_init(My_GFX *gfx, int16_t w, int16_t h);
void MyGFX_deinit(My_GFX *gfx);
void MyGFX_draw_pixel(My_GFX *gfx, uint16_t x, uint16_t y, pixel_t color);
void MyGFX_fill_screen(My_GFX *gfx, pixel_t color);
void MyGFX_draw_vline(My_GFX *gfx, uint16_t x, uint16_t y, uint16_t h, pixel_t color);
void MyGFX_draw_hline(My_GFX *gfx, uint16_t x, uint16_t y, uint16_t w, pixel_t color);
pixel_t MyGFX_get_pixel(My_GFX *gfx, uint16_t x, uint16_t y);

#ifdef __cplusplus
}
#endif

#endif /* _MY_GFX_H */