#include "bmi088.hpp"
#include "coreless_motor.hpp"
#include "led.hpp"
#include "uart_dma.hpp"
#include "usb_console.hpp"
#include <zephyr/logging/log.h>
#include <zephyr/zephyr.h>

LOG_MODULE_REGISTER(cf_app);

BUILD_ASSERT(DT_NODE_HAS_COMPAT(DT_CHOSEN(zephyr_console), zephyr_cdc_acm_uart),
             "Console device is not ACM CDC UART device");

// console
const struct device *console_dev = DEVICE_DT_GET(DT_CHOSEN(zephyr_console));

// communication peripherals
const static struct device *i2c_dev = DEVICE_DT_GET(DT_NODELABEL(i2c3));

int main(void) {
  UsbConsole console(console_dev);

  BMI088 imu(i2c_dev);
  imu.acc.wakeup();
  imu.gyro.wakeup();

  printk("Acc chip id: %d\n", imu.acc.chip_id());
  printk("Gyro chip id: %d\n", imu.gyro.chip_id());

  uint64_t start{}, end{};
  const int no_readings = 1000;

  //---------- Derived  class virtual func --------------//

  // start timer
  start = k_uptime_get();

  for (int i = 0; i < no_readings; i++) {

    imu.acc.read();

    k_busy_wait(1000);
  }
  // end timer
  end = k_uptime_get();
  uint64_t t1 = end - start;

  //---------- Derived  class non-virtual func --------------//

  // start timer
  start = k_uptime_get();

  for (int i = 0; i < no_readings; i++) {

    imu.acc.read_non_virtual();

    k_busy_wait(1000);
  }
  // end timer
  end = k_uptime_get();

  uint64_t t2 = end - start;

  printk("virtual: %lld ms\n", t1);
  printk("non-virtual: %lld ms\n", t2);
  printk("\n");
}
