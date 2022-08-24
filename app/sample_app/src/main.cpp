#include "usb_console.hpp"
#include <zephyr/zephyr.h>

LOG_MODULE_REGISTER(cf_app);

BUILD_ASSERT(DT_NODE_HAS_COMPAT(DT_CHOSEN(zephyr_console), zephyr_cdc_acm_uart),
             "Console device is not ACM CDC UART device");

// console
const struct device *console_dev = DEVICE_DT_GET(DT_CHOSEN(zephyr_console));

int main(void) {
  UsbConsole console(console_dev);

  for (;;) {

    printk("Acc chip id\n");

    k_sleep(K_MSEC(1500));
  }
}
