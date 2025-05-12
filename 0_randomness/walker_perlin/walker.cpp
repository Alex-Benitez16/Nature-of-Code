#include "../../additional/perlin.hpp"
#include <random>
#include <raylib.h>
#define WIDTH 640
#define HEIGHT 240

std::random_device rd;
std::mt19937 gen(rd());

class Walker {
private:
  int x;
  int y;

public:
  Walker() : x(0), y(0) { init_perlin(); }
  Walker(int width, int height) : x(width / 2), y(height / 2) { init_perlin(); }
  void step(double t) {
    double choice = perlin(t);

    if (choice < 0.25) {
      x++;
    } else if (choice < 0.5) {
      x--;
    } else if (choice < 0.75) {
      y++;
    } else {
      y--;
    }

    // Keep the walker within window bounds
    x = x < 0 ? 0 : (x >= WIDTH ? WIDTH - 1 : x);
    y = y < 0 ? 0 : (y >= HEIGHT ? HEIGHT - 1 : y);
  }
  void show(RenderTexture2D *canvas) {
    // Draw to the provided canvas
    BeginTextureMode(*canvas);
    DrawPixel(x, y, BLACK);
    EndTextureMode();
  }
  int get_x() const { return x; }
  int get_y() const { return y; }
};

Walker my_walker;
RenderTexture2D canvas;

void init() {
  InitWindow(WIDTH, HEIGHT, "Walker with Trail");
  my_walker = Walker(WIDTH, HEIGHT);
  SetTargetFPS(60);

  // Create a render texture to serve as our persistent canvas
  canvas = LoadRenderTexture(WIDTH, HEIGHT);

  // Initialize the canvas with a white background
  BeginTextureMode(canvas);
  ClearBackground(RAYWHITE);
  EndTextureMode();
}

void update(double dt) { my_walker.step(dt); }

void draw() {
  my_walker.show(&canvas); // Draw to the canvas

  BeginDrawing();
  ClearBackground(RAYWHITE); // Clear the screen to prevent artifacts

  // Draw the canvas (which contains all previous steps) to the screen
  // Note: We need to flip the texture vertically because of OpenGL coordinates
  DrawTextureRec(canvas.texture,
                 (Rectangle){0, 0, (float)canvas.texture.width,
                             (float)-canvas.texture.height},
                 (Vector2){0, 0}, WHITE);

  EndDrawing();
}

void end() {
  UnloadRenderTexture(canvas);
  CloseWindow();
}

int main() {
  init();
  SetTargetFPS(60);
  int perlin_var = 0;

  while (!WindowShouldClose()) {
    update(perlin_var++);
    draw();
  }

  end();
  return 0;
}
