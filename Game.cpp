#include "Game.h"
#include "Player.h"
#include <iostream>
#include <string>
#include <fstream>
#include <random>
using namespace std;

default_random_engine defEngine;

void readLines(const string &fileName, vector<string> &lines) {
  ifstream file(fileName);
  string line;
  while (getline(file, line)) {
    lines.push_back(line);
  }
  file.close();
}
Board::Board() {
  rows_ = BOARD_DIMENSION_X;
  cols_ = BOARD_DIMENSION_Y;
  // Read the map text file into a vector of lines
  vector<string> lines;
  string pathToMap = "map.txt";
  readLines(pathToMap, lines);
  Position pos{0, 0};
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      pos.col = j;
      pos.row = i;
      int curr = lines[i][j] - '0'; // this run little hack subtracts the ascii value of 0 from that of the char
      SquareType currSquareType = numToSquareType(curr);
      SetSquareValue(pos, currSquareType);
    }
  }
}
SquareType Board::numToSquareType(int i) {
  switch (i) {
    case 0: return SquareType::Empty;
    case 1: return SquareType::Wall;
    case 2: return SquareType::Dots;
    case 3: return SquareType::Treasure;
    default: return SquareType::Empty;
  }
}
void Board::SetSquareValue(Position pos, SquareType value) {
  arr_[pos.row][pos.col] = value;
}
std::ostream &operator<<(ostream &os, const Board &b) {
  for (int i = 0; i < b.rows_; ++i) {
    for (int j = 0; j < b.cols_; ++j) {
      cout << SquareTypeStringify(b.arr_[i][j]);
    }
    cout << endl;
  }
  return os;
}
SquareType Board::get_square_value(Position pos) const {
  return arr_[pos.row][pos.col];
}
std::vector<Position> Board::GetMoves(Player *p) const {
  std::vector<Position> moves;
  Position pos = p->get_position();
  Position up{pos.row - 1, pos.col}; // this is the possible new position
  if (up.row >= 0 && up.row < rows_ && up.col >= 0 && up.col < cols_) // if the new position is on the board
  {
    if ((get_square_value(up) != SquareType::Wall)
        and (get_square_value(up) != SquareType::Pacman)) // if the new position is not a wall or the current position
    {
      moves.push_back(up);
    }
  }
  Position down{pos.row + 1, pos.col}; // this is the possible new position
  if (down.row >= 0 && down.row < rows_ && down.col >= 0 && down.col < cols_) // if the new position is on the board
  {
    if ((get_square_value(down) != SquareType::Wall)
        and (get_square_value(down) != SquareType::Pacman)) // if the new position is not a wall or the current position
    {
      moves.push_back(down);
    }
  }
  Position left{pos.row, pos.col - 1}; // this is the possible new position
  if (left.row >= 0 && left.row < rows_ && left.col >= 0 && left.col < cols_) // if the new position is on the board
  {
    if ((get_square_value(left) != SquareType::Wall)
        and (get_square_value(left) != SquareType::Pacman)) // if the new position is not a wall or the current position
    {
      moves.push_back(left);
    }
  }
  Position right{pos.row, pos.col + 1}; // this is the possible new position
  if (right.row >= 0 && right.row < rows_ && right.col >= 0 && right.col < cols_) // if the new position is on the board
  {
    if ((get_square_value(right) != SquareType::Wall) and (get_square_value(right)
        != SquareType::Pacman)) // if the new position is not a wall or the current position
    {
      moves.push_back(right);
    }
  }
  return moves;
}
bool Board::MovePlayer(Player *p, Position new_pos, const std::vector<Player *> &enemyList) {
  std::vector<Position> moves = GetMoves(p); // get the possible moves
  for (auto &move : moves) // for each possible move
  {
    if (move == new_pos) { // if the move is the same as the new position
      for (auto &enemy : enemyList) { // for each enemy
        if (enemy->get_position() == new_pos) { // if the enemy is at the new position
          if (p->canEatGhosts()) { // if the player can eat ghosts
            enemy->setIsDead(true);
            p->setHasTreasure(-1);
          } else {
            p->setIsDead(true);
            return true;
          }
        }
      }
      if (get_square_value(new_pos) == SquareType::Dots) { // if the old position was a dot
        p->ChangePoints(1); // add a point
      } else if (get_square_value(new_pos) == SquareType::Treasure) {
        p->setHasTreasure(1);
      }
      SetSquareValue(p->get_position(), SquareType::Empty); // set the old position to empty
      SetSquareValue(new_pos, SquareType::Pacman); // set the new position to Pacman
      p->SetPosition(new_pos); // set the player's position to the new position
      return true;
    }
  }
  return false;
}
bool Board::MoveEnemy(Player *enemy, Player *pacman) {
  std::vector<Position> moves = GetMoves(enemy);
  int possible_moves = moves.size();
  uniform_int_distribution<int> intDistro(0, possible_moves - 1);
  int random_move = intDistro(defEngine);
  if (random_move >= possible_moves) {
    cout << "RANDOM MOVE OUT OF RANGE" << endl;
    exit(-1);
  }
  Position new_pos = moves[random_move];
  if (get_square_value(enemy->get_position()) == SquareType::EnemyPoint) {
    SetSquareValue(enemy->get_position(), SquareType::Dots); // set the old position to dots
  } else if (get_square_value(enemy->get_position()) == SquareType::EnemyNoPoint) {
    SetSquareValue(enemy->get_position(), SquareType::Empty); // set the old position to empty
  }
  if (get_square_value(new_pos) == SquareType::Dots) {
    SetSquareValue(new_pos, SquareType::EnemyPoint);
    enemy->SetPosition(new_pos);
    return true;
  } else if (get_square_value(new_pos) == SquareType::Empty) {
    SetSquareValue(new_pos, SquareType::EnemyNoPoint);
    enemy->SetPosition(new_pos);
    return true;
  } else if (get_square_value(new_pos) == SquareType::Pacman) {
    pacman->setIsDead(true);
    SetSquareValue(new_pos, SquareType::EnemyNoPoint);
    enemy->SetPosition(new_pos);
    return true;
  } else if (get_square_value(new_pos) == SquareType::PowerfulPacman) {
    enemy->setIsDead(true);
    pacman->setHasTreasure(-1);
    return true;
  }
  return false;
}
std::string SquareTypeStringify(SquareType sq) {
  switch (sq) {
    case SquareType::Wall:return "█";
    case SquareType::Empty:return " ";
    case SquareType::Dots:return ".";
    case SquareType::Pacman:return "<";
    case SquareType::PowerfulPacman:return "≤";
    case SquareType::Treasure:return "$";
    case SquareType::EnemyNoPoint:return "@";
    case SquareType::EnemyPoint:return "@";
    default: return " ";
  }
}
Game::Game(Board *b) {
  board_ = b;
  turn_count_ = 0;
  dots_count_ = 239;
  GameOver = false;
}
void Game::TakeTurn(Player *p, const std::vector<Player *> &enemyList) {
  vector<Position> possibleMoves;
  string temp;
  char d;
  cout << p->Stringify() << endl;
  possibleMoves = board_->GetMoves(p);
  for (auto &move : possibleMoves) {
    cout << p->ToRelativePosition(move) << " ";
  }
  temp = "";
  getline(cin, temp);
  d = temp[0];
  Position dPos = p->CharToPos(d);
  board_->MovePlayer(p, dPos, enemyList);
  turn_count_++;
}
void Game::TakeTurnEnemy(Player *enemy, Player *pacman) {
  board_->MoveEnemy(enemy, pacman);
}
