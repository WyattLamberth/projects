#include "raylib.h"
#include "raymath.h"
#include <iostream>

struct window_ctx {
  const char *title = "paint-app";
  const int width = GetScreenWidth();
  const int height = GetScreenHeight();
  const int refresh_rate = GetMonitorRefreshRate(0);
};

void clear_canvas(RenderTexture &canvas) {
  BeginTextureMode(canvas);
  ClearBackground(BLACK);
  EndTextureMode();
}

int main() {
  window_ctx window;
  InitWindow(window.width, window.height, window.title);
  SetTargetFPS(window.refresh_rate);

  Vector2 mouse_pos_prev = GetMousePosition();
  Vector2 mouse_pos;
  RenderTexture canvas = LoadRenderTexture(window.width, window.height);

  float line_thickness = 1.f;
  Color line_color = RED;

  bool lmb_down = false;
  bool rmb_down = false;

  clear_canvas(canvas);

  while (!WindowShouldClose()) {
    // update stuff here
    //
    mouse_pos = GetMousePosition();
    lmb_down = IsMouseButtonDown(MOUSE_LEFT_BUTTON);
    rmb_down = IsMouseButtonDown(MOUSE_RIGHT_BUTTON);

    // texture start
    BeginTextureMode(canvas);
    DrawCircleV(mouse_pos_prev, line_thickness * 5.f, line_color);
    DrawCircleV(mouse_pos, line_thickness * 5.f, line_color);
    DrawLineEx(mouse_pos_prev, mouse_pos, line_thickness, line_color);

    // texture end
    EndTextureMode();
    mouse_pos_prev = GetMousePosition();

    BeginDrawing();

    DrawTextureRec(canvas.texture,
                   (Rectangle){0.0f, 0.0f, (float)canvas.texture.width,
                               (float)-canvas.texture.height},
                   Vector2Zero(), WHITE);
    if (!lmb_down)
      DrawCircleLinesV(mouse_pos, line_thickness, line_color);
    EndDrawing();
  }

  UnloadRenderTexture(canvas);
  CloseWindow();
  return 0;
}
