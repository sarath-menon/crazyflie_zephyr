#include "bmi088.hpp"
#include "coreless_motor.hpp"
#include "devices.hpp"
#include "led.hpp"
#include "uart_dma.hpp"
#include "usb_console.hpp"
#include <cstdio>
#include <string>
#include <zephyr/logging/log.h>
#include <zephyr/zephyr.h>

LOG_MODULE_REGISTER(cf_app);

BUILD_ASSERT(DT_NODE_HAS_COMPAT(DT_CHOSEN(zephyr_console), zephyr_cdc_acm_uart),
             "Console device is not ACM CDC UART device");

int main(void) {
  UsbConsole console(devices::console);

  rl::actuators::motors::Coreless motor1(devices::motor1);
  rl::actuators::motors::Coreless motor2(devices::motor2);
  rl::actuators::motors::Coreless motor3(devices::motor3);
  rl::actuators::motors::Coreless motor4(devices::motor4);

  rl::io_devices::Led red_led_left(devices::red_led_left);
  rl::io_devices::Led green_led_left(devices::green_led_left);
  rl::io_devices::Led green_led_right(devices::green_led_right);
  rl::io_devices::Led red_led_right(devices::red_led_right);
  rl::io_devices::Led blue_led_left(devices::blue_led_left);

  rl::sensors::imu::BMI088 imu(devices::i2c);
  imu.acc.wakeup();
  imu.gyro.wakeup();

  printf("Acc chip status: %d\n", imu.acc.check_device_exists());
  printf("Gyro chip status: %d\n", imu.gyro.check_device_exists());

  for (;;) {

    imu.acc.read();

    imu.gyro.read();

    printk("\n");

    k_sleep(K_MSEC(5));
  }
}
