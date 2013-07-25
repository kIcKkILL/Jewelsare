#ifndef GAME_H
#define GAME_H

#include <QObject>
#include "board.h"
#include "util/jewelwidget.h"

class QWidget;
namespace Jewelsare {

class Board;
class ScoreSystem;
struct GameSettings;
class ModeLogic;

class Game : public QObject
{
	Q_OBJECT
public:
	explicit Game(const GameSettings &settings,QObject *parent = 0);
	std::list<BoardEvent> Swap(JewelPos,Jewelsare::SwapDirection direction);
	BoardEvent NewGame();
	void Pause();
	void Resume();
	
	// copy inhibited
	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;

signals:
	void ScoreUpdated(int);
	void TimeTick(int);
	void GameEnd(int score);
	void Hint(Jewelsare::JewelPos);
	
public slots:
	void EndGame_();

private:
	Board *board_;
	ScoreSystem *score_system_;
	ModeLogic *mode_logic_;
	bool hint_;
};

}
#endif // GAME_H
