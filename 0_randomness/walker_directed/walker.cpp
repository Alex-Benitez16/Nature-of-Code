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
  std::uniform_real_distribution<float> dist;

public:
  Walker() : x(0), y(0), dist(0.0f, 1.0f) {}
  Walker(int width, int height)
      : x(width / 2), y(height / 2), dist(0.0f, 1.0f) {}

  void move_to_mouse(Vector2 mouse) {
    if (x < mouse.x)
      x++;
    else if (x > mouse.x)
      x--;

    if (y < mouse.y)
      y++;
    else if (y > mouse.y)
      y--;
  }

  void step(Vector2 mouse) {
    float random_choice = dist(gen);

    if (random_choice < 0.2) {
      move_to_mouse(mouse);
    } else if (random_choice < 0.4) {
      x++;
    } else if (random_choice < 0.6) {
      x--;
    } else if (random_choice < 0.8) {
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

void update() {
  Vector2 mouse = GetMousePosition();
  my_walker.step(mouse);
}

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

  while (!WindowShouldClose()) {
    update();
    draw();
  }

  end();
  return 0;
}
