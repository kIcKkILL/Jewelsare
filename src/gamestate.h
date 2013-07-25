#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <QObject>
#include <vector>
#include "board.h"
#include "util/jewelwidget.h"

namespace Jewelsare {

enum class Difficulty { EASY, MEDIUM, HARD };
enum class Mode { TIME_LIMIT, FAST_REACTION };
struct GameSettings {
	Mode mode;
	Difficulty difficulty;
};

class Game; // forward statement

class HighScoresStorage {
public:
	static const int kMaxRecord = 8;
	HighScoresStorage();
	bool NewScore(Mode mode,int score);
	int GetScore(Mode mode,int rank);
	void WriteToFile();
	~HighScoresStorage();

	// copy inhibited
	HighScoresStorage(const HighScoresStorage&) = delete;
	HighScoresStorage& operator=(const HighScoresStorage&) = delete;

private:
	std::vector<int> tl_scores_;
	std::vector<int> fr_scores_;
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
	void Abort();
	int GetScore(Mode mode,int rank) {return highscores_.GetScore(mode,rank);}
	std::list<BoardEvent> Swap(JewelPos,Jewelsare::SwapDirection direction);

	// copy inhibited
	GameState(const GameState&) = delete;
	GameState& operator=(const GameState&) = delete;

	State state() const;

signals:
	void TimeTick(int remain);
	void ScoreUpdated(int new_score);
	void GameEnd(bool high_score);
	void Hint(Jewelsare::JewelPos pos);

public slots:

private slots:
	void GameEndProcessor_(int);

private:
	HighScoresStorage highscores_;
	GameSettings *settings_;
	State state_;
	Game *game_;
};

}
#endif // GAMESTATE_H
