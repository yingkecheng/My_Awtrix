#ifndef WS2812B_H 
#define WS2812B_H

#include <stdint.h>

/* Public Includes */
void ws2812b_init(void);
void ws2812b_refresh(uint8_t* frame_p);

#endif /* WS2812B_H */
