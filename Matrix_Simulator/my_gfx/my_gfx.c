
#include "my_gfx.h"

/**
 * @brief         初始化My_GFX
 * 
 * @param gfx     My_GFX指针
 * @param w       宽度
 * @param h       高度
 */
void MyGFX_init(My_GFX *gfx, int16_t w, int16_t h) {
    uint32_t size = sizeof(pixel_t) * w * h;
    if (gfx->buffer = (pixel_t *) malloc(size)) {
        memset(gfx->buffer, 0, size);

        gfx->width = w;
        gfx->height = h;
    }
}

/**
 * @brief         去初始化
 * 
 * @param gfx     My_GFX指针
 */
void MyGFX_deinit(My_GFX *gfx) {
    if (gfx->buffer) {
        free(gfx->buffer);
    }
}

/**
 * @brief         以指定参数画点
 * 
 * @param gfx     My_GFX指针
 * @param x       画点位置的横坐标
 * @param y       画点位置的纵坐标
 * @param color   画点的颜色
 */
void MyGFX_draw_pixel(My_GFX *gfx, int16_t x, int16_t y, pixel_t color) {
    if (gfx->buffer) {
        if ((x < 0) || (y < 0) || (x >= gfx->width) || (y >= gfx->height)) {
            return;
        }

        gfx->buffer[x + y * gfx->width] = color;
    }
}

/**
 * @brief         以指定颜色填充屏幕
 * 
 * @param gfx     My_GFX指针
 * @param color   指定颜色
 */
void MyGFX_fill_screen(My_GFX *gfx, pixel_t color) {
    if (gfx->buffer) {
        uint32_t i;
        uint32_t num = gfx->height * gfx->width;

        for (i = 0; i < num; i++) {
            gfx->buffer[i] = color;
        }
    }
}

/**
 * @brief         绘制垂直直线
 * 
 * @param gfx     My_GFX指针
 * @param x       直线起点横坐标
 * @param y       直线起点纵坐标
 * @param h       直线高度
 * @param color   指定颜色
 */
void MyGFX_draw_vline(My_GFX *gfx, int16_t x, int16_t y, int16_t h, pixel_t color) {
    // 边界检测
    if ((x < 0) || (y + h < 0) || (x >= gfx->width) || (y >= gfx->height)) {
        return;
    }

    // 将负的高度转换为正的高度
    if (h < 0) {
        h *= -1;
        y -= h;
    }

    if (y < 0) {
        h += y;
        y = 0;
    }

    if (y + h >= gfx->height) {
        h = gfx->height - y - 1;
    }

    pixel_t *pixel_p = gfx->buffer + y * gfx->width + x;
    for (int16_t i = 0; i < h; i++) {
        *pixel_p = color;
        pixel_p += gfx->width;
    }
}


/**
 * @brief         绘制水平直线
 * 
 * @param gfx     My_GFX指针
 * @param x       直线起点横坐标
 * @param y       直线起点纵坐标
 * @param h       直线宽度
 * @param color   指定颜色
 */
void MyGFX_draw_hline(My_GFX *gfx, int16_t x, int16_t y, int16_t w, pixel_t color) {
    // 边界检测
    if ((x + w < 0) || (y < 0) || (x >= gfx->width) || (y >= gfx->height)) {
        return;
    }

    // 将负的宽度转换为正的宽度
    if (w < 0) {
        w *= -1;
        x -= w;
    }

    if (x < 0) {
        w += x;
        x = 0;
    }

    if (x + w >= gfx->width) {
        w = gfx->width - x - 1;
    }

    pixel_t *pixel_p = gfx->buffer + y * gfx->width + x;
    for (int16_t i = 0; i < w; i++) {
        *pixel_p = color;
        pixel_p++;
    }
}
