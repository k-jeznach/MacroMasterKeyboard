/******************************************************************************
 * File:        ssd1306_driver.h
 * Author:      Konrad Jeznach
 * Email:       konznach@gmail.com
 * GitHub:      https://github.com/k-jeznach
 *
 * Copyright (c) 2025 Konrad Jeznach. All rights reserved.
 ******************************************************************************/

#ifndef SSD1306_DRIVER_H
#define SSD1306_DRIVER_H

#include <stdint.h>
#include <stdbool.h>
#include "hardware/spi.h"
#include "hardware/i2c.h"
#include "pico/stdlib.h"

#define SSD1306_WIDTH 128
#define SSD1306_HEIGHT 64
#define SSD1306_BUFFER_SIZE (SSD1306_WIDTH * SSD1306_HEIGHT / 8)

#define SSD1306_USE_SPI // SPI
// #define SSD1306_USE_I2C  // I2C

#ifdef SSD1306_USE_SPI
#define SSD1306_SPI_PORT spi0
#define SSD1306_SCK 18
#define SSD1306_MOSI 19
#define SSD1306_DC 16
#define SSD1306_CS 17
#define SSD1306_RST 9
#define SSD1306_SPI_CLOCK 480000
#endif

#ifdef SSD1306_USE_I2C
#define SSD1306_I2C_PORT i2c0
#define SSD1306_SDA 4
#define SSD1306_SCL 5
#define SSD1306_I2C_ADDR 0x3C
#define SSD1306_I2C_CLOCK 400000
#endif

// === SSD1306 COMMANDS ===
#define SSD1306_DISPLAY_OFF 0xAE        // Turn display off
#define SSD1306_DISPLAY_ON 0xAF         // Turn display on
#define SSD1306_SET_DISPLAY_CLK 0xD5    // Set display clock divide ratio/oscillator frequency
#define SSD1306_DEFAULT_CLK 0x80        // Default frequency setting
#define SSD1306_SET_MULTIPLEX 0xA8      // Set multiplex ratio
#define SSD1306_128x64_MUX 0x3F         // Multiplex for 128x64 display
#define SSD1306_SET_DISPLAY_OFFSET 0xD3 // Set display offset
#define SSD1306_NO_OFFSET 0x00          // No offset
#define SSD1306_SET_START_LINE 0x40     // Set display start line at 0
#define SSD1306_CHARGE_PUMP 0x8D        // Enable charge pump
#define SSD1306_CHARGE_PUMP_ON 0x14     // Enable internal voltage regulator
#define SSD1306_MEMORY_MODE 0x20        // Set memory addressing mode
#define SSD1306_SET_PAGE_START 0xB0     // Set page start address (0xB0 to 0xB7)
#define SSD1306_HORIZONTAL_MODE 0x00    // Horizontal addressing mode
#define SSD1306_SEG_REMAP 0xA1          // Set segment re-map (A0 = normal, A1 = flipped)
#define SSD1306_COM_SCAN_DIR 0xC8       // Set COM output scan direction
#define SSD1306_SET_CONTRAST 0x81       // Set contrast control
#define SSD1306_DEFAULT_CONTRAST 0x7F   // Default contrast value
#define SSD1306_PRECHARGE 0xD9          // Set precharge period
#define SSD1306_PRECHARGE_15CLK 0xF1    // Precharge value
#define SSD1306_VCOM_DESELECT 0xDB      // Set VCOMH deselect level
#define SSD1306_VCOM_0_77 0x40          // Default 0.77 × Vcc
#define SSD1306_DISPLAY_NORMAL 0xA6     // Normal display mode
#define SSD1306_DISPLAY_INVERT 0xA7     // Inverted display mode

void ssd1306_driver_init();
void ssd1306_send_command(uint8_t cmd);
void ssd1306_send_data(uint8_t *data, size_t length);

#endif
