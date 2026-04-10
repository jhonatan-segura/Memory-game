#pragma once
#include <raylib.h>

class ProgressBar
{
private:
  Vector2 position;
  Color color;
  Vector2 size;

public:
  ProgressBar();
  ProgressBar(Vector2 position, Vector2 size, Color color);
  void SetSize(Vector2 size);
  void Draw();
};