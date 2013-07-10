#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <QObject>

namespace Jewelsare {

enum class Difficulty { EASY, MEDIUM, HARD };
enum class Mode { TIME_LIMIT, FAST_REACTION };
struct GameSettings {
	Mode mode;
	Difficulty difficulty;
};

class QBasicTimer;
class ScoreSystem;

class GameState : public QObject
{
	Q_OBJECT
public:
	enum State { PAUSE, INGAME, ENDED };

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
	State state_;
};

}
#endif // GAMESTATE_H
