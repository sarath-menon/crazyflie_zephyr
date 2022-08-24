#include "tests.hpp"

IMU_Test::IMU_Test() {
  imu.acc.wakeup();
  imu.gyro.wakeup();
}

void IMU_Test::accel_chipid_test() {
  int8_t chip_id = imu.acc.chip_id();
  TEST_ASSERT_EQUAL_UINT8(ACC_WHO_AMI, chip_id);
}

void IMU_Test::gyro_chipid_test() {
  int8_t chip_id = imu.gyro.chip_id();
  TEST_ASSERT_EQUAL_UINT8(GYRO_WHO_AMI, chip_id);
}

void IMU_Test::accel_read_test() {
  int8_t err = imu.acc.read();
  TEST_ASSERT_EQUAL_UINT8(0, err);
}

void IMU_Test::gyro_read_test() {
  int8_t err = imu.gyro.read();
  TEST_ASSERT_EQUAL_UINT8(0, err);
}

void IMU_Test::chipid_test() {
  RUN_TEST(accel_chipid_test);
  RUN_TEST(gyro_chipid_test);
}

void IMU_Test::read_test() {
  RUN_TEST(accel_read_test);
  RUN_TEST(gyro_read_test);
}
