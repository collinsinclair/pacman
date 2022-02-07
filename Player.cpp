#include "Player.h"

#include <utility>

void Player::ChangePoints(const int x) {
  points_ += x;
}
void Player::SetPosition(Position pos) {
  pos_ = pos;
}
void Player::setHasTreasure(const int x) {
  has_Treasure_ += x;
}
void Player::setIsDead(bool isdead) {
  isDead_ = isdead;
}
std::string Player::Stringify() {
  std::string pointString = std::to_string(points_);
  std::string playerString = name_ + ": " + pointString;
  return playerString;
}
Player::Player(std::string name, bool is_human) {
  name_ = std::move(name);
  is_human_ = is_human;
  pos_.col = 1;
  pos_.row = 1;
  points_ = 0;
  has_Treasure_ = 0;
  isDead_ = false;
}
std::string Player::ToRelativePosition(Position other) const {
  Position relPos = Position{pos_.row - other.row, pos_.col - other.col};
  if (relPos.row == 0 and relPos.col == 1) { return "←"; }
  if (relPos.row == 0 and relPos.col == -1) { return "→"; }
  if (relPos.row == 1 and relPos.col == 0) { return "↑"; }
  if (relPos.row == -1 and relPos.col == 0) { return "↓"; }
  return "Somehow it's illegal bro";
}
