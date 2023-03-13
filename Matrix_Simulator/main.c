#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define MATRIX_ROWS 8
#define MATRIX_COLS 32
#define MATRIX_NUM  (MATRIX_ROWS * MATRIX_COLS)

uint8_t matrix_buf[MATRIX_NUM];

void matrix_init(uint8_t *matrix_p);
void matrix_display(uint8_t *matrix_p);

int main(void) {
    matrix_init(matrix_buf);
    matrix_display(matrix_buf);
}

void matrix_init(uint8_t *matrix_p) {
    memset(matrix_p, 0x01, MATRIX_NUM);
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

