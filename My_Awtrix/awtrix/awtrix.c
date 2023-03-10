#include "awtrix.h"
#include "debug.h"
#include "string.h"

static uint8_t cursor_x = 0;
static uint8_t cursor_y = 0;

static uint8_t matrix_buffer[MATRIX_ROWS][MATRIX_COLS][3] = {0};

static uint8_t font_code_6x5[][6] = {
    {0x3C, 0x12, 0x12, 0x12, 0x3C}, /*"A",0*/
    {0x3E, 0x2A, 0x2A, 0x2A, 0x14}, /*"B",1*/
    {0x1C, 0x22, 0x22, 0x22, 0x14}, /*"C",2*/
    {0x3E, 0x22, 0x22, 0x22, 0x1C}, /*"D",3*/
    {0x3E, 0x2A, 0x2A, 0x2A, 0x2A}, /*"E",4*/
    {0x3E, 0x0A, 0x0A, 0x0A, 0x0A}, /*"F",5*/
    {0x1C, 0x22, 0x22, 0x2A, 0x1A}, /*"G",6*/
    {0x3E, 0x08, 0x08, 0x08, 0x3E}, /*"H",7*/
    {0x3E, 0x00, 0x00, 0x00, 0x00}, /*"I",8*/
    {0x12, 0x22, 0x22, 0x22, 0x1E}, /*"J",9*/
    {0x3E, 0x08, 0x08, 0x14, 0x32}, /*"K",10*/
    {0x3E, 0x20, 0x20, 0x20, 0x20}, /*"L",11*/
    {0x3E, 0x04, 0x04, 0x08, 0x04}, /*"M",12*/
    {0x3E, 0x04, 0x04, 0x08, 0x3E}, /*"N",13*/
    {0x1C, 0x22, 0x22, 0x22, 0x1C}, /*"O",14*/
    {0x3E, 0x0A, 0x0A, 0x0A, 0x0E}, /*"P",15*/
    {0x1C, 0x22, 0x22, 0x32, 0x12}, /*"Q",16*/
    {0x3E, 0x0A, 0x0A, 0x0A, 0x34}, /*"R",17*/
    {0x2E, 0x2A, 0x2A, 0x2A, 0x3A}, /*"S",18*/
    {0x02, 0x02, 0x02, 0x3E, 0x02}, /*"T",19*/
    {0x1E, 0x20, 0x20, 0x20, 0x1E}, /*"U",20*/
    {0x0E, 0x10, 0x10, 0x20, 0x10}, /*"V",21*/
    {0x1E, 0x20, 0x20, 0x10, 0x20}, /*"W",22*/
    {0x26, 0x18, 0x18, 0x10, 0x18}, /*"X",23*/
    {0x06, 0x08, 0x08, 0x30, 0x08}, /*"Y",24*/
    {0x32, 0x2A, 0x2A, 0x26, 0x22}, /*"Z",25*/
    {0x34, 0x34, 0x34, 0x34, 0x38}, /*"a",26*/
    {0x3C, 0x30, 0x30, 0x30, 0x30}, /*"b",27*/
    {0x3C, 0x24, 0x24, 0x24, 0x24}, /*"c",28*/
    {0x30, 0x30, 0x30, 0x30, 0x3C}, /*"d",29*/
    {0x3C, 0x34, 0x34, 0x34, 0x2C}, /*"e",30*/
    {0x3C, 0x14, 0x14, 0x14, 0x14}, /*"f",31*/
    {0x3C, 0x24, 0x24, 0x34, 0x34}, /*"g",32*/
    {0x3C, 0x10, 0x10, 0x10, 0x30}, /*"h",33*/
    {0x34, 0x00, 0x00, 0x00, 0x00}, /*"i",34*/
    {0x20, 0x20, 0x20, 0x34, 0x00}, /*"j",35*/
    {0x3C, 0x10, 0x10, 0x10, 0x30}, /*"k",36*/
    {0x3C, 0x00, 0x00, 0x00, 0x00}, /*"l",37*/
    {0x3C, 0x08, 0x08, 0x30, 0x08}, /*"m",38*/
    {0x3C, 0x08, 0x08, 0x10, 0x3C}, /*"n",39*/
    {0x18, 0x24, 0x24, 0x24, 0x18}, /*"o",40*/
    {0x3C, 0x14, 0x14, 0x14, 0x0C}, /*"p",41*/
    {0x0C, 0x14, 0x14, 0x14, 0x3C}, /*"q",42*/
    {0x3C, 0x04, 0x04, 0x04, 0x04}, /*"r",43*/
    {0x2C, 0x34, 0x34, 0x34, 0x34}, /*"s",44*/
    {0x3C, 0x30, 0x30, 0x30, 0x30}, /*"t",45*/
    {0x1C, 0x20, 0x20, 0x20, 0x1C}, /*"u",46*/
    {0x0C, 0x10, 0x10, 0x20, 0x10}, /*"v",47*/
    {0x1C, 0x20, 0x20, 0x10, 0x20}, /*"w",48*/
    {0x24, 0x18, 0x18, 0x10, 0x18}, /*"x",49*/
    {0x2C, 0x30, 0x30, 0x30, 0x3C}, /*"y",50*/
    {0x34, 0x34, 0x34, 0x2C, 0x24}, /*"z",51*/
    {0x3E, 0x00, 0x00, 0x00, 0x00}, /*"1",52*/
    {0x32, 0x32, 0x32, 0x2A, 0x24}, /*"2",53*/
    {0x2A, 0x2A, 0x2A, 0x2A, 0x14}, /*"3",54*/
    {0x0E, 0x08, 0x08, 0x08, 0x3E}, /*"4",55*/
    {0x2E, 0x2A, 0x2A, 0x2A, 0x12}, /*"5",56*/
    {0x1C, 0x2A, 0x2A, 0x2A, 0x12}, /*"6",57*/
    {0x22, 0x12, 0x12, 0x12, 0x0E}, /*"7",58*/
    {0x14, 0x2A, 0x2A, 0x2A, 0x14}, /*"8",59*/
    {0x2E, 0x2A, 0x2A, 0x2A, 0x3E}, /*"9",60*/
    {0x3E, 0x22, 0x22, 0x22, 0x3E}, /*"0",61*/
};

void enter_AWTRIX(void)
{
    uint16_t idx = 0;
    uint16_t row = 0;
    uint16_t col = 0;

    for (idx = 0; idx < 6; idx++)
    {
        cursor_y = 0;
        for (row = 0; row < 6; row++)
        {
            cursor_x = 5 * idx;
            for (col = 0; col < font_code_8x8[idx][6]; col++)
            {
                matrix_buffer[cursor_y][cursor_x][0] = ((font_code_8x8[idx][row] << col) & 0x80) ? 0x01 : 0x00;
                matrix_buffer[cursor_y][cursor_x][1] = matrix_buffer[cursor_y][cursor_x][0];
                matrix_buffer[cursor_y][cursor_x][2] = matrix_buffer[cursor_y][cursor_x][0];
                cursor_x++;
            }
            cursor_y++;
        }
    }

    ws2812b_refresh(matrix_buffer);

    Delay_Ms(500);

    memset(matrix_buffer, 0x00, sizeof(matrix_buffer));

    ws2812b_refresh(matrix_buffer);

    Delay_Ms(500);
}
