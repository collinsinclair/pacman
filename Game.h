/**
Collin Sinclair
Homework 1: Pacman
*/

#ifndef _GAME_H_
#define _GAME_H_
#include <vector>
#include "Player.h"
const int BOARD_DIMENSION_X = 30;
const int BOARD_DIMENSION_Y = 30;
enum class SquareType {
  Wall,
  Dots,
  Pacman,
  Treasure,
  EnemyNoPoint,
  EnemyPoint,
  Empty,
};
/**
 * turn a square type into a string that can be printed to the console (mainly unicode emojis!)
 * @param sq
 * @return
 */
std::string SquareTypeStringify(SquareType sq, Player *p);
class Board {
 public:
  /**
   * default constructor for the board
   */
  explicit Board(Player *p);
  static int get_rows() { return BOARD_DIMENSION_Y; }
  static int get_cols() { return BOARD_DIMENSION_X; }
  /**
   * get the value of a square on the grid at a specified position
   * @param pos
   * @return
   */
  SquareType get_square_value(Position pos) const;
  /**
   * converts a map number to square type
   * @param i map number
   * @return SquareType
   */
  static SquareType NumToSquareType(int i);
  /**
   * set the value of a square to the given SquareType
   * @param pos
   * @param value
   */
  void SetSquareValue(Position pos, SquareType value);
  /**
   * get the possible Positions that a Player/Enemy could move too (those that are neither off the board nor into a
   * wall)
   * @calls get_square_value
   * @param p
   * @return
   */
  std::vector<Position> GetMoves(Player *p) const;
  /**
   * move a player to a new position on the board
   * @calls GetMoves
   * @param p
   * @param new_pos
   * @param enemyList
   * @return return true if they moved successfully, false otherwise
   */
  bool MovePlayer(Player *p, Position new_pos, const std::vector<Player *> &enemyList);
  /**
   * move an enemy to a new position on the board
   * @calls GetMoves, SetSquareValue
   * @param enemy
   * @return true if they moved successfully, false otherwise
   */
  bool MoveEnemy(Player *enemy, Player *pacman);
  /**
   * facilitates printing to the console on each turn
   * @calls get_square_value, SetSquareValue
   * @param os
   * @param b
   * @return
   */
  friend std::ostream &operator<<(std::ostream &os, const Board &b);
 private:
  SquareType arr_[BOARD_DIMENSION_Y][BOARD_DIMENSION_X];
  int rows_;
  int cols_;
  Player *p_;
};
class Game {
 public:
  /**
   * default constructor for Game
   */
  explicit Game(Board *b);
  /**
   * have the given Player take their turn
   * @calls MovePlayer
   * @param p
   * @param enemyList
   */
  void TakeTurn(Player *p, const std::vector<Player *> &enemyList);
  /**
   * have an enemy take its turn
   * @calls MoveEnemy
   * @param enemy
   */
  void TakeTurnEnemy(Player *enemy, Player *pacman);
  /**
   * specifies whether the game is over
   * @calls get_square_value
   * @param p
   * @return true if game over, false otherwise
   */
  bool IsGameOver(Player *p) const { return CheckIfDotsOver() or p->IsDead(); };
  /**
   * @calls get_square_value
   * specifies whether the player has collected all of the dots
   * @return true if all pellets have been collected
   */
  bool CheckIfDotsOver() const {return dots_remaining_ == 0;}
  int CountDots();
  /**
   * @calls GetMoves
   * compiles game stats to display for player after a game ends
   * @param p
   * @return
   */
  std::string GenerateReport(Player *p) const;
 private:
  Board *board_;
  int turn_count_;
  int dots_remaining_;
};
#endif
