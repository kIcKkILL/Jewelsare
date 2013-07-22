#ifndef COUNTDOWNTIMER_H
#define COUNTDOWNTIMER_H

#include <QObject>

class QTimer;

class CountdownTimer : public QObject
{
	Q_OBJECT
public:
	explicit CountdownTimer(int sec,QObject *parent = 0);
	void Start();
	void Pause();
	void Resume();
	void SetTimeRemained(int sec);
	int GetTimeRemained() {return remain_sec_;}

	// copy inhibited
	CountdownTimer(const CountdownTimer&) = delete;
	CountdownTimer& operator=(const CountdownTimer&) = delete;

signals:
	void TimeOut();
	void Tick();
	
private slots:
	void InternalTimerTimeout_();

private:
	int remain_sec_;
	bool paused_;
	bool dead_;
	QTimer *tick_;

};

#endif // COUNTDOWNTIMER_H
