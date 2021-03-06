/**
Collin Sinclair
Homework 1: Pacman
*/

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

void createTreasure(const string &fileName, const string &newFileName) {
  vector<string> lines;
  readLines(fileName, lines);
  // for each line, for each character, if the character is a "2", replace it with a "3" 10% of the time
  for (auto &line : lines) {
    for (char &j : line) {
      if (j == '2') {
        uniform_int_distribution<int> dist(0, 9);
        if (dist(defEngine) < 1) {
          j = '3';
        }
      }
    }
  }
  ofstream file(newFileName);
  for (auto &line : lines) {
    file << line << endl;
  }
  file.close();
}

Board::Board(Player *p) {
  p_ = p;
  rows_ = BOARD_DIMENSION_X;
  cols_ = BOARD_DIMENSION_Y;
  vector<string> lines;
  string pathToMap = "map.txt";
  string pathToNewMap = "new_map.txt";
  createTreasure(pathToMap, pathToNewMap); // creates a new map with 10% chance of treasure in each square
  readLines(pathToNewMap, lines); // reads the new map
  Position pos{0, 0}; // sets the starting position of the player
  for (int i = 0; i < rows_; ++i) { // for each row
    for (int j = 0; j < cols_; ++j) { // for each column
      pos.col = j;
      pos.row = i;
      int curr = lines[i][j] - '0'; // this run little hack subtracts the ascii value of 0 from that of the char
      SquareType currSquareType = NumToSquareType(curr); // converts the number to a SquareType
      SetSquareValue(pos, currSquareType); // sets the square value
    }
  }
}
SquareType Board::NumToSquareType(int i) {
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
      cout << SquareTypeStringify(b.arr_[i][j], b.p_);
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
    if ((get_square_value(up) != SquareType::Wall)) // if the new position is not a wall or the current position
    {
      moves.push_back(up);
    }
  }
  Position down{pos.row + 1, pos.col}; // this is the possible new position
  if (down.row >= 0 && down.row < rows_ && down.col >= 0 && down.col < cols_) // if the new position is on the board
  {
    if ((get_square_value(down) != SquareType::Wall)) // if the new position is not a wall or the current position
    {
      moves.push_back(down);
    }
  }
  Position left{pos.row, pos.col - 1}; // this is the possible new position
  if (left.row >= 0 && left.row < rows_ && left.col >= 0 && left.col < cols_) // if the new position is on the board
  {
    if ((get_square_value(left) != SquareType::Wall)) // if the new position is not a wall or the current position
    {
      moves.push_back(left);
    }
  }
  Position right{pos.row, pos.col + 1}; // this is the possible new position
  if (right.row >= 0 && right.row < rows_ && right.col >= 0
      && right.col < cols_) // if the new position is on the board
  {
    if ((get_square_value(right) != SquareType::Wall)) // if the new position is not a wall or the current position
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
          if (p->CanEatGhosts()) { // if the player can eat ghosts
            enemy->SetPosition(Position{14, 13});
            if (get_square_value(enemy->get_position()) == SquareType::EnemyPoint) {
              SetSquareValue(enemy->get_position(), SquareType::Dots); // set the old position to dots
            } else if (get_square_value(enemy->get_position()) == SquareType::EnemyNoPoint) {
              SetSquareValue(enemy->get_position(), SquareType::Empty); // set the old position to empty
            }
            p->SetHasTreasure(-1);
          } else {
            p->SetIsDead(true);
            return true;
          }
        }
      }
      if (get_square_value(new_pos) == SquareType::Dots) { // if the new position is a dot
        p->ChangePoints(1); // add a point
      } else if (get_square_value(new_pos) == SquareType::Treasure) {
        p->SetHasTreasure(1);
        p->ChangePoints(100);
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
  std::vector<Position> moves = GetMoves(enemy); // get the possible moves
  int possible_moves = moves.size(); // get the number of possible moves
  uniform_int_distribution<int> intDistro(0, possible_moves - 1); // create a uniform distribution
  int random_move = intDistro(defEngine); // get a random move
  if (random_move >= possible_moves) {  // if the random move is greater than the number of possible moves
    cout << "RANDOM MOVE OUT OF RANGE" << endl;
    exit(-1);
  }
  Position new_pos = moves[random_move]; // get the new position
  if (get_square_value(enemy->get_position()) == SquareType::EnemyPoint) { // if the enemy is at a dot
    SetSquareValue(enemy->get_position(), SquareType::Dots); // set the old position to dots
  } else if (get_square_value(enemy->get_position()) == SquareType::EnemyNoPoint) { // if the enemy is not at a dot
    SetSquareValue(enemy->get_position(), SquareType::Empty); // set the old position to empty
  }
  if (get_square_value(new_pos) == SquareType::Dots) { // if the new position is a dot
    SetSquareValue(new_pos, SquareType::EnemyPoint); // set the new position to an enemy dot
    enemy->SetPosition(new_pos); // set the enemy's position to the new position
    return true;
  } else if (get_square_value(new_pos) == SquareType::Empty) { // if the new position is empty
    SetSquareValue(new_pos, SquareType::EnemyNoPoint); // set the new position to an enemy no point
    enemy->SetPosition(new_pos); // set the enemy's position to the new position
    return true;
  } else if (get_square_value(new_pos) == SquareType::Pacman) { // if the new position is Pacman
    if (pacman->CanEatGhosts()) { // if the pacman can eat ghosts
      enemy->SetPosition(Position{14, 13}); // return the ghost to the ghost chamber
      if (get_square_value(enemy->get_position()) == SquareType::EnemyPoint) { // if the enemy is at a dot
        SetSquareValue(enemy->get_position(), SquareType::Dots); // set the old position to dots
      } else if (get_square_value(enemy->get_position()) == SquareType::EnemyNoPoint) {
        SetSquareValue(enemy->get_position(), SquareType::Empty); // set the old position to empty
      }
      pacman->SetHasTreasure(-1); // decremenet the number of treasures
    } else {
      pacman->SetIsDead(true); // if pacman can't eat ghosts, he is dead :(
      SetSquareValue(new_pos, SquareType::EnemyNoPoint); // set the new position to an enemy no point
      enemy->SetPosition(new_pos); // set the enemy's position to the new position
      return true;
    }
  }
  return false;
}
std::string SquareTypeStringify(SquareType sq, Player *p) {
  switch (sq) {
    case SquareType::Wall:return "???";
    case SquareType::Empty:return " ";
    case SquareType::Dots:return ".";
    case SquareType::Pacman:
      if (p->CanEatGhosts()) return "???";
      else return "<";
    case SquareType::Treasure:return "$";
    case SquareType::EnemyNoPoint:return "@";
    case SquareType::EnemyPoint:return "@";
    default: return " ";
  }
}
Game::Game(Board *b) {
  board_ = b;
  turn_count_ = 0;
  dots_remaining_ = CountDots();
}
void Game::TakeTurn(Player *p, const std::vector<Player *> &enemyList) {
  vector<Position> possibleMoves; // vector of possible moves
  string temp;
  char d;
  cout << p->Stringify() << endl;
  possibleMoves = board_->GetMoves(p); // get the possible moves
  for (auto &move : possibleMoves) {
    cout << p->ToRelativePosition(move) << " "; // print the relative position of the possible moves
  }
  temp = "";
  getline(cin, temp);
  d = temp[0];
  Position dPos = p->CharToPos(d); // convert the char to a position
  board_->MovePlayer(p, dPos, enemyList); // move the player
  turn_count_++;
}
void Game::TakeTurnEnemy(Player *enemy, Player *pacman) {
  board_->MoveEnemy(enemy, pacman);
}
std::string Game::GenerateReport(Player *p) const {
  std::string report;
  report += "GAME REPORT FOR " + p->get_name() + "\n";
  report += "FINAL SCORE: " + std::to_string(p->get_points()) + "\n";
  report += "NUMBER OF TURNS: " + std::to_string(turn_count_) + " (" + to_string(p->get_points() / turn_count_)
      + " POINTS / TURN)";
  return report;
}
int Game::CountDots() {
// counts all the Squares that are dots
  int dots = 0;
  for (int i = 0; i < Board::get_cols(); i++) {
    for (int j = 0; j < Board::get_rows(); j++) {
      if (board_->get_square_value({i, j}) == SquareType::Dots) {
        dots++;
      }
    }
  }
  dots_remaining_ = dots;
  return dots;
}
