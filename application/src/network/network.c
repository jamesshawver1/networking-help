#include "lte.h"

#include <zephyr/device.h>
#include <zephyr/kernel.h>

#include <zephyr/net/net_core.h>
#include <zephyr/net/net_mgmt.h>

#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(NETWORK, 4);

#include <zephyr/net/net_if.h>


// Main function
int network_init(void) {

    int ret;
    struct net_if *const telit_iface = net_if_get_first_by_type(&NET_L2_GET_NAME(PPP));
    struct net_if *const iface = telit_iface;
    net_if_set_default(iface);


    ret = lte_init();
    if (ret < 0) {
        LOG_ERR("Failed to initialize modem");
        return -1;
    }

    LOG_INF("Bringing up network interface");
    ret = net_if_up(iface);
    if (ret < 0) {
        LOG_ERR("Failed to bring up network interface");
        return -2;
    }

    LOG_INF("Waiting for network connection");
    ret = net_mgmt_event_wait_on_iface(iface, NET_EVENT_L4_CONNECTED, NULL, NULL, NULL, K_SECONDS(180));
    if (ret < 0) {
        LOG_ERR("Network connection timed out");
        return -3;
    }

    LOG_INF("Checking network interface state");
    if (net_if_is_up(iface)) {


    }
    else {
        LOG_ERR("Network interface is down");
        return -1;
    }

    return 0;
}

