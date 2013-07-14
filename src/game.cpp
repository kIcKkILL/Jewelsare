#include "gamestate.h"
#include "game.h"
#include "board.h"
#include "gamelogic.h"
#include "scoresystem.h"

using namespace Jewelsare;

Game::Game(const GameSettings &settings,QObject *parent)
{
	Board::Size boardsize;
	switch(settings.difficulty) {
	case Difficulty::EASY:
		boardsize = Board::SMALL;
		break;
	case Difficulty::MEDIUM:
		boardsize = Board::MEDIUM;
		break;
	case Difficulty::HARD:
		boardsize = Board::LARGE;
		break;
	default:
		break;
	}
	board_ = new Board(boardsize);
	mode_logic_ = new TimeOutMode();
	board_->SetGenerationFactor(mode_logic_->NextGeneration());
	board_->Generate();
	connect(mode_logic_,SIGNAL(TimeOut()),this,SLOT(EndGame()));
}

std::list<BoardEvent> Game::Swap(JewelPos pos,JewelWidget::SwapDirection direction)
{
	// update generation factor
	board_->SetGenerationFactor(mode_logic_->NextGeneration());
}

void Game::EndGame()
{

}
