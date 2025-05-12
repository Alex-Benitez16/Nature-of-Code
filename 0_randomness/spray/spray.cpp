#include "../../additional/slider.hpp"
#include <random>
#include <raylib.h>

#define WIDTH 800
#define HEIGHT 400

// NOTE: not gonna separate into functions bc of time

int main() {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::normal_distribution<float> dist_2(0, 30);

  InitWindow(WIDTH, HEIGHT, "Spray paint");

  Slider my_slider(10, 10, 100, 5, 20);

  SetTargetFPS(60);

  RenderTexture2D canvas = LoadRenderTexture(WIDTH, HEIGHT);
  BeginTextureMode(canvas);
  ClearBackground(RAYWHITE);
  EndTextureMode();

  while (!WindowShouldClose()) {

    my_slider.is_within_circle();
    my_slider.move_slider();

    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawTextureRec(canvas.texture,
                   (Rectangle){0, 0, (float)WIDTH, (float)-HEIGHT},
                   (Vector2){0, 0}, RAYWHITE);
    my_slider.draw();
    EndDrawing();

    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
      for (int i = 0; i < 30; i++) {
        Vector2 mouse = GetMousePosition();
        std::normal_distribution<float> dist(0, my_slider.get_value());
        int x = dist(gen);
        int y = dist(gen);
        // Color color = {(unsigned char)dist_2(gen),
        //                (unsigned char)(121 + dist_2(gen)),
        //                (unsigned char)(241 + dist_2(gen)), 255};
        BeginTextureMode(canvas);
        DrawPixel(mouse.x + x, mouse.y + y, BLUE);
        EndTextureMode();
      }
    }
  }

  UnloadRenderTexture(canvas);
  CloseWindow();
  return 0;
}
