#include "usb_console.hpp"
#include <zephyr/zephyr.h>

BUILD_ASSERT(DT_NODE_HAS_COMPAT(DT_CHOSEN(zephyr_console), zephyr_cdc_acm_uart),
             "Console device is not ACM CDC UART device");
// console
const struct device *console_dev = DEVICE_DT_GET(DT_CHOSEN(zephyr_console));

const int arr_size = 10;
const uint16_t n_itr = 1000;
volatile int arr[arr_size];

void do_work() {
  for (uint8_t i = 0; i < arr_size; i++) {
    arr[i] = 5 * i;
  }
  k_busy_wait(1000);
}

class Base {
public:
  virtual void disp() { do_work(); }
};

class Derived : public Base {
public:
  void disp() final { do_work(); }

  void disp_normal() { do_work(); }
};

int main() {

  UsbConsole console(console_dev);

  Base b_obj;
  Derived d_obj;

  uint64_t start{}, end{};

  //---------- Derived  class virtual func --------------//

  // start timer
  start = k_uptime_get();

  for (int i = 0; i < n_itr; i++) {
    d_obj.disp();
  }

  // stop the timer
  end = k_uptime_get();

  uint64_t t1_ms = end - start;

  //---------- Derived  class non-virtual func--------------//

  // start the timer
  start = k_uptime_get();

  for (int i = 0; i < n_itr; i++) {
    d_obj.disp_normal();
  }

  // stop the timer
  end = k_uptime_get();

  uint64_t t2_ms = end - start;

  //---------- Display result--------------//

  printk("derived class virtual: %lld ms\n", t1_ms);
  printk("derived class normal: %lld ms\n\n", t2_ms);
}