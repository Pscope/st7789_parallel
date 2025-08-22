#include "st7789v3_parallel.h"

#define LCD_WR   GPIO_NUM_6
#define LCD_RD   GPIO_NUM_7
#define LCD_DC   GPIO_NUM_5
#define LCD_CS   GPIO_NUM_4
#define LCD_RES  GPIO_NUM_3

#define LCD_D0   GPIO_NUM_8

void ST7789V3Parallel::setup() {
  gpio_set_direction(LCD_WR, GPIO_MODE_OUTPUT);
  gpio_set_direction(LCD_RD, GPIO_MODE_OUTPUT);
  gpio_set_direction(LCD_DC, GPIO_MODE_OUTPUT);
  gpio_set_direction(LCD_CS, GPIO_MODE_OUTPUT);
  gpio_set_direction(LCD_RES, GPIO_MODE_OUTPUT);

  gpio_set_level(LCD_RD, 1);
  gpio_set_level(LCD_CS, 0);
  gpio_set_level(LCD_RES, 1);

  for (int i = 0; i < 8; i++) {
    gpio_set_direction((gpio_num_t)(LCD_D0 + i), GPIO_MODE_OUTPUT);
  }

  // Reset sequence
  gpio_set_level(LCD_RES, 0);
  delay(50);
  gpio_set_level(LCD_RES, 1);
  delay(120);

  // Initialization sequence
  write_command(0x11); delay(120);
  write_command(0x3A); write_data(0x55);
  write_command(0x36); write_data(0x00);
  write_command(0x21);
  write_command(0xB2); write_data(0x0C); write_data(0x0C); write_data(0x00); write_data(0x33); write_data(0x33);
  write_command(0xB7); write_data(0x35);
  write_command(0xBB); write_data(0x2B);
  write_command(0xC0); write_data(0x2C);
  write_command(0xC2); write_data(0x01);
  write_command(0xC3); write_data(0x0B);
  write_command(0xC4); write_data(0x20);
  write_command(0xC6); write_data(0x0F);
  write_command(0xD0); write_data(0xA4); write_data(0xA1);
  write_command(0xE0);
  write_data(0xD0); write_data(0x04); write_data(0x0D); write_data(0x11); write_data(0x13);
  write_data(0x2B); write_data(0x3F); write_data(0x54); write_data(0x4C); write_data(0x18);
  write_data(0x0D); write_data(0x0B); write_data(0x1F); write_data(0x23);
  write_command(0xE1);
  write_data(0xD0); write_data(0x04); write_data(0x0C); write_data(0x11); write_data(0x13);
  write_data(0x2C); write_data(0x3F); write_data(0x44); write_data(0x51); write_data(0x2F);
  write_data(0x1F); write_data(0x1F); write_data(0x20); write_data(0x23);
  write_command(0x29);
}

void ST7789V3Parallel::loop() {
  // Optional: refresh logic
}

void ST7789V3Parallel::write_bus(uint8_t value) {
  for (int i = 0; i < 8; i++) {
    gpio_set_level((gpio_num_t)(LCD_D0 + i), (value >> i) & 0x01);
  }
}

void ST7789V3Parallel::write_command(uint8_t cmd) {
  gpio_set_level(LCD_DC, 0);
  write_bus(cmd);
  gpio_set_level(LCD_WR, 0);
  gpio_set_level(LCD_WR, 1);
}

void ST7789V3Parallel::write_data(uint8_t data) {
  gpio_set_level(LCD_DC, 1);
  write_bus(data);
  gpio_set_level(LCD_WR, 0);
  gpio_set_level(LCD_WR, 1);
}
