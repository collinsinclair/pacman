#ifndef _PLAYER_H_
#define _PLAYER_H_
#include<string>
struct Position {
  int row;
  int col;
  bool operator==(const Position &other) const {
    return row == other.row && col == other.col;
  }
};
class Player {
 public:
  Player(std::string name);
  Position CharToPos(char d) const;
  Position get_position() const { return pos_; }
  bool canEatGhosts() const { return treasure_ > 0; }
  int numTreasure() const { return treasure_; }
  bool isDead() const { return isDead_; }
  int get_points() const { return points_; }
  std::string Stringify();
  std::string ToRelativePosition(Position other) const;
  std::string get_name() const { return name_; }
  void ChangePoints(int x);
  void SetPosition(Position pos);
  void setHasTreasure(int x);
  void setIsDead(bool isDead);
 private:
  std::string name_;
  Position pos_{};
  bool isDead_;
  int treasure_;
  int points_;
};
#endif  // _PLAYER_H_
