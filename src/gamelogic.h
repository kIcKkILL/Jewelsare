#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include <QObject>
#include <QTimer>
#include "util/countdowntimer.h"

namespace Jewelsare {

// Should be used as interface
class ModeLogic : public QObject
{
	Q_OBJECT
public:
	ModeLogic(QObject *parent = 0);
	virtual int NextGeneration() = 0;
	void Pause();
	void Resume();
	virtual void FinishedOneMove() = 0;

	// copy inhibited
	ModeLogic() = delete;
	ModeLogic(const ModeLogic&) = delete;
	ModeLogic& operator=(const ModeLogic&) = delete;

signals:
	void TimeTick(int);
	void TimeOut();
protected:
	CountdownTimer *timer_;
};

class TimeOutMode : public ModeLogic
{
	Q_OBJECT
public:
	TimeOutMode();
	int NextGeneration();
	void FinishedOneMove() {} // do nothing in TimeOutMode

};

class FastReactionMode : public ModeLogic
{
	Q_OBJECT
public:
	FastReactionMode();
	int NextGeneration();
	void IncreaseDifficulty();
	void ReduceDifficulty();
	void FinishedOneMove();
private:
	int diff_;
	int count_;
};

}

#endif // GAMELOGIC_H
