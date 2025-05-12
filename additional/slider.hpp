#ifndef SLIDER_H
#define SLIDER_H

#include <raylib.h>

class Slider {
private:
  Vector2 absolute_position;
  int length;
  int min;
  int max;
  int circ_x;
  int circ_radius;
  bool is_beign_pressed;

public:
  Slider()
      : absolute_position((Vector2){0., 0.}), length(0), min(0), max(0),
        circ_x(0), circ_radius(0), is_beign_pressed(false) {}
  Slider(int x, int y, int set_length, int min_value, int max_value) {
    absolute_position = (Vector2){(float)x, (float)y};
    length = set_length;
    min = min_value;
    max = max_value;
    circ_x = length / 2;
    circ_radius = 7;
    is_beign_pressed = false;
  }

  void draw() {
    DrawRectangle(absolute_position.x, absolute_position.y, length, 5, BLACK);
    DrawRectangle(absolute_position.x + 1, absolute_position.y + 1, length - 2,
                  3, DARKGRAY);
    DrawCircle(absolute_position.x + circ_x, absolute_position.y + 2,
               circ_radius, BLACK);
    DrawCircle(absolute_position.x + circ_x, absolute_position.y + 2,
               circ_radius - 1, BLUE);
  }

  bool are_valid_bounds(int x) {
    return x >= absolute_position.x && x <= absolute_position.x + length;
  }

  void is_within_circle() {
    Vector2 mouse = GetMousePosition();
    int left = absolute_position.x + circ_x - circ_radius;
    int right = absolute_position.x + circ_x + circ_radius;
    int up = absolute_position.y - circ_radius;
    int down = absolute_position.y + circ_radius;

    if (mouse.x >= left && mouse.x <= right && mouse.y >= up &&
        mouse.y <= down && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
      is_beign_pressed = true;
    } else if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
      is_beign_pressed = false;
    }
  }

  void move_slider() {
    Vector2 mouse = GetMousePosition();
    is_within_circle();
    if (are_valid_bounds(mouse.x) && IsMouseButtonDown(MOUSE_BUTTON_LEFT) &&
        is_beign_pressed) {
      circ_x = mouse.x - absolute_position.x;
    }
  }

  float get_value() {
    return min + ((float)circ_x / (float)length) * (max - min);
  }
};

#endif
