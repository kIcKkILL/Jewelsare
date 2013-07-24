#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <QObject>
#include "board.h"
#include "util/jewelwidget.h"

namespace Jewelsare {

enum class Difficulty { EASY, MEDIUM, HARD };
enum class Mode { TIME_LIMIT, FAST_REACTION };
struct GameSettings {
	Mode mode;
	Difficulty difficulty;
};

class Game;

class HighScoresStorage {
	// TODO Implement this class
public:
	HighScoresStorage() {}
	void NewScore(int) {}
	int GetScore(int rank) {return -1;}

	// copy inhibited
	HighScoresStorage(const HighScoresStorage&) = delete;
	HighScoresStorage& operator=(const HighScoresStorage&) = delete;
};

class GameState : public QObject
{
	Q_OBJECT
public:
	enum State { PAUSE, INGAME, ENDED };

	explicit GameState(QObject *parent = 0);
	virtual ~GameState();
	void SetDifficulty(Difficulty);
	void SetMode(Mode);
	BoardEvent StartNewGame();
	void Pause();
	void Resume();
	std::list<BoardEvent> Swap(JewelPos,Jewelsare::SwapDirection direction);

	// copy inhibited
	GameState(const GameState&) = delete;
	GameState& operator=(const GameSTate&) = delete;

signals:
	void TimeTick(int remain);
	void ScoreUpdated(int new_score);

public slots:

private:
	HighScoresStorage highscores_;
	GameSettings *settings_;
	State state_;
	Game *game_;
};

}
#endif // GAMESTATE_H
