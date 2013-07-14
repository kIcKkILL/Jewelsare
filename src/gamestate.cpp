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

void GameState::StartNewGame()
{
	game_ = new Game(*settings_);
	state_ = INGAME;
}

std::list<BoardEvent> GameState::Swap(JewelPos pos,JewelWidget::SwapDirection direction)
{
	return game_->Swap(pos,direction);
}
