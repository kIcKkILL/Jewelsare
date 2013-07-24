#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include <QObject>
#include <QTimer>
#include "util/countdowntimer.h"

namespace Jewelsare {

class ModeLogic : public QObject
{
	Q_OBJECT
public:
	virtual int NextGeneration() = 0;
	virtual void Pause() = 0;
	virtual void Resume() = 0;

	// copy inhibited
	ModeLogic(const ModeLogic&) = delete;
	ModeLogic& operator=(const ModeLogic&) = delete;

signals:
	void TimeTick(int);
	void TimeOut();
};

class TimeOutMode : public ModeLogic {
	Q_OBJECT
public:
	explicit TimeOutMode();
	int NextGeneration();
	void Pause();
	void Resume();
signals:
	void TimeTick(int);
	void TimeOut();

private:
	CountdownTimer *timer_;
};

class FastReactionMode : public ModeLogic {
	Q_OBJECT
public:
	void IncreaseDifficulty();
	void ReduceDifficulty();
	FastReactionMode()
	{
		// TODO
	}
	int NextGeneration() { return 5; }
	void Pause(){}
	void Resume(){}
	// TODO
};

}

#endif // GAMELOGIC_H
