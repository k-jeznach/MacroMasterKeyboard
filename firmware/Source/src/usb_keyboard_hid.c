#include "usb_keyboard_hid.h"
#include "pico/stdlib.h"
#include "tusb.h"
#include "bsp/board_api.h"
#include "os.h"
#include "FreeRTOS.h"
#include "queue.h"
#include "task.h"
#include "ssd1306_gfx.h"


static void initialize_keyboard_hid()
{
    board_init();
    tusb_init();
}

void send_key(uint8_t keycode)
{
    if (tud_hid_ready())
    {
        uint8_t keycode_array[6] = { keycode };
        tud_hid_keyboard_report(0, 0, keycode_array);
    }
}

void release_key()
{
    if (tud_hid_ready())
    {
        tud_hid_keyboard_report(0, 0, NULL);
    }
}

static void usb_hid_keyboard_task(void *pvParameters)
{
    /* Remove compiler warning about unused parameter. */
    (void)pvParameters;
    initialize_keyboard_hid();

    ssd1306_clear_screen(COLOR_BLACK); // temporary
    ssd1306_draw_string(7, 8, "MacroMaster", COLOR_WHITE, 2);
    ssd1306_update_screen();

    while (1)
    {
        tud_task();
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

void usb_hid_keyboard_init(void)
{
    xTaskCreate(usb_hid_keyboard_task, "Keyboard task", 256, NULL, OSPRIORITYABOVENORMAL, NULL);
}
