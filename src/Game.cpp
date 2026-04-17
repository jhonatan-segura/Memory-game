#include "Game.hpp"
#include <iostream>
#include <fstream>
#include <vector>

Game::Game()
{
  InitGame(false);
}

void Game::InitGame(bool restarting)
{
  if (!restarting) {
    tiles = CreateTiles();
  }
  progressBar = ProgressBar((Vector2){0, 0}, (Vector2){GetScreenWidth(), 10}, WHITE);
  gameTurn = CPU_TURN;
  running = true;
  turningOff = false;
  isDelayTurnSwitchActive = false;
  gameStarted = false;
  timePerRound = 10.0;
  remainingTimeProgressBar = timePerRound;
  timeAtTurnSwitch = 0;
  score = 0;
  correctPlayerTilesCount = 0;
  tileToLitIndex = 0;
  lastTime = GetTime();
  turnedOnDuration = .8;
  turnedOffDuration = .3;
  Rectangle popUpRect = (Rectangle){
      .x = GetScreenWidth() / 2 - 240,
      .y = GetScreenHeight() / 2 - 125,
      .width = 480,
      .height = 250};
  popUp = PopUp(popUpRect, "Has perdido", "Presiona Enter para comenzar de nuevo.", "Reiniciar");
  AddNewCPUMove();
}

void Game::Update()
{
  if (gameTurn == PLAYER_TURN && !isDelayTurnSwitchActive && running)
  {
    remainingTimeProgressBar -= GetFrameTime();
    double barPercentage = remainingTimeProgressBar / timePerRound;
    double result = 800.0 * barPercentage;
    progressBar.SetSize((Vector2){result, 10});
  }
}

void Game::Draw(Shader shader, int colorLoc, int strengthLoc)
{
  if (!gameStarted)
  {
    InitialDelay();
  }

  progressBar.Draw();
  for (auto &tile : tiles)
  {
    if (tile.IsLit() && gameTurn == PLAYER_TURN)
    {
      lastTime = tile.LitAfterClicking(lastTime);
      if (!tile.IsLit())
      {
        CheckUpdateTurn();
      }

      // Vector2 pos = (Vector2) {0,0};
      // Vector2 size = (Vector2) {50,50};

      // SetShaderValue(shader, colorLoc, &pos, SHADER_UNIFORM_VEC2);
      // SetShaderValue(shader, strengthLoc, &size, SHADER_UNIFORM_VEC2);
      // BeginShaderMode(shader);
      // tile.Draw();
      // EndShaderMode();

      // Image img = GenImageColor(1, 1, WHITE);
      // Texture2D tex = LoadTextureFromImage(img);
      // UnloadImage(img);
      // BeginShaderMode(shader);

      // DrawTexturePro(
      //     tex,
      //     (Rectangle){0, 0, 1, 1},                                                 // source
      //     (Rectangle){0, 0, 100, 100}, // destino
      //     (Vector2){0, 0},
      //     0.0f,
      //     WHITE);

      // EndShaderMode();
    }
    // else
    // {
    //   tile.Draw();
    // }
    tile.Draw();
  }
  DelayTurnSwitch(CPU_TURN);
  DisplayTilesInOrder();

  if (score > 0)
  {
    const char *textScore = TextFormat("%d", score);
    DrawText(textScore, GetScreenWidth() / 2 - TextLength(textScore) / 2, 20, 36, WHITE);
  }

  if (!running)
  {
    popUp.Draw();
  }
}

void Game::HandleInput()
{
  if (gameTurn == CPU_TURN)
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
          lastTime = GetTime();
        }
        else
        {
          correctPlayerTilesCount = 0;
          running = false;
        }
      }
    }
  }

  if (IsKeyReleased(KEY_ENTER) && !running) {
    cpuTiles.clear();
    InitGame(true);
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
}

void Game::InitialDelay()
{
  double now = GetTime();
  double duration = 1.0;
  if (now - lastTime >= duration)
  {
    lastTime = now;
    gameStarted = true;
  }
}

void Game::DisplayTilesInOrder()
{
  if (gameTurn == PLAYER_TURN || !gameStarted)
    return;

  double now = GetTime();
  double duration = turningOff ? turnedOnDuration : turnedOffDuration;
  if (now - lastTime >= duration)
  {
    lastTime = now;

    if (tileToLitIndex > 0 && turningOff)
    {
      tiles.at(cpuTiles.at(tileToLitIndex - 1)).TurnOffTile();
      if (tileToLitIndex == cpuTiles.size())
      {
        tileToLitIndex = 0;
        gameTurn = PLAYER_TURN;
        timeAtTurnSwitch = GetTime();
      }
    }
    if (tileToLitIndex < cpuTiles.size() && !turningOff)
    {
      tiles.at(cpuTiles.at(tileToLitIndex++)).TurnOnTile();
    }
    turningOff = !turningOff;
  }
}

void Game::CheckUpdateTurn()
{
  if (correctPlayerTilesCount == cpuTiles.size())
  {
    correctPlayerTilesCount = 0;
    lastTime = GetTime();
    DelayTurnSwitch(CPU_TURN);
    isDelayTurnSwitchActive = true;
    AddNewCPUMove();
  }
}

void Game::DelayTurnSwitch(GameTurn _gameState)
{
  if (!isDelayTurnSwitchActive)
    return;

  double now = GetTime();
  double duration = .8;
  if (now - lastTime >= duration)
  {
    lastTime = GetTime();
    gameTurn = _gameState;
    isDelayTurnSwitchActive = false;
    progressBar.SetSize((Vector2){GetScreenWidth(), 10});
    score++;
    timePerRound = timePerRound + timePerRound * .05;
    remainingTimeProgressBar = timePerRound;
    double speedIncrease;
    if (score < 5)
    {
      speedIncrease = .1;
    }
    else if (score < 10)
    {
      speedIncrease = .09;
    }
    else if (score >= 10)
    {
      speedIncrease = .06;
    }
    turnedOnDuration = turnedOnDuration - turnedOnDuration * speedIncrease;
    turnedOffDuration = turnedOffDuration - turnedOffDuration * speedIncrease;
  }
}