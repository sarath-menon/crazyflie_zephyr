# SPDX-License-Identifier: Apache-2.0
list(APPEND ZEPHYR_EXTRA_MODULES
  ${CMAKE_CURRENT_SOURCE_DIR}/robotics_lib
  )


cmake_minimum_required(VERSION 3.20.0)
set(BOARD_ROOT ${CMAKE_SOURCE_DIR})
set(BOARD bitcraze_crazyflie)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(console)


option(TESTING_MODE "Enables unit testing" OFF)

set(APP_NAME imu_read)

set(TESTING_MODE OFF)
set(TEST_NAME imu_test)

if(TESTING_MODE)
    add_subdirectory(tests)
    set(APP_ENABLED OFF)
endif()

if(NOT TESTING_MODE)
add_subdirectory(app)
endif()

# add_subdirectory(robotics_lib)
