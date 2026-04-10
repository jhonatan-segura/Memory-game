#pragma once
#include <raylib.h>

class Tile
{
private:
  Vector2 position;
  Color color;
  Vector2 size;
  bool isLit;

public:
  Tile(Vector2 position, Vector2 size, Color color);
  void Draw();
  bool IsLit();
  void SetIsLit(bool value);
  double LitAfterClicking(double lastTime);
  void TurnOnTile();
  void TurnOffTile();
  bool IsBeingClicked(Vector2 mousePosition);
};