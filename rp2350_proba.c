#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/clocks.h"
#include "pio_usb.h"
#include "tusb.h"


#define USB_PIO_D_PLUS_PIN 28
#define USB_PIO_D_MINUS_PIN 29

int main()
{
    set_sys_clock_khz(120 * 1000, true);

    pio_usb_configuration_t pio_usb_cfg = PIO_USB_DEFAULT_CONFIG;
    pio_usb_cfg.pin_dp = USB_PIO_D_PLUS_PIN;

    tuh_configure(BOARD_TUH_RHPORT, TUH_CFGID_RPI_PIO_USB_CONFIGURATION, &pio_usb_cfg);

    tusb_rhport_init_t dev_init = {
        .role = TUSB_ROLE_DEVICE,
        .speed = TUSB_SPEED_AUTO};
    tusb_init(BOARD_TUD_RHPORT, &dev_init);

    tusb_rhport_init_t host_init = {
        .role = TUSB_ROLE_HOST,
        .speed = TUSB_SPEED_AUTO};
    tusb_init(BOARD_TUH_RHPORT, &host_init);

    stdio_init_all();

    bool has_greetings = false;

    while (true)
    {
        tuh_task();
        if(stdio_usb_connected() && !has_greetings) {
            printf("Hello Denis\n");
            has_greetings = true;
        }
    }
}

void tuh_hid_report_received_cb(uint8_t dev_addr, uint8_t idx, uint8_t const* report, uint16_t len) {

}