#include "usb_console.hpp"
#include <zephyr/zephyr.h>

// console
const struct device *console_dev = DEVICE_DT_GET(DT_CHOSEN(zephyr_console));

const uint8_t arr_size = 100;
const uint16_t n_itr = 1000;

int main() {
  UsbConsole console(console_dev);
  volatile int arr[arr_size];

  // start timer
  uint64_t start = k_uptime_get();

  for (uint16_t i = 0; i < n_itr; i++) {

    // do the work here
    for (uint8_t i = 0; i < arr_size; i++) {
      arr[i] = 5 * i;
    }
  }

  // stop timer
  uint64_t end = k_uptime_get();

  //---------- Display result--------------//

  uint64_t elapsed_time = end - start;
  printk("time taken:%lld ms\n", elapsed_time);
}
