#include "bmi088.hpp"
#include "coreless_motor.hpp"
#include "devices.hpp"
#include "led.hpp"
#include "uart_dma.hpp"
#include "usb_console.hpp"
#include <zephyr/logging/log.h>
#include <zephyr/zephyr.h>

LOG_MODULE_REGISTER(cf_app);

BUILD_ASSERT(DT_NODE_HAS_COMPAT(DT_CHOSEN(zephyr_console), zephyr_cdc_acm_uart),
             "Console device is not ACM CDC UART device");

int main(void) {
  UsbConsole console(devices::console);

  CorelessMotor motor1(devices::motor1);
  CorelessMotor motor2(devices::motor2);
  CorelessMotor motor3(devices::motor3);
  CorelessMotor motor4(devices::motor4);

  Led red_led_left(devices::red_led_left);
  Led green_led_left(devices::green_led_left);
  Led green_led_right(devices::green_led_right);
  Led red_led_right(devices::red_led_right);
  Led blue_led_left(devices::blue_led_left);

  BMI088 imu(devices::i2c);
  imu.acc.wakeup();
  imu.gyro.wakeup();

  //   std::int16_t err{};

  // UartDma uart_dma(uart6);
  // uart_dma.enable_dma_receiving();

  printk("Acc chip id: %d\n", imu.acc.chip_id());
  printk("Gyro chip id: %d\n", imu.gyro.chip_id());

  for (;;) {

    imu.acc.read();

    imu.gyro.read();

    printk("\n");

    k_sleep(K_MSEC(5));
  }
}
