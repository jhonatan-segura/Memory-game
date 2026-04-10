#include <iostream>
#include <raylib.h>
#include "Game.hpp"

int main() {
  Color grey = {29, 29, 27, 255};
  InitWindow(800, 850, "Memory Game");

  SetTargetFPS(60);

  Game game;

  while (!WindowShouldClose())
  {
    game.HandleInput();
    game.Update();

    BeginDrawing();
    ClearBackground(grey);
    game.Draw();
    EndDrawing();
  }

  CloseWindow();
}