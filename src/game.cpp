#include "game.h"
#include "board.h"
#include "gamestate.h"
#include "gamelogic.h"

using namespace Jewelsare;


Game::Game(const GameSettings &settings,QObject *parent) :
	QObject(parent)
{
	switch (settings.difficulty) {
	case Difficulty::EASY:
		board_ = new Board(Board::LARGE,dynamic_cast<QWidget*>(parent));
		break;
	case Difficulty::MEDIUM:
		board_ = new Board(Board::MEDIUM,dynamic_cast<QWidget*>(parent));
		break;
	case Difficulty::HARD:
		board_ = new Board(Board::SMALL,dynamic_cast<QWidget*>(parent));
		break;
	default:
		break;
	}

	game_logic_ = new GameLogic();
}

Game::~Game()
{

}
