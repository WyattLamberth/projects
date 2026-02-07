#include "raylib.h"
#include "raymath.h"
#include <iostream>

struct window_ctx {
  const char *title = "paint-app";
  const int width = GetScreenWidth();
  const int height = GetScreenHeight();
  const int refresh_rate = GetMonitorRefreshRate(0);
};

struct mouse_ctx {
  Vector2 pos_prev = GetMousePosition();
  Vector2 pos;
  bool lmb_down = false;
  bool rmb_down = false;
};

void clear_canvas(RenderTexture &canvas) {
  BeginTextureMode(canvas);
  ClearBackground(BLACK);
  EndTextureMode();
}

int main() {
  window_ctx window;
  mouse_ctx mouse;
  InitWindow(window.width, window.height, window.title);
  SetTargetFPS(window.refresh_rate);

  RenderTexture canvas = LoadRenderTexture(window.width, window.height);

  float line_thickness = 1.f;
  Color line_color = RED;

  clear_canvas(canvas);

  while (!WindowShouldClose()) {
    // update stuff here
    //
    mouse.pos = GetMousePosition();
    mouse.lmb_down = IsMouseButtonDown(MOUSE_LEFT_BUTTON);
    mouse.rmb_down = IsMouseButtonDown(MOUSE_RIGHT_BUTTON);

    if (mouse.lmb_down) {
      // texture start
      BeginTextureMode(canvas);
      DrawCircleV(mouse.pos_prev, line_thickness * 5.f, line_color);
      DrawCircleV(mouse.pos, line_thickness * 5.f, line_color);
      DrawLineEx(mouse.pos_prev, mouse.pos, line_thickness, line_color);
      // texture end
      EndTextureMode();
    } else {
      mouse.pos_prev = GetMousePosition();
    }
    // draw start
    BeginDrawing();

    DrawTextureRec(canvas.texture,
                   (Rectangle){0.0f, 0.0f, (float)canvas.texture.width,
                               (float)-canvas.texture.height},
                   Vector2Zero(), WHITE);
    if (mouse.lmb_down)
      DrawCircleLinesV(mouse.pos, line_thickness, line_color);
    if (mouse.rmb_down)
      clear_canvas(canvas);

    // draw end
    EndDrawing();
  }

  UnloadRenderTexture(canvas);
  CloseWindow();
  return 0;
}
