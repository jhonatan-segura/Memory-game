#pragma once

#include "Tile.hpp"
#include "ProgressBar.hpp"
#include <vector>
#include <queue>

enum GameState
{
  PLAYER_TURN,
  CPU_TURN
};

class Game
{
public:
  Game();
  void Draw();
  void Update();
  void HandleInput();

private:
  std::vector<Tile> CreateTiles();
  void CheckUpdateTurn();
  void InitGame();
  void AddNewCPUMove();
  void DelayTurnSwitch(GameState gameState);
  void DisplayTilesInOrder();
  std::vector<Tile> tiles;
  ProgressBar progressBar;
  GameState gameState;
  bool turningOff;
  bool isDelayTurnSwitchActive;
  int correctPlayerTilesCount;
  int tileToLitIndex;
  double lastTimeDisplayAllTiles;
  double remainingTimeProgressBar;
  double timeAtTurnSwitch;
  // double lastTimeDisplayTile;
  std::vector<int> cpuTiles;
  std::vector<int> playerTiles;
};