/**
Collin Sinclair
Homework 1: Pacman
*/

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
  /**
   * constructor for player
   * @param name name of human player
   */
  Player(std::string name);
  /**
   * converts user input to position on board (e.g., w = position above player)
   * @param d w, a, s, or d
   * @return position
   */
  Position CharToPos(char d) const;
  Position get_position() const { return pos_; }
  bool CanEatGhosts() const { return treasure_ > 0; }
  int NumTreasure() const { return treasure_; }
  bool IsDead() const { return isDead_; }
  int get_points() const { return points_; }
  /**
   * returns a string representation of player stats
   * @return
   */
  std::string Stringify();
  /**
   * generates a string representing the direction a player must move to get to a position
   * @param other the position to get to
   * @return the string representing the direction player must move
   */
  std::string ToRelativePosition(Position other) const;
  std::string get_name() const { return name_; }
  void ChangePoints(int x);
  void SetPosition(Position pos);
  void SetHasTreasure(int x);
  void SetIsDead(bool isDead);
 private:
  std::string name_;
  Position pos_{};
  bool isDead_;
  int treasure_;
  int points_;
};
#endif  // _PLAYER_H_
