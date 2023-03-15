#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "my_gfx/my_gfx.h"

#define MATRIX_ROWS 8
#define MATRIX_COLS 32
#define MATRIX_NUM  (MATRIX_ROWS * MATRIX_COLS)

uint8_t matrix_buf[MATRIX_NUM];
pixel_t pixel0 = { 0, 0, 0 };
pixel_t pixel1 = { 1, 1, 1 };

void matrix_refresh(uint8_t *matrix_p, My_GFX *gfx);
void matrix_display(uint8_t *matrix_p);

int main(void) {
    My_GFX my_gfx;
    MyGFX_init(&my_gfx, MATRIX_COLS, MATRIX_ROWS);

    MyGFX_fill_screen(&my_gfx, pixel1);
    matrix_refresh(matrix_buf, &my_gfx);
    matrix_display(matrix_buf);

    MyGFX_fill_screen(&my_gfx, pixel0);
    matrix_refresh(matrix_buf, &my_gfx);
    matrix_display(matrix_buf);

    MyGFX_draw_vline(&my_gfx, 0, -1, 5, pixel1);
    matrix_refresh(matrix_buf, &my_gfx);
    matrix_display(matrix_buf);

    

    MyGFX_deinit(&my_gfx);
}

void matrix_refresh(uint8_t *matrix_p, My_GFX *gfx) {
    uint8_t (*matrix)[MATRIX_COLS] = (uint8_t (*)[MATRIX_COLS]) matrix_p;
    pixel_t (*pixel)[MATRIX_COLS] = (pixel_t (*)[MATRIX_COLS]) gfx->buffer;
    
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        for (uint8_t col = 0; col < MATRIX_COLS; col++) {
            if (pixel[row][col].b == pixel0.b) {
                matrix[row][col] = 0x00;
            } else {
                matrix[row][col] = 0x01;
            }
        }
    }
}

void matrix_display(uint8_t *matrix_p) {
    uint8_t (*matrix)[MATRIX_COLS] = (uint8_t (*)[MATRIX_COLS]) matrix_p;

    for (int i = 0; i < MATRIX_COLS * 2 + 2; i++) {
        printf("-");
    }
    printf("\n");

    for (int row = 0; row < MATRIX_ROWS; row++) {
        printf("|");
        for (int col = 0; col < MATRIX_COLS; col++) {
            if (matrix[row][col]) {
                printf("* ");
            } else {
                printf("  ");
            }
        }
        printf("|\n");
    }

    for (int i = 0; i < MATRIX_COLS * 2 + 2; i++) {
        printf("-");
    }
    printf("\n");
}

