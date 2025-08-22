#include "esphome.h"

class ST7789V3Parallel : public Component {
 public:
  void setup() override;
  void loop() override;

 private:
  void write_bus(uint8_t value);
  void write_command(uint8_t cmd);
  void write_data(uint8_t data);
};
