#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <QObject>

namespace Jewelsare {

struct GameSettings;
class QBasicTimer;
class ScoreSystem;

class GameState : public QObject
{
	Q_OBJECT
public:
	enum class Difficulty { EASY, MEDIUM, HARD };
	enum class Mode { TIME_LIMIT, FAST_REACTION };

	explicit GameState(QObject *parent = 0);
	virtual ~GameState();
	void SetDifficulty(Difficulty);
	void SetMode(Mode);

signals:
	
public slots:
	void StartNewGame();

private:
	QBasicTimer *timer_;
	GameSettings *settings_;
	ScoreSystem *score_;
};

}
#endif // GAMESTATE_H
