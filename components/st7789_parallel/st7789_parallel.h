#include "esphome.h"
#include "esphome/components/display/display_buffer.h"

class ST7789ParallelDisplay : public esphome::display::DisplayBuffer {
 public:
  void setup() override;
  void update() override;
  void draw_pixel(int x, int y, esphome::Color color) override;
  int get_width() override { return 170; }
  int get_height() override { return 320; }
};
