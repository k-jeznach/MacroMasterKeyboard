/******************************************************************************
 * File:        ssd1306_gfx.h
 * Author:      Konrad Jeznach
 * Email:       konznach@gmail.com
 * GitHub:      https://github.com/k-jeznach
 *
 * Copyright (c) 2025 Konrad Jeznach. All rights reserved.
 ******************************************************************************/

#ifndef SSD1306_GFX_H
#define SSD1306_GFX_H

#define COLOR_BLACK 0
#define COLOR_WHITE 1

// graphics functions
void ssd1306_update_screen();
void ssd1306_clear_screen(bool color);
void ssd1306_draw_pixel(uint8_t x, uint8_t y, bool color);
void ssd1306_draw_line(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, bool color);
void ssd1306_draw_rectangle(uint8_t x, uint8_t y, uint8_t width, uint8_t height, bool color);
void ssd1306_draw_filled_rectangle(uint8_t x, uint8_t y, uint8_t width, uint8_t height, bool color);
void ssd1306_draw_circle(uint8_t x, uint8_t y, uint8_t radius, bool color);

// text functions
void ssd1306_draw_char(uint8_t x, uint8_t y, char c, bool color, uint8_t size);
void ssd1306_draw_string(uint8_t x, uint8_t y, const char *str, bool color, uint8_t size);
void ssd1306_draw_numeric_variable(uint8_t x, uint8_t y, int32_t number, bool color, uint8_t size);
void ssd1306_get_text_bounds(const char *str, uint8_t x, uint8_t y, int16_t *x1, int16_t *y1, uint16_t *w, uint16_t *h);

#endif // SSD1306_GFX_H
