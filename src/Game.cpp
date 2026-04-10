#include "Game.hpp"
#include <iostream>
#include <fstream>
#include <vector>

Game::Game()
{
  InitGame();
}

void Game::InitGame()
{
  tiles = CreateTiles();
  progressBar = ProgressBar((Vector2){0, 0}, (Vector2){GetScreenWidth(), 20}, WHITE);
  gameState = CPU_TURN;
  turningOff = false;
  isDelayTurnSwitchActive = false;
  remainingTimeProgressBar = 10.0;
  timeAtTurnSwitch = 0;
  correctPlayerTilesCount = 0;
  tileToLitIndex = 0;
  lastTimeDisplayAllTiles = GetTime();
  // lastTimeDisplayTile = GetTime();
  for (int i = 0; i < 3; i++)
  {
    AddNewCPUMove();
  }
  // AddNewCPUMove();

  // cpuTiles.push_back(0);
  // cpuTiles.push_back(0);
  // cpuTiles.push_back(0);
}

void Game::Update()
{
  if (gameState == PLAYER_TURN)
  {
    double now = GetTime();
    double duration = GetFrameTime();
    if (now - timeAtTurnSwitch >= duration)
    {
      timeAtTurnSwitch = GetTime();
      remainingTimeProgressBar = remainingTimeProgressBar - duration;
      double barPercentage = remainingTimeProgressBar * 100.0 / 10.0;
      double result = 800.0 * (barPercentage / 100.0);
      progressBar.SetSize((Vector2){result, 20});
    }
  }
}

void Game::Draw()
{
  progressBar.Draw();
  for (auto &tile : tiles)
  {
    if (tile.IsLit() && gameState == PLAYER_TURN)
    {
      // std::cout << "celda iluminada" << std::endl;
      lastTimeDisplayAllTiles = tile.LitAfterClicking(lastTimeDisplayAllTiles);
      if (!tile.IsLit())
      {
        CheckUpdateTurn();
      }
    }
    tile.Draw();
  }
  if (isDelayTurnSwitchActive)
  {
    DelayTurnSwitch(CPU_TURN);
  }
  DisplayTilesInOrder();
}

void Game::HandleInput()
{
  if (gameState == CPU_TURN)
    return;

  if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
  {
    for (size_t i = 0; i < tiles.size(); i++)
    {
      Tile &tile = tiles.at(i);
      if (tile.IsBeingClicked(GetMousePosition()))
      {
        if (cpuTiles.at(correctPlayerTilesCount++) == i)
        {
          tile.SetIsLit(true);
          playerTiles.push_back(i);
          lastTimeDisplayAllTiles = GetTime();
        }
        else
        {
          std::cout << "no es el valor correcto" << std::endl;
          correctPlayerTilesCount = 0;
        }
      }
    }
  }
}

std::vector<Tile> Game::CreateTiles()
{
  float gap = 20;
  float upperGap = 50;
  float innerGap = 10;
  // (tilesCount - 1) * innerGap
  int tileSize = (GetScreenWidth() - 2 * gap - 2 * innerGap) / 3;
  Color red = {255, 0, 0, 100};
  Color green = {0, 255, 0, 100};
  Color blue = {0, 0, 255, 100};
  Color yellow = {255, 255, 0, 100};
  Color cyan = {0, 255, 255, 100};
  Color magenta = {255, 0, 255, 100};
  Color orange = {255, 165, 0, 100};
  Color purple = {128, 0, 128, 100};
  Color lightBlue = {217, 9, 109, 100};
  std::vector<Color> colors = {
      red, green, blue, yellow, cyan, magenta, orange, purple, lightBlue};

  for (int i = 0; i < 3; i++)
  {
    for (int j = 0; j < 3; j++)
    {
      float offsetX = gap + i * tileSize + i * innerGap;
      float offsetY = upperGap + gap + j * tileSize + j * innerGap;
      tiles.push_back(Tile({offsetX, offsetY}, (Vector2){(float)tileSize, (float)tileSize}, colors.at(j * 3 + i)));
    }
  }

  return tiles;
}

void Game::AddNewCPUMove()
{
  int tilesIndex = GetRandomValue(0, 8);
  cpuTiles.push_back(tilesIndex);
  std::cout << tilesIndex << std::endl;
}

void Game::DisplayTilesInOrder()
{
  if (gameState == PLAYER_TURN)
    return;

  double now = GetTime();
  double duration = turningOff ? .8 : .3;
  if (now - lastTimeDisplayAllTiles >= duration)
  {
    lastTimeDisplayAllTiles = now;

    if (tileToLitIndex > 0 && turningOff)
    {
      tiles.at(cpuTiles.at(tileToLitIndex - 1)).TurnOffTile();
      if (tileToLitIndex == cpuTiles.size())
      {
        tileToLitIndex = 0;
        gameState = PLAYER_TURN;
        timeAtTurnSwitch = GetTime();
      }
    }
    if (tileToLitIndex < cpuTiles.size() && !turningOff)
    {
      tiles.at(cpuTiles.at(tileToLitIndex++)).TurnOnTile();
    }
    turningOff = !turningOff;
    std::cout << ".";
  }
}

void Game::CheckUpdateTurn()
{
  if (correctPlayerTilesCount == cpuTiles.size())
  {
    correctPlayerTilesCount = 0;
    lastTimeDisplayAllTiles = GetTime();
    DelayTurnSwitch(CPU_TURN);
    isDelayTurnSwitchActive = true;
    AddNewCPUMove();
  }
}

void Game::DelayTurnSwitch(GameState _gameState)
{
  double now = GetTime();
  double duration = 2.0;
  if (now - lastTimeDisplayAllTiles >= duration)
  {
    lastTimeDisplayAllTiles = GetTime();
    gameState = _gameState;
    isDelayTurnSwitchActive = false;
    remainingTimeProgressBar = 10.0;
    std::cout << "cambio de turno a CPU" << std::endl;
  }
}