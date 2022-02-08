#include "Game.h"
#include "Player.h"
#include <iostream>
using namespace std;
int main() {
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
    g.countDots();
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
    cout << "Number of Treasures: " << p.numTreasure() << endl;
    cout << "Dots Reaming: " << g.countDots() << endl;
    g.TakeTurn(&p, enemies);
    allEnemiesDead = true;
    for (auto e : enemies) {
      if (not e->isDead()) {
        allEnemiesDead = false;
        break;
      }
    }
    for (auto e : enemies) {
      if (not e->isDead()) {
        g.TakeTurnEnemy(e, &p);
      }
    }
    allEnemiesDead = true;
    for (auto e : enemies) {
      if (not e->isDead()) {
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
  if ((g.CheckIfDotsOver() and not p.isDead()) or (allEnemiesDead)) {
    cout << "YOU WIN!" << endl;
  } else if (not g.CheckIfDotsOver() and p.isDead()) {
    cout << "YOU LOSE!" << endl;
  } else {
    cout << "Something else happened... not sure what" << endl;
  }
  cout << g.GenerateReport(&p) << endl;
  return 0;
}