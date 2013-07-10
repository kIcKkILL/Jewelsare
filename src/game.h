#ifndef GAME_H
#define GAME_H

namespace Jewelsare {

class GameLogic;
class Board;

class Game
{
public:
	Game();

private:
	GameLogic *game_logic_;
	Board *board_;
};

}
#endif // GAME_H
