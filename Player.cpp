/**
Collin Sinclair
Homework 1: Pacman
*/

#include "Player.h"
#include <utility>
void Player::ChangePoints(const int x) {
  points_ += x;
}
void Player::SetPosition(Position pos) {
  pos_ = pos;
}
void Player::SetHasTreasure(const int x) {
  treasure_ += x;
}
void Player::SetIsDead(bool isDead) {
  isDead_ = isDead;
}
std::string Player::Stringify() {
  std::string pointString = std::to_string(points_);
  std::string playerString = name_ + ": " + pointString;
  return playerString;
}
Player::Player(std::string name) {
  name_ = std::move(name);
  pos_.col = 1;
  pos_.row = 1;
  points_ = 0;
  treasure_ = 0;
  isDead_ = false;
}
std::string Player::ToRelativePosition(Position other) const {
  Position relPos = Position{pos_.row - other.row, pos_.col - other.col}; // calculate the relative position
  // return the string representation of the relative position
  if (relPos.row == 0 and relPos.col == 1) { return "←"; }
  if (relPos.row == 0 and relPos.col == -1) { return "→"; }
  if (relPos.row == 1 and relPos.col == 0) { return "↑"; }
  if (relPos.row == -1 and relPos.col == 0) { return "↓"; }
  return "Somehow it's illegal bro";
}
Position Player::CharToPos(char d) const {
  Position curr = get_position();
  // calculate each possible position
  Position up{curr.row - 1, curr.col};
  Position down{curr.row + 1, curr.col};
  Position left{curr.row, curr.col - 1};
  Position right{curr.row, curr.col + 1};
  // return the position that matches the input
  switch (d) {
    case 'w':return up;
    case 's':return down;
    case 'a':return left;
    case 'd':return right;
    default:return curr;
  }
}
