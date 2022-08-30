#pragma once
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/zephyr.h>

struct devices {
  // console
  struct device constexpr const static *const console =
      DEVICE_DT_GET(DT_CHOSEN(zephyr_console));

  // led's
  struct gpio_dt_spec constexpr static red_led_left =
      GPIO_DT_SPEC_GET(DT_ALIAS(led1), gpios);
  struct gpio_dt_spec constexpr static green_led_left =
      GPIO_DT_SPEC_GET(DT_ALIAS(led2), gpios);
  struct gpio_dt_spec constexpr static green_led_right =
      GPIO_DT_SPEC_GET(DT_ALIAS(led3), gpios);
  struct gpio_dt_spec constexpr static red_led_right =
      GPIO_DT_SPEC_GET(DT_ALIAS(led4), gpios);
  struct gpio_dt_spec constexpr static blue_led_left =
      GPIO_DT_SPEC_GET(DT_ALIAS(led5), gpios);

  // communication peripherals
  struct device constexpr const static *const i2c =
      DEVICE_DT_GET(DT_NODELABEL(i2c3));
  // const static struct device *uart6 =
  // DEVICE_DT_GET(DT_NODELABEL(usart6)); const static struct device *spi =
  // DEVICE_DT_GET(DT_NODELABEL(spi1));

  // motors
  struct pwm_dt_spec constexpr const static motor1 =
      PWM_DT_SPEC_GET(DT_ALIAS(motor1));
  struct pwm_dt_spec constexpr const static motor2 =
      PWM_DT_SPEC_GET(DT_ALIAS(motor2));
  struct pwm_dt_spec constexpr const static motor3 =
      PWM_DT_SPEC_GET(DT_ALIAS(motor3));
  struct pwm_dt_spec constexpr const static motor4 =
      PWM_DT_SPEC_GET(DT_ALIAS(motor4));
};