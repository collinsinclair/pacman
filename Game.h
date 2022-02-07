#ifndef _GAME_H_
#define _GAME_H_

#include <vector>
#include "Player.h"

const int BOARD_DIMENSION_X = 30;
const int BOARD_DIMENSION_Y = 30;
enum class SquareType { Wall, Dots, Pacman, Treasure, Enemies, Empty, PowerfulPacman, Trap, EnemySpecialTreasure };

/**
 * turn a square type into a string that can be printed to the console (mainly unicode emojis!)
 * @param sq
 * @return
 */
std::string SquareTypeStringify(SquareType sq);

class Board {
 public:
  /**
   * default constructor for the board
   */
  Board();

  // already implemented in line
  static int get_rows() { return BOARD_DIMENSION_Y; }  // you should be able to change the size of your
  static int get_cols() { return BOARD_DIMENSION_X; }  // board by changing these numbers and the numbers in the arr_ field

  /**
   * get the value of a square on the grid at a specified position
   * @param pos
   * @return
   */
  SquareType get_square_value(Position pos) const;

  static SquareType numToSquareType(int i);

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
  std::vector<Position> GetMoves(Player *p);

  /**
   * move a player to a new position on the board
   * @calls GetMoves
   * @param p
   * @param pos
   * @param enemylist
   * @return return true if they moved successfully, false otherwise
   */
  bool MovePlayer(Player *p, Position pos, std::vector<Player *> enemylist);

  /**
   * move an enemy to a new position on the board
   * @calls GetMoves, SetSquareValue
   * @param p
   * @param pos
   * @return true if they moved successfully, false otherwise
   */
  bool MoveEnemy(Player *p, Position pos);

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
  int rows_; // might be convenient but not necessary
  int cols_;
  // you may add more fields, as needed
};  // class Board

class Game {
 public:
  /**
   * default constructor for Game
   */
  Game(); // constructor

  /**
   * initialize a new game with one human player and a number of enemies to generate
   * @calls SetSquareValue
   * @param human
   * @param enemylist
   * @param enemies
   */
  void NewGame(Player *human, std::vector<Player *> enemylist, const int enemies);

  /**
   * have the given Player take their turn
   * @calls MovePlayer
   * @param p
   * @param enemylist
   */
  void TakeTurn(Player *p, std::vector<Player *> enemylist);

  /**
   * have an enemy take its turn
   * @calls MoveEnemy
   * @param p
   */
  void TakeTurnEnemy(Player *p);

  /**
   * specifies whether the game is over
   * @calls get_square_value
   * @param p
   * @return true if game over, false otherwise
   */
  bool IsGameOver(Player *p);

  /**
   * @calls get_square_value
   * specifies whether the player has collected all of the dots
   * @return true if all pellets have been collected
   */
  bool CheckifdotsOver();

  /**
   * @calls GetMoves
   * compiles game stats to display for player after a game ends
   * @param p
   * @return
   */
  std::string GenerateReport(Player *p);

  /**
   * facilitates printing to the console to start and end games, as well as in between games (menu system)
   * @param os
   * @param m
   * @return
   */
  friend std::ostream &operator<<(std::ostream &os, const Game &m);

 private:
  Board *board_;
  std::vector<Player *> players_;
  int turn_count_;
  int dots_count_;
  bool GameOver;

  // you may add more fields, as needed

};  // class Game

#endif  // _GAME_H_
