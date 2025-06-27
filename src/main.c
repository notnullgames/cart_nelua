#include "null0.h"

int main() {
  // no update needed, since this does not change
  u32 bg = image_gradient(SCREEN_WIDTH, SCREEN_HEIGHT, BLUE, GREEN, RED, YELLOW);
  draw_image(bg, 0, 0);
  draw_text(FONT_DEFAULT, "Welcome to null0!", 230, 230, BLACK);
  draw_text(FONT_DEFAULT, "Welcome to null0!", 231, 231, RAYWHITE);
}