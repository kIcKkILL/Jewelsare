#include "gamestate.h"
#include "game.h"
#include "board.h"
#include "gamelogic.h"
#include "scoresystem.h"

using namespace Jewelsare;

Game::Game(const GameSettings &settings,QObject *parent) :
	QObject(parent)
{
	Board::Size boardsize;
	switch(settings.difficulty) {
	case Difficulty::EASY:
		boardsize = Board::LARGE;
		break;
	case Difficulty::MEDIUM:
		boardsize = Board::MEDIUM;
		break;
	case Difficulty::HARD:
		boardsize = Board::SMALL;
		break;
	default:
		break;
	}
	board_ = new Board(boardsize);

	// Create appropriate GameLogic
	switch (settings.mode) {
	case Mode::TIME_LIMIT:
		mode_logic_ = new TimeOutMode();
		break;
	case Mode::FAST_REACTION:
		mode_logic_ = new FastReactionMode();
		break;
	}

	score_system_ = new ScoreSystem;
	board_->SetGenerationFactor(mode_logic_->NextGeneration());
	connect(mode_logic_,SIGNAL(TimeOut()),this,SLOT(EndGame()));
}

std::list<BoardEvent> Game::Swap(JewelPos pos,Jewelsare::SwapDirection direction)
{
	// update generation factor
	board_->SetGenerationFactor(mode_logic_->NextGeneration());
	std::list<BoardEvent> events = board_->Swap(pos,direction);
	bool first = true;
	for(BoardEvent event : events) {
		if(first && event.type == BoardEvent::EventType::DIE) {
			score_system_->FirstGain(event.GetDiePos().size());
			first = false;
		}
		if(!first && event.type == BoardEvent::EventType::DIE)
			score_system_->MoreGain(event.GetDiePos().size());
	}
	score_system_->FinishMove();
	return events;
}

BoardEvent Game::NewGame()
{
	return board_->Init();
}

void Game::EndGame()
{

}
