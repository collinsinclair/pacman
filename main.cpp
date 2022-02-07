#include "Game.h"
#include "Player.h"
#include <iostream>
using namespace std;

int main() {
  Board board;
  Player p = Player("Collin", true);
  board.SetSquareValue(p.get_position(), SquareType::Pacman);

  cout << board << endl;
  cout << p.Stringify() << endl;

  vector<Position> poss = board.GetMoves(&p);
  for (auto &pos : poss) {
//    cout << pos.col << " " << pos.row << endl;
    cout << p.ToRelativePosition(pos) << " ";
  }
  cout << endl;
  Position newpos = Position{2, 1};
  vector<Player *> enems;
  board.MovePlayer(&p, newpos, enems);
  int x;
  cin >> x;
  cout << board;
  cout << p.Stringify() << endl;

  poss = board.GetMoves(&p);

  for (auto &pos : poss) {
//    cout << pos.col << " " << pos.row << endl;
    cout << p.ToRelativePosition(pos) << " ";
  }
  cout << endl;
  return 0;
}