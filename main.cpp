/**
Collin Sinclair
Homework 1: Pacman
*/

#include "Game.h"
#include "Player.h"
#include <iostream>
using namespace std;
int main() {
  cout << "Welcome to Pacman!" << endl;
  cout << "Move with WASD. Legal moves will be displayed each turn." << endl;
  cout << "You start in the upper left corner and must collect all the dots to win." << endl;
  cout << "Ghosts are represented by @. If you get a treasure ($), you can eat ghosts." << endl;
  cout << "Enter your name: ";
  string name;
  getline(cin, name);
  Player p = Player{name};
  Board b(&p);
  Game g(&b);
  b.SetSquareValue(p.get_position(), SquareType::Pacman);
  cout << "Enter number of enemies: ";
  string numEnemies;
  getline(cin, numEnemies);
  vector<Player *> enemies;
  for (int i = 0; i < stoi(numEnemies); ++i) {
    g.CountDots();
    auto *e = new Player{to_string(i)};
    Position pos = Position{14, 13};
    e->SetPosition(pos);
    enemies.push_back(e);
  }
  bool allEnemiesDead;
  // MAIN GAME LOOP ==============================================
  while (not g.IsGameOver(&p)) {
    for (int i = 0; i < 100; ++i) {
      cout << endl;
    }
    cout << b << endl;
    cout << "Number of Treasures: " << p.NumTreasure() << endl;
    cout << "Dots Reaming: " << g.CountDots() << endl;
    g.TakeTurn(&p, enemies);
    allEnemiesDead = true;
    for (auto e : enemies) {
      if (not e->IsDead()) {
        allEnemiesDead = false;
        break;
      }
    }
    for (auto e : enemies) {
      if (not e->IsDead()) {
        g.TakeTurnEnemy(e, &p);
      }
    }
    allEnemiesDead = true;
    for (auto e : enemies) {
      if (not e->IsDead()) {
        allEnemiesDead = false;
        break;
      }
    }
  }
  // =============================================================
  for (int i = 0; i < 100; ++i) {
    cout << endl;
  }
  cout << b << endl;
  cout << "GAME OVER" << endl;
  if ((g.CheckIfDotsOver() and not p.IsDead()) or (allEnemiesDead)) {
    cout << "YOU WIN!" << endl;
  } else if (not g.CheckIfDotsOver() and p.IsDead()) {
    cout << "YOU LOSE!" << endl;
  } else {
    cout << "Something else happened... not sure what" << endl;
  }
  cout << g.GenerateReport(&p) << endl;
  return 0;
}