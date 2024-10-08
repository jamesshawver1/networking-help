# Setup

## Ubuntu

As long as you're using an Ubuntu machine, setup is rather straightforward. You just need make and docker setup and then to run make. The commands for this can be found below

`sudo apt install build-essential docker.io`
`sudo chown -aG docker $USER`
`sudo reboot`

`make`


if you want to nose around inside of the docker container, run:
`make mount`

## Windows
We've had a few folks still leverage windows, but they needed to use WSL and to pass the Segger to WSL to work. The docker image actually performs the flashing of the hardware etc, so we needed to run as privilledged.


# Current results

After flashing the code onto the mimxrt1060evkb with the telit LE910C4-WWXD modem wired up through the arduino header, we're able to get ping information, but that's it. We want DNS and TCP to work so that way we can move forward with getting AWS connected for FOTA.

uart:~$ net ping 8.8.8.8
PING 8.8.8.8
28 bytes from 8.8.8.8 to 48.48.77.115: icmp_seq=1 ttl=109 time=197 ms
28 bytes from 8.8.8.8 to 48.48.77.115: icmp_seq=2 ttl=109 time=117 ms
28 bytes from 8.8.8.8 to 48.48.77.115: icmp_seq=3 ttl=109 time=118 ms
uart:~$ net dns google.com A
IPv4 address type
Query for 'google.com' sent.
[00:02:23.482,000] <dbg> net_dns_resolve: dns_write: (shell_uart): [0] submitting work to server idx 0 for id 62282 hash 59079
dns: Timeout while resolving name.
[00:02:25.482,000] <dbg> net_dns_resolve: query_timeout: (sysworkq): Query timeout DNS req 62282 type 1 hash 59079
[00:02:25.482,000] <dbg> net_dns_resolve: dns_resolve_cancel_with_hash: (sysworkq): Cancelling DNS req 62282 (name google.com type 1 hash 59079)

# Log outputs
[00:00:00.010,000] <dbg> net_dns_resolve: dns_resolve_init_locked: (main): [0] 8.8.8.8
*** Booting Zephyr OS build v3.7.0 ***
[00:00:00.011,000] <inf> USB: Starting Initialization

[00:00:00.012,000] <inf> USB: Happy Dance

