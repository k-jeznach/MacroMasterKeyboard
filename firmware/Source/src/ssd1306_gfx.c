/******************************************************************************
 * File:        ssd1306_gfx.c
 * Author:      Konrad Jeznach
 * Email:       konznach@gmail.com
 * GitHub:      https://github.com/k-jeznach
 *
 * Copyright (c) 2025 Konrad Jeznach. All rights reserved.
 ******************************************************************************/
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "ssd1306_gfx.h"
#include "ssd1306_driver.h"
#include "font5x7.h"

static uint8_t ssd1306_buffer[SSD1306_BUFFER_SIZE];

void ssd1306_update_screen()
{
    for (uint8_t page = 0; page < 8; page++)
    {
        ssd1306_send_command(SSD1306_SET_PAGE_START | page);
        ssd1306_send_command(SSD1306_SET_START_LINE);

        for (uint8_t col = 0; col < SSD1306_WIDTH; col++)
        {
            ssd1306_send_data(&ssd1306_buffer[col + page * SSD1306_WIDTH], 1);
        }
    }
}

void ssd1306_clear_screen(bool color)
{
    uint8_t value = color ? 0xFF : 0x00;

    for (uint16_t i = 0; i < SSD1306_BUFFER_SIZE; i++)
    {
        ssd1306_buffer[i] = value;
    }
}

void ssd1306_draw_pixel(uint8_t x, uint8_t y, bool color)
{
    if (x >= SSD1306_WIDTH || y >= SSD1306_HEIGHT)
        return; // Out of bounds

    uint16_t index = x + (y / 8) * SSD1306_WIDTH;
    if (color)
        ssd1306_buffer[index] |= (1 << (y % 8)); // Set pixel
    else
        ssd1306_buffer[index] &= ~(1 << (y % 8)); // Clear pixel
}

void ssd1306_draw_char(uint8_t x, uint8_t y, char c, bool color, uint8_t size)
{
    if (c < 32 || c > 126)
        c = '?';

    uint8_t charIndex = c - 32;

    for (uint8_t row = 0; row < FONT_CHAR_HEIGHT; row++)
    {
        uint8_t rowData = font5x7[charIndex][row];
        for (uint8_t col = 0; col < FONT_CHAR_WIDTH; col++)
        {
            if ((rowData & (1 << (FONT_CHAR_WIDTH - 1 - col))) != 0)
            {
                for (uint8_t sx = 0; sx < size; sx++)
                {
                    for (uint8_t sy = 0; sy < size; sy++)
                    {
                        ssd1306_draw_pixel(x + (col * size) + sx, y + (row * size) + sy, color);
                    }
                }
            }
        }
    }
}

void ssd1306_draw_string(uint8_t x, uint8_t y, const char *str, bool color, uint8_t size)
{
    if (str == NULL)
        return;

    uint8_t startX = x;
    uint8_t charWidth = (FONT_CHAR_WIDTH + 1) * size;
    uint8_t charHeight = FONT_CHAR_HEIGHT * size;

    while (*str)
    {
        if (x + charWidth > SSD1306_WIDTH)
        {
            x = startX;
            y += charHeight + 1;
        }

        if (y + charHeight > SSD1306_HEIGHT)
        {
            break;
        }

        ssd1306_draw_char(x, y, *str, color, size);
        x += charWidth;
        str++;
    }
}

// needs to be debugged
void ssd1306_draw_numeric_variable(uint8_t x, uint8_t y, int32_t number, bool color, uint8_t size)
{
    char buffer[12]; // Enough for 32-bit signed integer
    snprintf(buffer, sizeof(buffer), "%ld", number);
    ssd1306_draw_string(x, y, buffer, color, size);
}

void ssd1306_get_text_bounds(const char *str, uint8_t x, uint8_t y, int16_t *x1, int16_t *y1, uint16_t *w, uint16_t *h)
{
    if (str == NULL || x1 == NULL || y1 == NULL || w == NULL || h == NULL)
        return;

    *x1 = x;
    *y1 = y;
    *w = 0;
    *h = FONT_CHAR_HEIGHT;

    while (*str)
    {
        if (*str < 32 || *str > 126)
            str++; // Skip unsupported characters
        else
        {
            *w += (FONT_CHAR_WIDTH + 1);
            str++;
        }
    }
}

void ssd1306_draw_line(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, bool color)
{
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;

    while (true)
    {
        ssd1306_draw_pixel(x0, y0, color);
        if (x0 == x1 && y0 == y1)
            break;
        int err2 = err * 2;
        if (err2 > -dy)
        {
            err -= dy;
            x0 += sx;
        }
        if (err2 < dx)
        {
            err += dx;
            y0 += sy;
        }
    }
}

void ssd1306_draw_rectangle(uint8_t x, uint8_t y, uint8_t width, uint8_t height, bool color)
{
    ssd1306_draw_line(x, y, x + width - 1, y, color);                           // Top side
    ssd1306_draw_line(x, y + height - 1, x + width - 1, y + height - 1, color); // Bottom side
    ssd1306_draw_line(x, y, x, y + height - 1, color);                          // Left side
    ssd1306_draw_line(x + width - 1, y, x + width - 1, y + height - 1, color);  // Right side
}

void ssd1306_draw_filled_rectangle(uint8_t x, uint8_t y, uint8_t width, uint8_t height, bool color)
{
    for (uint8_t i = 0; i < height; i++)
    {
        ssd1306_draw_line(x, y + i, x + width - 1, y + i, color);
    }
}

void ssd1306_draw_circle(uint8_t x, uint8_t y, uint8_t radius, bool color)
{
    int16_t f = 1 - radius;
    int16_t ddF_x = 1;
    int16_t ddF_y = -2 * radius;
    int16_t x0 = 0;
    int16_t y0 = radius;

    ssd1306_draw_pixel(x, y + radius, color);
    ssd1306_draw_pixel(x, y - radius, color);
    ssd1306_draw_pixel(x + radius, y, color);
    ssd1306_draw_pixel(x - radius, y, color);

    while (x0 < y0)
    {
        if (f >= 0)
        {
            y0--;
            ddF_y += 2;
            f += ddF_y;
        }
        x0++;
        ddF_x += 2;
        f += ddF_x;

        ssd1306_draw_pixel(x + x0, y + y0, color);
        ssd1306_draw_pixel(x - x0, y + y0, color);
        ssd1306_draw_pixel(x + x0, y - y0, color);
        ssd1306_draw_pixel(x - x0, y - y0, color);
        ssd1306_draw_pixel(x + y0, y + x0, color);
        ssd1306_draw_pixel(x - y0, y + x0, color);
        ssd1306_draw_pixel(x + y0, y - x0, color);
        ssd1306_draw_pixel(x - y0, y - x0, color);
    }
}
