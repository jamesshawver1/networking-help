#include <zephyr/device.h>
#include <zephyr/kernel.h>

#include <zephyr/drivers/cellular.h>

#include <zephyr/pm/device.h>
#include <zephyr/pm/device_runtime.h>

#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(LTE, 4);

// LTE Modem setup
const struct device *modem = DEVICE_DT_GET(DT_ALIAS(modem));

int lte_init( void ) {
    LOG_INF("Powering on modem");
    pm_device_action_run(modem, PM_DEVICE_ACTION_RESUME);

    return 0;
}
