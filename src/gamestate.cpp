#include <QBasicTimer>

#include "gamestate.h"
#include "game.h"
#include "scoresystem.h"

namespace Jewelsare {
struct GameSettings {
	Jewelsare::GameState::Mode mode;
	Jewelsare::GameState::Difficulty difficulty;
};

}

using namespace Jewelsare;

GameState::GameState(QObject *parent) :
	QObject(parent)
{

}

void Jewelsare::GameState::SetDifficulty(GameState::Difficulty diff)
{
	settings_->difficulty = diff;
}

void Jewelsare::GameState::SetMode(GameState::Mode mode)
{
	settings_->mode = mode;
}

GameState::~GameState() {

}

void GameState::StartNewGame()
{

}
