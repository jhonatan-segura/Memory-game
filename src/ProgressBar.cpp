#include "ProgressBar.hpp"
#include <iostream>

ProgressBar::ProgressBar()
{
  this->position = (Vector2) {0,0};
  this->size = (Vector2) {0,0};
  this->color = WHITE;
}

ProgressBar::ProgressBar(Vector2 position, Vector2 size, Color color)
{
  this->position = position;
  this->size = size;
  this->color = color;
}

void ProgressBar::Draw()
{
  DrawRectangleV(position, size, color);
}

void ProgressBar::SetSize(Vector2 size) {
  this->size = size;
}