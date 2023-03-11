#ifndef _WS2812B_H 
#define _WS2812B_H

#ifdef __cplusplus
    extern "C" {
#endif 

/* Public Includes */
#include <stdint.h>

/* Public Defines */
#define MATRIX_ROWS         8
#define MATRIX_COLS         32
#define MATRIX_PIXEL_NUM    (MATRIX_ROWS * MATRIX_COLS)

/* Public Protypes */
void ws2812b_init(void);
void ws2812b_refresh(uint8_t* frame_p);

#ifdef __cplusplus
    }
#endif

#endif /* _WS2812B_H */
