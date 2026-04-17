#include "PopUp.hpp"

PopUp::PopUp()
{
}

void PopUp::Draw()
{
  DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), (Color) {0,0,0,100});
  DrawRectangleRec(rect, (Color) {236, 237, 218, 255});
  DrawText(title.c_str(), GetScreenWidth() / 2 - MeasureText(title.c_str(), 28) / 2, rect.y + 20, 28, BLACK);
  DrawText(body.c_str(), GetScreenWidth() / 2 - MeasureText(body.c_str(), 24) / 2, rect.y + 100, 24, BLACK);
  DrawText(buttonText.c_str(), GetScreenWidth() / 2 - MeasureText(buttonText.c_str(), 24) / 2, rect.y + 150, 24, BLACK);
}
