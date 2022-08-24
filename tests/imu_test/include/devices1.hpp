#pragma once

#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/zephyr.h>

struct devices {
  // console
  constexpr const static struct device *console =
      DEVICE_DT_GET(DT_CHOSEN(zephyr_console));
};
