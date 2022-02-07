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
