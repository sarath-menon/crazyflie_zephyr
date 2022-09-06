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
  constexpr static struct gpio_dt_spec blue_led =
      GPIO_DT_SPEC_GET(DT_ALIAS(led5), gpios);
};