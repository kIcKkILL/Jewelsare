#include "gamestate.h"
#include "scoresystem.h"
#include "game.h"


using namespace Jewelsare;

GameState::GameState(QObject *parent) :
	QObject(parent),
	state_(ENDED)
{
	settings_ = new GameSettings;
}

void GameState::SetDifficulty(Difficulty diff)
{
	settings_->difficulty = diff;
}

void GameState::SetMode(Mode mode)
{
	settings_->mode = mode;
}

GameState::~GameState() {

}

BoardEvent GameState::StartNewGame()
{
	game_ = new Game(*settings_);
	connect(game_,SIGNAL(TimeTick(int)),this,SIGNAL(TimeTick(int)));
	connect(game_,SIGNAL(ScoreUpdated(int)),this,SIGNAL(ScoreUpdated(int)));
	state_ = INGAME;
	return game_->NewGame();
}

void GameState::Pause()
{
	game_->Pause();
}

void GameState::Resume()
{
	game_->Resume();
}

std::list<BoardEvent> GameState::Swap(JewelPos pos,Jewelsare::SwapDirection direction)
{
	return game_->Swap(pos,direction);
}
