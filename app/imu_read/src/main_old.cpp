/*
 * Copyright (c) 2016 Intel Corporation.
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include "logger.hpp"
//
#include "bmi088.hpp"
#include "coreless_motor.hpp"
#include "led.hpp"
#include "syslink.hpp"
#include "uart_dma.hpp"
#include "usb_console.hpp"
#include <zephyr/drivers/uart.h>
#include <zephyr/logging/log.h>
#include <zephyr/zephyr.h>

// LOG_MODULE_DECLARE(cf_app, LOG_LEVEL_INF);
LOG_MODULE_REGISTER(cf_app);

BUILD_ASSERT(DT_NODE_HAS_COMPAT(DT_CHOSEN(zephyr_console), zephyr_cdc_acm_uart),
             "Console device is not ACM CDC UART device");

// console
const struct device *console_dev = DEVICE_DT_GET(DT_CHOSEN(zephyr_console));

// led's
constexpr static struct gpio_dt_spec red_led_left_dev =
    GPIO_DT_SPEC_GET(DT_ALIAS(led1), gpios);
constexpr static struct gpio_dt_spec green_led_left_dev =
    GPIO_DT_SPEC_GET(DT_ALIAS(led2), gpios);
constexpr static struct gpio_dt_spec green_led_right_dev =
    GPIO_DT_SPEC_GET(DT_ALIAS(led3), gpios);
constexpr static struct gpio_dt_spec red_led_right_dev =
    GPIO_DT_SPEC_GET(DT_ALIAS(led4), gpios);
constexpr static struct gpio_dt_spec blue_led_left_dev =
    GPIO_DT_SPEC_GET(DT_ALIAS(led5), gpios);

// communication peripherals
const static struct device *i2c_dev = DEVICE_DT_GET(DT_NODELABEL(i2c3));
const static struct device *uart6_dev = DEVICE_DT_GET(DT_NODELABEL(usart6));
// const static struct device *spi_dev = DEVICE_DT_GET(DT_NODELABEL(spi1));

// motors
const static struct pwm_dt_spec motor1_dev = PWM_DT_SPEC_GET(DT_ALIAS(motor1));
const static struct pwm_dt_spec motor2_dev = PWM_DT_SPEC_GET(DT_ALIAS(motor2));
const static struct pwm_dt_spec motor3_dev = PWM_DT_SPEC_GET(DT_ALIAS(motor3));
const static struct pwm_dt_spec motor4_dev = PWM_DT_SPEC_GET(DT_ALIAS(motor4));

// temp
constexpr static std::uint8_t buf_size = 20;
static std::uint8_t rx_buf[buf_size]{};
constexpr static std::uint8_t tx_buf[buf_size] = "selva\n";
// constexpr static std::uint8_t ack_buf[buf_size] = "roger\n";
constexpr static std::uint8_t nrf_ack = 'a';

// async callback
static void uart_cb(const struct device *dev, struct uart_event *evt,
                    void *user_data);

int main(void) {
  UsbConsole console(console_dev);

  CorelessMotor motor1(&motor1_dev);
  CorelessMotor motor2(&motor2_dev);
  CorelessMotor motor3(&motor3_dev);
  CorelessMotor motor4(&motor4_dev);

  Led red_led_left(red_led_left_dev);
  Led green_led_left(green_led_left_dev);
  Led green_led_right(green_led_right_dev);
  Led red_led_right(red_led_right_dev);
  Led blue_led_left(blue_led_left_dev);

  BMI088 imu(i2c_dev);

  UartDma uart_dma(uart6_dev);

  Syslink syslink(&uart_dma);

  // if (!device_is_ready(uart6_dev)) {
  //   // printk("UART device not found!");
  //   LOG_ERR("UART device not found!");
  //   return -1;
  // }

  std::int16_t err{};

  // uart_dma.enable_dma_receiving();

  // // set uart async callback
  // err = uart_callback_set(uart6_dev, uart_cb, NULL);
  // if (err) {
  //   printk("Err:%d Could not set uart callback!\n", err);
  //   return err;
  // }

  // // enable uart receiving
  // err = uart_rx_enable(uart6_dev, rx_buf, buf_size, 100);
  // if (err) {
  //   printk("Error %d: Could not enable uart async receive !\n", err);
  //   return err;
  // }

  for (;;) {

    printk("Chip id: %d\n", imu.acc_chip_id());

    // uart_dma.send_dma(&nrf_ack, 1);
    // syslink.systemRequestNRFVersion();

    // syslink.systemRequestShutdown();
    uart_poll_out(uart6_dev, 0xBC);

    green_led_right.toggle();

    k_sleep(K_MSEC(1500));
  }
}

static void uart_cb(const struct device *dev, struct uart_event *evt,
                    void *user_data) {
  std::int16_t err;
  switch (evt->type) {

  // Whole TX buffer was transmitted.
  case UART_TX_DONE:
    // printk("tx done\n");
    break;

    // Transmitting aborted due to timeout or uart_tx_abort call.
  case UART_TX_ABORTED:
    printk("tx aborted\n");
    break;

    // Received data is ready for processing (also generated in some other
    // cases (eg.when buffer is full, When RX timeout occurred etc )  See docs
  case UART_RX_RDY:
    printk("nrf tx recv\n");
    // err = uart_tx(uart6_dev, &nrf_ack, 1, SYS_FOREVER_US);
    // if (err) {
    //   printk("Error %d: Could not send uart async msg\n", err);
    // }
    break;

  /* receiving has started for a new buffer. r, i.e. it’s time to provide a next
   buffer for a seamless switchover to it. For continuous reliable receiving,
   user should provide another RX buffer in response to this event, using
   uart_rx_buf_rsp function*/
  case UART_RX_BUF_REQUEST:
    printk("uart rx buf request\n");
    break;

  // Buffer is no longer used by UART driver.
  case UART_RX_BUF_RELEASED:
    printk("uart rx buf released\n");
    break;

  // RX has been disabled, can be reenabled
  case UART_RX_DISABLED:
    printk("uart rx disabled\n");
    break;

  // RX has stopped due to external event.
  case UART_RX_STOPPED:
    printk("uart rx stopped\n");
    break;
  }
}
