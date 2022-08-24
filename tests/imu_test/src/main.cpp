#include "bmi088.hpp"
#include "devices1.hpp"
#include "tests.hpp"
#include "unity.h"
#include "usb_console.hpp"
#include <zephyr/zephyr.h>

LOG_MODULE_REGISTER(cf_app);

BUILD_ASSERT(DT_NODE_HAS_COMPAT(DT_CHOSEN(zephyr_console), zephyr_cdc_acm_uart),
             "Console device is not ACM CDC UART device");

int main(void) {

  UsbConsole console(devices::console);

  IMU_Test imu_tester;

  UNITY_BEGIN();

  imu_tester.chipid_test();
  imu_tester.read_test();

  return UNITY_END();
}

void setUp(void) {}

void tearDown(void) {}
