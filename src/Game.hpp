#pragma once

#include "Tile.hpp"
#include "ProgressBar.hpp"
#include "PopUp.hpp"
#include <vector>
#include <queue>

enum GameTurn
{
  PLAYER_TURN,
  CPU_TURN
};

class Game
{
public:
  Game();
  void Draw(Shader shader, int colorLoc, int strengthLoc);
  void Update();
  void HandleInput();

private:
  std::vector<Tile> CreateTiles();
  void CheckUpdateTurn();
  void InitGame(bool restarting);
  void AddNewCPUMove();
  void DelayTurnSwitch(GameTurn gameTurn);
  void InitialDelay();
  void DisplayTilesInOrder();
  double timePerRound;
  std::vector<Tile> tiles;
  ProgressBar progressBar;
  GameTurn gameTurn;
  PopUp popUp;
  bool turningOff;
  bool running;
  bool gameStarted;
  bool isDelayTurnSwitchActive;
  int correctPlayerTilesCount;
  int score;
  int tileToLitIndex;
  double lastTime;
  double remainingTimeProgressBar;
  double timeAtTurnSwitch;
  double turnedOnDuration;
  double turnedOffDuration;
  std::vector<int> cpuTiles;
};