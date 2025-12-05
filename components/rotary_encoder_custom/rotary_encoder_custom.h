#pragma once

#include "esphome/core/component.h"
#include "esphome/core/hal.h"                  // brings in GPIOPin
#include "esphome/components/sensor/sensor.h"

namespace esphome {
namespace rotary_encoder_custom {

// If you still miss steps at high speed, raise this to 6 or 7
static constexpr uint8_t DEBOUNCE_TICKS = 0;

class RotaryEncoderCustom : public Component, public sensor::Sensor {
 public:
  // These take the pointer types that esphome::gpio_pin_expression returns
  void set_pin_a(GPIOPin *pin_a) { this->pin_a_ = pin_a; }
  void set_pin_b(GPIOPin *pin_b) { this->pin_b_ = pin_b; }
  void set_min_value(int *min_value) {this->min_value = min_value;}
  void set_max_value(int *max_value) {this->max_value = max_value;}
  
  void set_publish_initial_value(bool v) { this->publish_initial_value_ = v; }

  void setup() override;
  void dump_config() override;
  void loop() override;

 protected:
  GPIOPin *pin_a_;
  GPIOPin *pin_b_;
  int32_t *min_value_;
  int32_t *max_value_;

  bool publish_initial_value_{false};

  int32_t counter_{0};

  // Debounce state for each channel
  bool last_a_{false};
  bool last_b_{false};
  uint8_t debounce_a_cnt_{0};
  uint8_t debounce_b_cnt_{0};

  void process_channel(bool current, bool &prev,
                       uint8_t &debounce_cnt, bool clockwise);
  void read_encoder();
};

}  // namespace rotary_encoder_custom
}  // namespace esphome
