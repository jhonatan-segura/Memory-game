#include <iostream>
#include <raylib.h>
#include "Game.hpp"

int main()
{
  Color grey = {29, 29, 27, 255};
  InitWindow(800, 850, "Memory Game");

  Shader glowShader = LoadShader(0, "/home/jsegurapinto/Proyectos_C/memory_game/shaders/glow2.fs");

  int glowColorLoc = GetShaderLocation(glowShader, "glowColor");
  int glowStrengthLoc = GetShaderLocation(glowShader, "glowStrength");
  SetTargetFPS(60);

  Game game;

  while (!WindowShouldClose())
  {
    game.HandleInput();
    game.Update();

    BeginDrawing();
    ClearBackground(grey);
    game.Draw(glowShader, glowColorLoc, glowStrengthLoc);
    EndDrawing();
  }

  CloseWindow();
}