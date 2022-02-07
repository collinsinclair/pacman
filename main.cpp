#include "Game.h"
#include "Player.h"
#include <iostream>
using namespace std;

int main() {
  Board b;
  Player p{"Collin", true};
  b.SetSquareValue(p.get_position(), SquareType::Pacman);
  vector<Position> possibleMoves;
  vector<Player *> enems;
  char d;
  while (true) {

    cout << b << endl;
    cout << p.Stringify() << endl;

    possibleMoves = b.GetMoves(&p);
    for (auto &move : possibleMoves) {
      cout << p.ToRelativePosition(move) << " ";
    }

    cin >> d;
    Position dPos = p.CharToPos(d);
    b.MovePlayer(&p, dPos, enems);
//    break;
  }
  return 0;
}