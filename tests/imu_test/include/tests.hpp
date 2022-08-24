#pragma once
#include "bmi088.hpp"
#include "unity.h"
#include <zephyr/zephyr.h>

class IMU_Test {

public:
  IMU_Test();

  // check if we can read the chip id's
  void chipid_test();

  // check if reading from imu works
  void read_test();

private:
  // chip is tests
  static void accel_chipid_test();
  static void gyro_chipid_test();

  // read tests
  static void accel_read_test();
  static void gyro_read_test();

private:
  const static constexpr struct device *i2c_dev =
      DEVICE_DT_GET(DT_NODELABEL(i2c3));

  static BMI088 imu;

  constexpr static std::uint8_t ACC_WHO_AMI = 0x1E;
  constexpr static std::uint8_t GYRO_WHO_AMI = 0x0F;
};

inline BMI088 IMU_Test::imu(i2c_dev);
