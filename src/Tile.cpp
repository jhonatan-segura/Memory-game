#include "Tile.hpp"
#include <iostream>

Tile::Tile(Vector2 position, Vector2 size, Color color)
{
  this->position = position;
  this->size = size;
  this->color = color;
  isLit = false;
}

void Tile::Draw()
{
  DrawRectangleV(position, size, color);
}

double Tile::LitAfterClicking(double lastTime)
{
  double now = GetTime();
  double duration = .3;
  color.a = 255;
  if (now - lastTime >= duration)
  {
    lastTime = now;

    color.a = 100;
    // std::cout << "Temporal";
    isLit = false;
  }
  return lastTime;
}

void Tile::TurnOnTile()
{
  color.a = 255;
}

void Tile::TurnOffTile()
{
  color.a = 100;
}

bool Tile::IsBeingClicked(Vector2 mousePosition)
{
  if (position.x < mousePosition.x && position.y < mousePosition.y &&
      position.x + size.x > mousePosition.x && position.y + size.y > mousePosition.y)
  {
    return true;
  }
  return false;
}

bool Tile::IsLit()
{
  return isLit;
}

void Tile::SetIsLit(bool value)
{
  isLit = value;
}
