#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/sys/time_units.h>

#include "usb/usb.h"
#include "network/network.h"

LOG_MODULE_REGISTER(MAIN, 4);

int main(void) {
    usb_init();
    LOG_WRN("Made with Love on %s: at %s UTC", __DATE__, __TIME__);

    LOG_DBG("Starting system initialization...");

    network_init();
    while ( 1 ) {
	k_msleep(2000);
    }
}

