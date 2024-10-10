#include "lte.h"

#include <zephyr/device.h>
#include <zephyr/kernel.h>

#include <zephyr/net/net_if.h>
#include <zephyr/net/net_ip.h>
#include <zephyr/net/net_mgmt.h>

#include <zephyr/net/net_core.h>
#include <zephyr/net/net_mgmt.h>

#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(NETWORK, 4);

#include <zephyr/net/net_if.h>

struct in_addr gateway;
struct in_addr netmask, gateway;

// Main function
int network_init(void) {

    int ret;
    struct net_if *iface = net_if_get_first_by_type(&NET_L2_GET_NAME(PPP));
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
        struct in_addr *current_ip;

        // Retry until a valid IP address is obtained (poll until timeout of 15 seconds)
        for (int i = 0; i < 150; i++) {
            current_ip = net_if_ipv4_get_global_addr(iface, NET_ADDR_PREFERRED);
            if (current_ip != NULL) {
                LOG_INF("Current IP address while waiting: %s", net_addr_ntop(AF_INET, current_ip, (char[NET_IPV4_ADDR_LEN]){0}, NET_IPV4_ADDR_LEN));
                break;
            } else {
                LOG_DBG("No IP address found on the interface yet.");
            }
            k_sleep(K_MSEC(100));  // Wait 100ms between retries
        }

        // Check if the current IP is set by the modem driver
        if (current_ip != NULL) {
            LOG_INF("Current IP address: %s", net_addr_ntop(AF_INET, current_ip, (char[NET_IPV4_ADDR_LEN]){0}, NET_IPV4_ADDR_LEN));

            // Verify if the interface is ready for manual IP assignment
            if (!net_if_is_up(iface)) {
                LOG_ERR("Network interface is not ready for manual IP configuration");
                return -4;
            }

            // Avoid reassigning the same IP address if it's already configured
            struct net_if_addr *existing_addr = net_if_ipv4_addr_lookup(current_ip, &iface);
            if (existing_addr != NULL && existing_addr->addr_state == NET_ADDR_PREFERRED) {
                LOG_INF("IP address is already configured, skipping reassignment.");
            } else {
                // Apply the same IP address
                LOG_INF("Reconfiguring network with new settings...");
                ret = (int)net_if_ipv4_addr_add(iface, current_ip, NET_ADDR_MANUAL, 0);
                if (ret < 0) {
                    LOG_ERR("Failed to set manual IP address: %d", ret);
                } else {
                    LOG_INF("Network configuration updated with the desired IP settings.");
                }
            }

            // Set the gateway and netmask
            LOG_INF("Setting the gateway and netmask now");
            struct in_addr new_gateway = *current_ip;  // Use the current IP as the gateway for cellular connections
            struct in_addr new_netmask = { { { 255, 255, 255, 252 } } }; // Typical netmask for cellular PPP connections

            net_if_ipv4_set_gw(iface, &new_gateway);
            LOG_INF("Gateway updated to: %s", net_addr_ntop(AF_INET, &new_gateway, (char[NET_IPV4_ADDR_LEN]){0}, NET_IPV4_ADDR_LEN));

            // Set the netmask using net_if_ipv4_set_netmask
            net_if_ipv4_set_netmask(iface, &new_netmask);
            LOG_INF("Netmask set to: %s", net_addr_ntop(AF_INET, &new_netmask, (char[NET_IPV4_ADDR_LEN]){0}, NET_IPV4_ADDR_LEN));

            // Set default route (create a route to the gateway)
            LOG_INF("Adding default route to the gateway");
            struct net_if_router *router = net_if_ipv4_router_add(iface, &new_gateway, true,  10000 );
            if (!router) {
                LOG_ERR("Failed to add default route");
            } else {
                LOG_INF("Default route added successfully");
            }

        } else {
            LOG_ERR("Failed to retrieve a valid IP address from the modem driver.");
            LOG_INF("Finished checking anyway.");
        }

    } else {
        LOG_ERR("Network interface is down");
        return -1;
    }

    return 0;
}
