#ifndef _PLAYER_H_
#define _PLAYER_H_

#include<string>
#include <utility>
struct Position {
  int row;
  int col;

  // already implemented for you!
  bool operator==(const Position &other) const {
    return row == other.row && col == other.col;
  }
};

class Player {
 public:
  Player(std::string name, bool is_human);

  // These are already implemented for you
  std::string get_name() const { return name_; }  // inline member function
  int get_points() const { return points_; }  // inline member function
  Position get_position() const { return pos_; }  // inline member function
  bool is_human() const { return is_human_; }  // inline member function
  bool hasTreasure() const { return has_Treasure_; }  // inline member function
  bool isDead() const { return isDead_; }  // inline member function

  void ChangePoints(int x);

  // set a new position for this player
  void SetPosition(Position pos);

  // checks if the player owns a treasure
  void setHasTreasure(int x);

  //checks if the enemy is dead
  void setIsDead(bool isdead);

  // You may want to implement these functions as well
  // ToRelativePosition is a function we used to translate positions
  // into direction s relative to the player (up, down, etc)
  std::string ToRelativePosition(Position other);

  // Convert this player to a string representation of their name and points
  std::string Stringify();

  // You may add other functions as needed/wanted
  bool canEatGhosts() const { return has_Treasure_ > 0; }

 private:
  std::string name_;
  int points_;
  Position pos_{};
  bool is_human_;
  int has_Treasure_;
  bool isDead_;

  // You may add other fields as needed

}; // class Player

#endif  // _PLAYER_H_