[00:00:00.012,000] <inf> USB: Waiting on DTR
[00:00:00.112,000] <inf> USB: Waiting on DTR
[00:00:00.176,000] <inf> udc: ep 0x80 is not halted|disabled
[00:00:00.212,000] <inf> USB: Waiting on DTR
[00:00:00.263,000] <inf> udc: ep 0x80 is not halted|disabled
[00:00:00.312,000] <inf> USB: Waiting on DTR
[00:00:00.412,000] <inf> USB: Waiting on DTR
[00:00:00.512,000] <inf> USB: Waiting on DTR
[00:00:00.612,000] <wrn> MAIN: Made with Love on Oct  8 2024: at 20:03:55 UTC
[00:00:00.612,000] <dbg> MAIN: main: Starting system initialization...
[00:00:00.612,000] <inf> LTE: Powering on modem
[00:00:00.612,000] <dbg> modem_cellular: modem_cellular_log_event: event resume
[00:00:00.612,000] <dbg> modem_cellular: modem_cellular_log_state_changed: switch from idle to power pulse
[00:00:00.612,000] <inf> NETWORK: Bringing up network interface
[00:00:00.613,000] <inf> NETWORK: Waiting for network connection
[00:00:05.663,000] <dbg> modem_cellular: modem_cellular_log_event: event timeout
[00:00:05.663,000] <dbg> modem_cellular: modem_cellular_log_state_changed: switch from power pulse to await power on
[00:00:20.663,000] <dbg> modem_cellular: modem_cellular_log_event: event timeout
[00:00:20.663,000] <dbg> modem_cellular: modem_cellular_log_state_changed: switch from await power on to run init script
[00:00:20.663,000] <dbg> modem_cellular: modem_cellular_log_event: event bus opened
[00:00:20.663,000] <dbg> modem_chat: modem_chat_script_start: running script: telit_me910g1_init_chat_script
[00:00:20.663,000] <dbg> modem_chat: modem_chat_script_next: telit_me910g1_init_chat_script: step: 0
[00:00:20.663,000] <dbg> modem_chat: modem_chat_script_next: sending: AT
[00:00:20.685,000] <dbg> modem_chat: modem_chat_on_unknown_command_received: AT
[00:00:20.685,000] <dbg> modem_chat: modem_chat_on_unknown_command_received: OK
[00:00:20.763,000] <dbg> modem_chat: modem_chat_script_next: telit_me910g1_init_chat_script: step: 1
[00:00:20.763,000] <dbg> modem_chat: modem_chat_script_next: sending: AT
[00:00:20.787,000] <dbg> modem_chat: modem_chat_on_unknown_command_received: AT
[00:00:20.787,000] <dbg> modem_chat: modem_chat_on_unknown_command_received: OK
[00:00:20.863,000] <dbg> modem_chat: modem_chat_script_next: telit_me910g1_init_chat_script: step: 2
[00:00:20.863,000] <dbg> modem_chat: modem_chat_script_next: sending: ATE0
[00:00:20.888,000] <dbg> modem_chat: modem_chat_on_unknown_command_received: ATE0
[00:00:20.888,000] <dbg> modem_chat: modem_chat_on_unknown_command_received: OK
[00:00:20.963,000] <dbg> modem_chat: modem_chat_script_next: telit_me910g1_init_chat_script: step: 3
[00:00:20.963,000] <dbg> modem_chat: modem_chat_script_next: sending: AT+CMEE=1
[00:00:20.991,000] <dbg> modem_chat: modem_chat_on_unknown_command_received: OK
[00:00:21.163,000] <dbg> modem_chat: modem_chat_script_next: telit_me910g1_init_chat_script: step: 4
[00:00:21.163,000] <dbg> modem_chat: modem_chat_script_next: sending: AT#SELINT=2
[00:00:21.189,000] <dbg> modem_chat: modem_chat_on_unknown_command_received: OK
[00:00:21.363,000] <dbg> modem_chat: modem_chat_script_next: telit_me910g1_init_chat_script: step: 5
[00:00:21.363,000] <dbg> modem_chat: modem_chat_script_next: sending: AT+CFUN=1
[00:00:21.389,000] <dbg> modem_chat: modem_chat_on_unknown_command_received: OK
[00:00:23.364,000] <dbg> modem_chat: modem_chat_script_next: telit_me910g1_init_chat_script: step: 6
[00:00:23.364,000] <dbg> modem_chat: modem_chat_script_next: sending: AT+CREG=1
[00:00:23.390,000] <dbg> modem_chat: modem_chat_on_unknown_command_received: OK
[00:00:23.564,000] <dbg> modem_chat: modem_chat_script_next: telit_me910g1_init_chat_script: step: 7
[00:00:23.564,000] <dbg> modem_chat: modem_chat_script_next: sending: AT+CGREG=1
[00:00:23.590,000] <dbg> modem_chat: modem_chat_on_unknown_command_received: OK
[00:00:23.764,000] <dbg> modem_chat: modem_chat_script_next: telit_me910g1_init_chat_script: step: 8
[00:00:23.764,000] <dbg> modem_chat: modem_chat_script_next: sending: AT+CEREG=1
[00:00:23.790,000] <dbg> modem_chat: modem_chat_on_unknown_command_received: OK
[00:00:23.964,000] <dbg> modem_chat: modem_chat_script_next: telit_me910g1_init_chat_script: step: 9
[00:00:23.964,000] <dbg> modem_chat: modem_chat_script_next: sending: AT+COPS=0
[00:00:24.002,000] <dbg> modem_chat: modem_chat_on_unknown_command_received: OK
[00:00:24.964,000] <dbg> modem_chat: modem_chat_script_next: telit_me910g1_init_chat_script: step: 10
[00:00:24.964,000] <dbg> modem_chat: modem_chat_script_next: sending: AT+CGDCONT=1,"IP","h2g2"
[00:00:25.131,000] <dbg> modem_chat: modem_chat_on_unknown_command_received: OK
[00:00:27.464,000] <dbg> modem_chat: modem_chat_script_next: telit_me910g1_init_chat_script: step: 11
[00:00:27.464,000] <dbg> modem_chat: modem_chat_script_next: sending: AT#SGACT=1,1
[00:00:27.499,000] <dbg> modem_chat: modem_chat_on_unknown_command_received: #SGACT: 48.51.38.165
[00:00:27.499,000] <dbg> modem_chat: modem_chat_on_unknown_command_received: OK
[00:00:28.464,000] <dbg> modem_chat: modem_chat_script_next: telit_me910g1_init_chat_script: step: 12
[00:00:28.464,000] <dbg> modem_chat: modem_chat_script_next: sending: AT+ICCID
[00:00:28.494,000] <dbg> modem_chat: modem_chat_log_received_command: +ICCID:  8901240270115029670
[00:00:28.494,000] <dbg> modem_chat: modem_chat_script_next: telit_me910g1_init_chat_script: step: 13
[00:00:28.494,000] <dbg> modem_chat: modem_chat_script_next: sending: AT+CIMI
[00:00:28.494,000] <dbg> modem_chat: modem_chat_log_received_command:  OK
[00:00:28.494,000] <dbg> modem_chat: modem_chat_script_next: telit_me910g1_init_chat_script: step: 14
[00:00:28.494,000] <dbg> modem_chat: modem_chat_script_next: sending: AT+CGSN
[00:00:28.521,000] <dbg> modem_chat: modem_chat_log_received_command:  310240271502967
[00:00:28.521,000] <dbg> modem_chat: modem_chat_script_next: telit_me910g1_init_chat_script: step: 15
[00:00:28.521,000] <dbg> modem_chat: modem_chat_script_next: sending: AT+CGMM
[00:00:28.521,000] <dbg> modem_chat: modem_chat_on_unknown_command_received: OK
[00:00:28.547,000] <dbg> modem_chat: modem_chat_log_received_command:  LE910C4-WWXD
[00:00:28.547,000] <dbg> modem_chat: modem_chat_script_next: telit_me910g1_init_chat_script: step: 16
[00:00:28.547,000] <dbg> modem_chat: modem_chat_script_next: sending: AT+CGMI
[00:00:28.547,000] <dbg> modem_chat: modem_chat_on_unknown_command_received: OK
[00:00:28.573,000] <dbg> modem_chat: modem_chat_log_received_command:  Telit
[00:00:28.573,000] <dbg> modem_chat: modem_chat_script_next: telit_me910g1_init_chat_script: step: 17
[00:00:28.573,000] <dbg> modem_chat: modem_chat_script_next: sending: AT+CGMR
[00:00:28.573,000] <dbg> modem_chat: modem_chat_on_unknown_command_received: OK
[00:00:28.599,000] <dbg> modem_chat: modem_chat_log_received_command:  M0F.603003
[00:00:28.599,000] <dbg> modem_chat: modem_chat_script_next: telit_me910g1_init_chat_script: step: 18
[00:00:28.599,000] <dbg> modem_chat: modem_chat_script_next: sending: AT#CMUXMODE=5
[00:00:28.599,000] <dbg> modem_chat: modem_chat_on_unknown_command_received: OK
[00:00:28.626,000] <dbg> modem_chat: modem_chat_on_unknown_command_received: OK
[00:00:29.599,000] <dbg> modem_chat: modem_chat_script_next: telit_me910g1_init_chat_script: step: 19
[00:00:29.599,000] <dbg> modem_chat: modem_chat_script_next: sending: AT+CMUX=0,0,5,122
[00:00:29.633,000] <dbg> modem_chat: modem_chat_on_unknown_command_received: OK
[00:00:30.599,000] <dbg> modem_chat: modem_chat_script_stop: telit_me910g1_init_chat_script: complete
[00:00:30.599,000] <dbg> modem_cellular: modem_cellular_log_event: event script success
[00:00:30.599,000] <dbg> modem_cellular: modem_cellular_log_event: event bus closed
[00:00:30.599,000] <dbg> modem_cellular: modem_cellular_log_state_changed: switch from run init script to connect cmux
[00:00:30.699,000] <dbg> modem_cellular: modem_cellular_log_event: event timeout
[00:00:30.699,000] <dbg> modem_cellular: modem_cellular_log_event: event bus opened
[00:00:30.723,000] <dbg> modem_cellular: modem_cellular_log_event: event cmux connected
[00:00:30.723,000] <dbg> modem_cellular: modem_cellular_log_state_changed: switch from connect cmux to open dlci1
[00:00:30.747,000] <dbg> modem_cellular: modem_cellular_log_event: event dlci1 opened
[00:00:30.747,000] <dbg> modem_cellular: modem_cellular_log_state_changed: switch from open dlci1 to open dlci2
[00:00:30.772,000] <dbg> modem_cellular: modem_cellular_log_event: event dlci2 opened
[00:00:30.772,000] <dbg> modem_cellular: modem_cellular_log_state_changed: switch from open dlci2 to run dial script
[00:00:30.872,000] <dbg> modem_cellular: modem_cellular_log_event: event timeout
[00:00:30.872,000] <dbg> modem_chat: modem_chat_script_start: running script: telit_me910g1_dial_chat_script
[00:00:30.872,000] <dbg> modem_chat: modem_chat_script_next: telit_me910g1_dial_chat_script: step: 0
[00:00:30.872,000] <dbg> modem_chat: modem_chat_script_next: sending: ATD*99***1#
[00:00:30.908,000] <dbg> modem_chat: modem_chat_log_received_command: CONNECT  150000000
[00:00:30.908,000] <dbg> modem_chat: modem_chat_script_stop: telit_me910g1_dial_chat_script: complete
[00:00:30.908,000] <dbg> modem_cellular: modem_cellular_log_event: event script success
[00:00:30.908,000] <dbg> modem_cellular: modem_cellular_log_state_changed: switch from run dial script to await registered
[00:00:33.908,000] <dbg> modem_cellular: modem_cellular_log_event: event timeout
[00:00:33.908,000] <dbg> modem_chat: modem_chat_script_start: running script: telit_me910g1_periodic_chat_script
[00:00:33.908,000] <dbg> modem_chat: modem_chat_script_next: telit_me910g1_periodic_chat_script: step: 0
[00:00:33.908,000] <dbg> modem_chat: modem_chat_script_next: sending: AT+CREG?
[00:00:33.940,000] <dbg> modem_chat: modem_chat_on_unknown_command_received: AT+CREG?
[00:00:33.940,000] <dbg> modem_chat: modem_chat_log_received_command: +CREG:  1 1
[00:00:33.940,000] <dbg> modem_chat: modem_chat_on_unknown_command_received: OK
[00:00:33.940,000] <dbg> modem_cellular: modem_cellular_log_event: event registered
[00:00:33.940,000] <dbg> modem_cellular: modem_cellular_log_state_changed: switch from await registered to carrier on
[00:00:33.969,000] <dbg> modem_ppp: modem_ppp_process_received_byte: Receiving PPP frame
[00:00:33.969,000] <dbg> modem_ppp: modem_ppp_process_received_byte: Received PPP frame (len 29)
[00:00:33.969,000] <dbg> modem_ppp: modem_ppp_process_received_byte: Receiving PPP frame
[00:00:33.970,000] <dbg> modem_ppp: modem_ppp_process_received_byte: Received PPP frame (len 12)
[00:00:34.001,000] <dbg> modem_ppp: modem_ppp_process_received_byte: Receiving PPP frame
[00:00:34.001,000] <dbg> modem_ppp: modem_ppp_process_received_byte: Received PPP frame (len 13)
[00:00:34.030,000] <dbg> modem_ppp: modem_ppp_process_received_byte: Receiving PPP frame
[00:00:34.030,000] <dbg> modem_ppp: modem_ppp_process_received_byte: Received PPP frame (len 12)
[00:00:34.065,000] <dbg> modem_ppp: modem_ppp_process_received_byte: Receiving PPP frame
[00:00:34.065,000] <dbg> modem_ppp: modem_ppp_process_received_byte: Received PPP frame (len 12)
[00:00:34.065,000] <dbg> modem_ppp: modem_ppp_process_received_byte: Receiving PPP frame
[00:00:34.065,000] <dbg> modem_ppp: modem_ppp_process_received_byte: Received PPP frame (len 9)
[00:00:34.111,000] <dbg> modem_ppp: modem_ppp_process_received_byte: Receiving PPP frame
[00:00:34.111,000] <dbg> modem_ppp: modem_ppp_process_received_byte: Received PPP frame (len 8)
[00:00:34.111,000] <dbg> modem_ppp: modem_ppp_process_received_byte: Receiving PPP frame
[00:00:34.111,000] <dbg> modem_ppp: modem_ppp_process_received_byte: Received PPP frame (len 26)
[00:00:34.146,000] <dbg> modem_ppp: modem_ppp_process_received_byte: Receiving PPP frame
[00:00:34.146,000] <dbg> modem_ppp: modem_ppp_process_received_byte: Received PPP frame (len 26)
[00:00:34.146,000] <inf> NETWORK: Checking network interface state
[00:00:34.408,000] <dbg> modem_chat: modem_chat_script_next: telit_me910g1_periodic_chat_script: step: 1
[00:00:34.408,000] <dbg> modem_chat: modem_chat_script_next: sending: AT+CEREG?
[00:00:34.440,000] <dbg> modem_chat: modem_chat_on_unknown_command_received: AT+CEREG?
[00:00:34.440,000] <dbg> modem_chat: modem_chat_log_received_command: +CEREG:  1 1
[00:00:34.440,000] <dbg> modem_chat: modem_chat_on_unknown_command_received: OK
[00:00:34.440,000] <dbg> modem_cellular: modem_cellular_log_event: event registered
[00:00:34.908,000] <dbg> modem_chat: modem_chat_script_stop: telit_me910g1_periodic_chat_script: complete
[00:00:34.908,000] <dbg> modem_cellular: modem_cellular_log_event: event script success
[00:00:36.940,000] <dbg> modem_cellular: modem_cellular_log_event: event timeout
[00:00:36.940,000] <dbg> modem_chat: modem_chat_script_start: running script: telit_me910g1_periodic_chat_script
[00:00:36.940,000] <dbg> modem_chat: modem_chat_script_next: telit_me910g1_periodic_chat_script: step: 0
[00:00:36.940,000] <dbg> modem_chat: modem_chat_script_next: sending: AT+CREG?
[00:00:36.969,000] <dbg> modem_chat: modem_chat_on_unknown_command_received: AT+CREG?
[00:00:36.969,000] <dbg> modem_chat: modem_chat_log_received_command: +CREG:  1 1
[00:00:36.969,000] <dbg> modem_chat: modem_chat_on_unknown_command_received: OK
[00:00:36.969,000] <dbg> modem_cellular: modem_cellular_log_event: event registered
[00:00:37.440,000] <dbg> modem_chat: modem_chat_script_next: telit_me910g1_periodic_chat_script: step: 1
[00:00:37.440,000] <dbg> modem_chat: modem_chat_script_next: sending: AT+CEREG?
[00:00:37.472,000] <dbg> modem_chat: modem_chat_on_unknown_command_received: AT+CEREG?
[00:00:37.472,000] <dbg> modem_chat: modem_chat_log_received_command: +CEREG:  1 1
[00:00:37.472,000] <dbg> modem_chat: modem_chat_on_unknown_command_received: OK
[00:00:37.473,000] <dbg> modem_cellular: modem_cellular_log_event: event registered
[00:00:37.940,000] <dbg> modem_chat: modem_chat_script_stop: telit_me910g1_periodic_chat_script: complete

