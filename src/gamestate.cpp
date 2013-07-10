#include <QBasicTimer>

#include "gamestate.h"
#include "scoresystem.h"


using namespace Jewelsare;

GameState::GameState(QObject *parent) :
	QObject(parent)
{

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

}
