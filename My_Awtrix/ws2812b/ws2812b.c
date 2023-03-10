/* TIM2_CH2 -- PA1 -- DMA1_Channel7 */

/* Private Includes */
#include "ch32v30x.h"
#include "string.h"
#include "ws2812b.h"

/* Private Defines */
#define ARR                 164
#define T1H_TICKS           130
#define T0H_TICKS           33
#define BITS_PER_UNIT       24
#define MATRIX_ROWS         8
#define MATRIX_COLS         32
#define MATRIX_PIXEL_NUM    (MATRIX_ROWS * MATRIX_COLS)
#define RESET_NUM           30
#define BITS_NUM            (BITS_PER_UNIT * MATRIX_PIXEL_NUM + RESET_NUM)
#define IDLE                0x00
#define BUSY                0x01

/* Static Protypes */
static void TIM2_CH2_GPIO_Init(void);
static void TIM2_CH2_DMA_Init(void);
static void TIM2_CH2_PWM_Init(void);
static void encode_frame(uint8_t* frame_p);




/* Static Variables */
static uint8_t bits_buf[BITS_NUM] = { 0 };
static uint8_t buf_state;




void ws2812b_refresh(uint8_t* frame_p) {
    encode_frame(frame_p);

    buf_state = BUSY;

    DMA_Cmd(DMA1_Channel7, DISABLE);
    DMA1_Channel7->MADDR = (uint32_t) bits_buf;
    DMA_SetCurrDataCounter(DMA1_Channel7, BITS_NUM);
    DMA_Cmd(DMA1_Channel7, ENABLE);
    TIM_DMACmd(TIM2, TIM_DMA_CC2, ENABLE);
    TIM_CtrlPWMOutputs(TIM2, ENABLE);
    TIM_Cmd(TIM2, ENABLE);
}


void ws2812b_init(void) {
    TIM2_CH2_PWM_Init();
}


static void encode_frame(uint8_t* frame_p) {
    uint32_t row, col, i, j;
    uint32_t pixel_pos_base;
    uint32_t byte_pos_base;
    uint32_t byte_pos;
    uint32_t bit_pos = 0;

    for (row = 0; row < MATRIX_ROWS; row++) {
        pixel_pos_base = row * MATRIX_COLS;
        if (row % 2) {
            /* 逆序行 */
            for (col = 0; col < MATRIX_COLS; col++) {
                byte_pos_base = (pixel_pos_base + MATRIX_COLS - col - 1) * 3;
                for (i = 0; i < 3; i++) {
                    byte_pos = byte_pos_base + i;
                    for (j = 0; j < 8; j++) {
                        bits_buf[bit_pos] = ((frame_p[byte_pos] << j) & 0x80) ? T1H_TICKS : T0H_TICKS;
                        bit_pos++;
                    }
                }
            }
        } else {
            /* 正序行 */
            for (col = 0; col < MATRIX_COLS; col++) {
                byte_pos_base = (pixel_pos_base + col) * 3;
                for (i = 0; i < 3; i++) {
                    byte_pos = byte_pos_base + i;
                    for (j = 0; j < 8; j++) {
                        bits_buf[bit_pos] = ((frame_p[byte_pos] << j) & 0x80) ? T1H_TICKS : T0H_TICKS;
                        bit_pos++;
                    }
                }
            }
        }
    }

    for (; bit_pos < BITS_NUM; bit_pos++) {
        bits_buf[bit_pos] = 0;
    }
}

static void TIM2_CH2_PWM_Init(void) {
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct = { 0 };
    TIM_OCInitTypeDef TIM_OCInitStruct = { 0 };

    TIM2_CH2_GPIO_Init();
    TIM2_CH2_DMA_Init();

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

    TIM_TimeBaseInitStruct.TIM_Prescaler = 0;
    TIM_TimeBaseInitStruct.TIM_Period = ARR;
    TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStruct);

    TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OCInitStruct.TIM_Pulse = 0;
    TIM_OC2Init(TIM2, &TIM_OCInitStruct);
    
    TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable);

}

static void TIM2_CH2_DMA_Init(void) {
    DMA_InitTypeDef DMA_InitStruct = { 0 };
    NVIC_InitTypeDef NVIC_InitStruct = { 0 };

    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);

    DMA_InitStruct.DMA_PeripheralBaseAddr = (uint32_t) &TIM2->CH2CVR;
    DMA_InitStruct.DMA_MemoryBaseAddr     = 0;
    DMA_InitStruct.DMA_DIR                = DMA_DIR_PeripheralDST;
    DMA_InitStruct.DMA_BufferSize         = 0;
    DMA_InitStruct.DMA_PeripheralInc      = DMA_PeripheralInc_Disable;
    DMA_InitStruct.DMA_MemoryInc          = DMA_MemoryInc_Enable;
    DMA_InitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
    DMA_InitStruct.DMA_MemoryDataSize     = DMA_MemoryDataSize_Byte;
    DMA_InitStruct.DMA_Mode               = DMA_Mode_Normal;
    DMA_InitStruct.DMA_Priority           = DMA_Priority_Medium;
    DMA_InitStruct.DMA_M2M                = DMA_M2M_Disable;

    DMA_Init(DMA1_Channel7, &DMA_InitStruct);

    DMA_ITConfig(DMA1_Channel7, DMA_IT_TC, ENABLE);

    NVIC_InitStruct.NVIC_IRQChannel = DMA1_Channel7_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;

    NVIC_Init(&NVIC_InitStruct);
}

static void TIM2_CH2_GPIO_Init(void) {
    GPIO_InitTypeDef GPIO_InitStruct = { 0 };

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;

    GPIO_Init(GPIOA, &GPIO_InitStruct);
}

void DMA1_Channel7_IRQHandler(void) {
    if (DMA_GetITStatus(DMA1_IT_TC7)) {
        DMA_ClearITPendingBit(DMA1_IT_TC7);
        
        buf_state = IDLE;
    }
}


