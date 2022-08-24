#include "unity.h"
#include "usb_console.hpp"
#include <zephyr/zephyr.h>

LOG_MODULE_REGISTER(cf_app);

BUILD_ASSERT(DT_NODE_HAS_COMPAT(DT_CHOSEN(zephyr_console), zephyr_cdc_acm_uart),
             "Console device is not ACM CDC UART device");

// console
const struct device *console_dev = DEVICE_DT_GET(DT_CHOSEN(zephyr_console));
const int a = 2;

void setUp(void) {
  // set stuff up here
}

void tearDown(void) {
  // clean stuff up here
}

void sample_test(void) { TEST_ASSERT_EQUAL(2, a); }

int main(void) {
  UsbConsole console(console_dev);

  UNITY_BEGIN();
  RUN_TEST(sample_test);

  return UNITY_END();
}
