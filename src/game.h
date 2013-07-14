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
	std::list<BoardEvent> Swap(JewelPos,JewelWidget::SwapDirection direction);
	
signals:
	
public slots:
	void EndGame();

private:
	Board *board_;
	ScoreSystem *score_system_;
	ModeLogic *mode_logic_;
};

}
#endif // GAME_H