#pragma once
#include <raylib.h>
#include <string>

class PopUp
{
public:
  PopUp();
  PopUp(Rectangle rect, std::string title, std::string body, std::string buttonText) : rect(rect), title(title), body(body), buttonText(buttonText) {};
  void Draw();

private:
  Rectangle rect;
  std::string title, body, buttonText;
};