#include "usb.h"
#include "tusb.h"
// #include "tusb_hid.h"


void usb_init(void) {
    tusb_init();
}

void usb_task(void) {
    tud_task();
}

bool usb_keyboard_ready(void) {
    return tud_hid_ready();
}

void usb_keyboard_press(uint8_t keycode) {
    if (!tud_hid_ready()) return;

    uint8_t keycodes[6] = { keycode };
    tud_hid_keyboard_report(0, 0, keycodes);
}

void usb_keyboard_release(void) {
    if (!tud_hid_ready()) return;
    tud_hid_keyboard_report(0, 0, NULL);
}

uint16_t tud_hid_get_report_cb(uint8_t instance,
                               uint8_t report_id,
                               hid_report_type_t report_type,
                               uint8_t* buffer,
                               uint16_t reqlen)
{
    (void) instance;
    (void) report_id;
    (void) report_type;
    (void) buffer;
    (void) reqlen;

    return 0;
}

void tud_hid_set_report_cb(uint8_t instance,
                           uint8_t report_id,
                           hid_report_type_t report_type,
                           uint8_t const* buffer,
                           uint16_t bufsize)
{
    (void) instance;
    (void) report_id;
    (void) report_type;
    (void) buffer;
    (void) bufsize;
}
