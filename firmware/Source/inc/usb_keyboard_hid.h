#ifndef USB_KEYBOARD_HID_H
#define USB_KEYBOARD_HID_H
#include <stdint.h>

void usb_hid_keyboard_init(void);
void send_key(uint8_t keycode);
void release_key();

#endif