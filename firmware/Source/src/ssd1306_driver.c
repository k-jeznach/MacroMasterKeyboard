/******************************************************************************
 * File:        ssd1306_driver.c
 * Author:      Konrad Jeznach
 * Email:       konznach@gmail.com
 * GitHub:      https://github.com/k-jeznach
 *
 * Copyright (c) 2025 Konrad Jeznach. All rights reserved.
 ******************************************************************************/

#include "ssd1306_driver.h"

void ssd1306_driver_init()
{
#ifdef SSD1306_USE_SPI
    spi_init(SSD1306_SPI_PORT, SSD1306_SPI_CLOCK);
    gpio_set_function(SSD1306_SCK, GPIO_FUNC_SPI);
    gpio_set_function(SSD1306_MOSI, GPIO_FUNC_SPI);

    gpio_init(SSD1306_CS);
    gpio_set_dir(SSD1306_CS, GPIO_OUT);
    gpio_put(SSD1306_CS, 1);

    gpio_init(SSD1306_DC);
    gpio_set_dir(SSD1306_DC, GPIO_OUT);

    gpio_init(SSD1306_RST);
    gpio_set_dir(SSD1306_RST, GPIO_OUT);

    gpio_put(SSD1306_RST, 0);
    sleep_ms(1);
    gpio_put(SSD1306_RST, 1);
#endif

#ifdef SSD1306_USE_I2C
    i2c_init(SSD1306_I2C_PORT, SSD1306_I2C_CLOCK);
    gpio_set_function(SSD1306_SDA, GPIO_FUNC_I2C);
    gpio_set_function(SSD1306_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(SSD1306_SDA);
    gpio_pull_up(SSD1306_SCL);
#endif

    // ssd1306_send_command(SSD1306_DISPLAY_OFF);
    // ssd1306_send_command(SSD1306_SET_DISPLAY_CLK);
    // ssd1306_send_command(SSD1306_DEFAULT_CLK);
    // ssd1306_send_command(SSD1306_SET_MULTIPLEX);
    // ssd1306_send_command(SSD1306_128x64_MUX);
    // ssd1306_send_command(SSD1306_SET_DISPLAY_OFFSET);
    // ssd1306_send_command(SSD1306_SET_START_LINE);
    // ssd1306_send_command(SSD1306_MEMORY_MODE);
    ssd1306_send_command(SSD1306_SEG_REMAP);
    ssd1306_send_command(SSD1306_COM_SCAN_DIR);
    ssd1306_send_command(SSD1306_SET_CONTRAST);
    ssd1306_send_command(SSD1306_DEFAULT_CONTRAST);
    // ssd1306_send_command(SSD1306_PRECHARGE);
    // ssd1306_send_command(SSD1306_PRECHARGE_15CLK);
    // ssd1306_send_command(SSD1306_VCOM_DESELECT);
    // ssd1306_send_command(SSD1306_VCOM_0_77);
    ssd1306_send_command(SSD1306_DISPLAY_NORMAL);
    ssd1306_send_command(SSD1306_CHARGE_PUMP);
    ssd1306_send_command(SSD1306_CHARGE_PUMP_ON);
    ssd1306_send_command(SSD1306_DISPLAY_ON);
    ssd1306_send_command(SSD1306_HORIZONTAL_MODE);
    ssd1306_send_command(SSD1306_NO_OFFSET);
}
void ssd1306_send_command(uint8_t cmd)
{
#ifdef SSD1306_USE_SPI
    gpio_put(SSD1306_DC, 0);
    gpio_put(SSD1306_CS, 0);
    spi_write_blocking(SSD1306_SPI_PORT, &cmd, 1);
    gpio_put(SSD1306_CS, 1);
#endif

#ifdef SSD1306_USE_I2C
    uint8_t buffer[2] = {0x00, cmd};
    i2c_write_blocking(SSD1306_I2C_PORT, SSD1306_I2C_ADDR, buffer, 2, false);
#endif
}

void ssd1306_send_data(uint8_t *data, size_t length)
{
#ifdef SSD1306_USE_SPI
    gpio_put(SSD1306_DC, 1);
    gpio_put(SSD1306_CS, 0);
    spi_write_blocking(SSD1306_SPI_PORT, data, length);
    gpio_put(SSD1306_CS, 1);
#endif

#ifdef SSD1306_USE_I2C
    uint8_t buffer[length + 1];
    buffer[0] = SSD1306_SET_START_LINE;
    memcpy(&buffer[1], data, length);
    i2c_write_blocking(SSD1306_I2C_PORT, SSD1306_I2C_ADDR, buffer, length + 1, false);
#endif
}
