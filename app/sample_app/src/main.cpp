#include "devices.hpp"
#include "led.hpp"
#include "usb_console.hpp"
#include <zephyr/zephyr.h>

LOG_MODULE_REGISTER(cf_app);

BUILD_ASSERT(DT_NODE_HAS_COMPAT(DT_CHOSEN(zephyr_console), zephyr_cdc_acm_uart),
             "Console device is not ACM CDC UART device");

int main(void) {
  UsbConsole console(devices::console);
  Led red_led_left(devices::red_led_left);

  for (;;) {

    red_led_left.toggle();

    k_sleep(K_MSEC(500));
  }
}
