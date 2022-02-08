#include "Game.h"
#include "Player.h"
#include <iostream>
using namespace std;
int main() {
//  Board b;
//  Player p{"Gabby", true};
//  b.SetSquareValue(p.get_position(), SquareType::Pacman);
//  vector<Position> possibleMoves;
//  vector<Player *> enems;
//  string temp;
//  char d;
//  while (true) {
//    for (int i = 0; i < 100; ++i) {
//      cout << endl;
//    }
//    cout << b << endl;
//    cout << p.Stringify() << endl;
//
//    possibleMoves = b.GetMoves(&p);
//    for (auto &move : possibleMoves) {
//      cout << p.ToRelativePosition(move) << " ";
//    }
//    temp = "";
//    getline(cin, temp);
//    d = temp[0];
//    Position dPos = p.CharToPos(d);
//    b.MovePlayer(&p, dPos, enems);
//    break;
//  }

  Board b;
  Game g(&b);
  cout << "Enter your name: ";
  string name;
  getline(cin, name);
  Player p = Player{name, true};
  b.SetSquareValue(p.get_position(), SquareType::Pacman);
  cout << "Enter number of enemies: ";
  string numEnemies;
  getline(cin, numEnemies);
  vector<Player *> enemies;
  for (int i = 0; i < stoi(numEnemies); ++i) {
    auto *e = new Player{to_string(i), false};
    Position pos = Position{14, 13};
    e->SetPosition(pos);
    enemies.push_back(e);
  }
  while (not g.IsGameOver(&p)) {
    for (int i = 0; i < 100; ++i) {
      cout << endl;
    }
    cout << b << endl;
    g.TakeTurn(&p, enemies);
    for (auto e : enemies) {
      g.TakeTurnEnemy(e, &p);
    }
  }

  return 0;
}