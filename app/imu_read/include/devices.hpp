#pragma once
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/zephyr.h>

struct devices {
  // console
  constexpr const static struct device *console =
      DEVICE_DT_GET(DT_CHOSEN(zephyr_console));

  // led's
  constexpr static struct gpio_dt_spec red_led_left =
      GPIO_DT_SPEC_GET(DT_ALIAS(led1), gpios);
  constexpr static struct gpio_dt_spec green_led_left =
      GPIO_DT_SPEC_GET(DT_ALIAS(led2), gpios);
  constexpr static struct gpio_dt_spec green_led_right =
      GPIO_DT_SPEC_GET(DT_ALIAS(led3), gpios);
  constexpr static struct gpio_dt_spec red_led_right =
      GPIO_DT_SPEC_GET(DT_ALIAS(led4), gpios);
  constexpr static struct gpio_dt_spec blue_led_left =
      GPIO_DT_SPEC_GET(DT_ALIAS(led5), gpios);

  // communication peripherals
  constexpr const static struct device *i2c = DEVICE_DT_GET(DT_NODELABEL(i2c3));
  // const static struct device *uart6 =
  // DEVICE_DT_GET(DT_NODELABEL(usart6)); const static struct device *spi =
  // DEVICE_DT_GET(DT_NODELABEL(spi1));

  // motors
  constexpr const static struct pwm_dt_spec motor1 =
      PWM_DT_SPEC_GET(DT_ALIAS(motor1));
  constexpr const static struct pwm_dt_spec motor2 =
      PWM_DT_SPEC_GET(DT_ALIAS(motor2));
  constexpr const static struct pwm_dt_spec motor3 =
      PWM_DT_SPEC_GET(DT_ALIAS(motor3));
  constexpr const static struct pwm_dt_spec motor4 =
      PWM_DT_SPEC_GET(DT_ALIAS(motor4));
};