#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include <QObject>
#include <QTimer>

namespace Jewelsare {

class ModeLogic : public QObject
{
	Q_OBJECT
public:
	virtual int NextGeneration() = 0;
signals:
	void TimeOut();
};

class TimeOutMode : public ModeLogic {
	Q_OBJECT
public:
	TimeOutMode()
	{
		timer_.start(5000);
		connect(&timer_,SIGNAL(timeout()),this,SIGNAL(TimeOut()));
	}
	int NextGeneration() { return 5; }
signals:
	void TimeOut();
private:
	QTimer timer_;
};

}

#endif // GAMELOGIC_H
