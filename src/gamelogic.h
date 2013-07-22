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
signals:
	void TimeTick(int);
	void TimeOut();
};

class TimeOutMode : public ModeLogic {
	Q_OBJECT
public:
	TimeOutMode();
	int NextGeneration() { return 4; } //TODO make it more complicated
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
