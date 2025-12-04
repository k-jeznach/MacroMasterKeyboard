#pragma once
#include <stdbool.h>
#include <stdint.h>

void usb_init(void);
void usb_task(void);

/* klawiatura */
bool usb_keyboard_ready(void);
void usb_keyboard_press(uint8_t keycode);
void usb_keyboard_release(void);
