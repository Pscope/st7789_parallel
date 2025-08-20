#include "st7789_parallel.h"
#include "esp_lcd_panel_interface.h"
#include "esp_lcd_panel_ops.h"
#include "esp_lcd_panel_vendor.h"

#define LCD_DC     5
#define LCD_WR     6
#define LCD_CS     4
#define LCD_RST    3
#define LCD_RD     7

#define LCD_D0     8
#define LCD_D1     9
#define LCD_D2     10
#define LCD_D3     11
#define LCD_D4     12
#define LCD_D5     13
#define LCD_D6     14
#define LCD_D7     15

esp_lcd_panel_handle_t panel_handle = NULL;

void ST7789ParallelDisplay::setup() {
  esp_lcd_i80_bus_handle_t i80_bus = NULL;

  esp_lcd_i80_bus_config_t bus_config = {
    .dc_gpio_num = LCD_DC,
    .wr_gpio_num = LCD_WR,
    .data_gpio_nums = {LCD_D0, LCD_D1, LCD_D2, LCD_D3, LCD_D4, LCD_D5, LCD_D6, LCD_D7},
    .bus_width = 8,
    .max_transfer_bytes = 320 * 100 * sizeof(uint16_t),
  };
  ESP_ERROR_CHECK(esp_lcd_new_i80_bus(&bus_config, &i80_bus));

  esp_lcd_panel_io_handle_t io_handle = NULL;
  esp_lcd_panel_io_i80_config_t io_config = {
    .cs_gpio_num = LCD_CS,
    .pclk_hz = 10 * 1000 * 1000,
    .trans_queue_depth = 10,
    .lcd_cmd_bits = 8,
    .lcd_param_bits = 8,
    .dc_levels = {
      .dc_idle_level = 0,
      .dc_cmd_level = 0,
      .dc_dummy_level = 0,
      .dc_data_level = 1,
    },
  };
  ESP_ERROR_CHECK(esp_lcd_new_panel_io_i80(i80_bus, &io_config, &io_handle));

  esp_lcd_panel_dev_config_t panel_config = {
    .reset_gpio_num = LCD_RST,
    .rgb_ele_order = LCD_RGB_ELEMENT_ORDER_RGB,
    .bits_per_pixel = 16,
  };
  ESP_ERROR_CHECK(esp_lcd_new_panel_st7789(io_handle, &panel_config, &panel_handle));
  ESP_ERROR_CHECK(esp_lcd_panel_reset(panel_handle));
  ESP_ERROR_CHECK(esp_lcd_panel_init(panel_handle));
  ESP_ERROR_CHECK(esp_lcd_panel_disp_on_off(panel_handle, true));
}

void ST7789ParallelDisplay::update() {
  // Fill screen with red for testing
  static uint16_t color_data[170 * 320];
  for (int i = 0; i < 170 * 320; ++i) {
    color_data[i] = 0xF800; // RGB565 red
  }
  ESP_ERROR_CHECK(esp_lcd_panel_draw_bitmap(panel_handle, 0, 0, 170, 320, color_data));
}

void ST7789ParallelDisplay::draw_pixel(int x, int y, esphome::Color color) {
  // Optional: implement per-pixel drawing if needed
}
