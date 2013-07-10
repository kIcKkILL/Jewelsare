#ifndef GAME_H
#define GAME_H

#include <QObject>

namespace Jewelsare {

class GameLogic;
class Board;
struct GameSettings;

class Game : public QObject
{
public:
	explicit Game(const GameSettings &settings,QObject *parent = 0);
	~Game();

private:
	GameLogic *game_logic_;
	Board *board_;
};

}
#endif // GAME_H
