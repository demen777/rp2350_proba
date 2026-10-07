#include <stdio.h>
#include "pico/stdlib.h"

#define USB_PIO_D_PLUS_PIN 28
#define USB_PIO_D_MINUS_PIN 29

int main()
{
    stdio_init_all();

    while ( !stdio_usb_connected() ) {
        sleep_ms(100);
    }

    printf("Hello Denis\n");

    while (true) {
        sleep_ms(1000);
    }
}
