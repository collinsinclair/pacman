#include "Game.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

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

  //
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
    case 3: return SquareType::PowerfulPacman;
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

std::string SquareTypeStringify(SquareType sq) {
  switch (sq) {
    case SquareType::Wall:return "█";
    case SquareType::Empty:return "█";
    case SquareType::Dots:return ".";
    case SquareType::PowerfulPacman:return "$";
    default: return " ";
  }
}
