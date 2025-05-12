#include "../../additional/slider.hpp"
#include <cmath>
#include <raylib.h>
#include <raymath.h>

int my_lerp(int a, int b, float t) { return (1 - cos(t * M_PI)) / 2; }

double CosineInterpolate(double y1, double y2, double mu) {
  double mu2;

  mu2 = (1 - cos(mu * M_PI)) / 2;
  return (y1 * (1 - mu2) + y2 * mu2);
}

int main() {
  InitWindow(800, 400, "Lerp");
  int begin = 50;
  int end = 750;

  int b = 30;
  int a = 350;

  while (!WindowShouldClose()) {

    BeginDrawing();
    ClearBackground(RAYWHITE);
    for (int i = begin; i <= end; i++) {
      float t = (float)(i - begin) / (float)(end - begin);
      int value = CosineInterpolate(a, b, t);
      DrawPixel(i, value, BLACK);
    }
    EndDrawing();
  }

  CloseWindow();
  return 0;
}
