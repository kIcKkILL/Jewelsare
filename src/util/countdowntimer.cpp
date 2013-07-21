#include "countdowntimer.h"
#include <QTimer>

CountdownTimer::CountdownTimer(int sec,QObject *parent) :
	QObject(parent),
	dead_(true),
	paused_(false),
	remain_sec_(0)
{
	tick_ = new QTimer(this);
	tick_->setInterval(1000);
	tick_->setSingleShot(false); // repeat ticks
	connect(tick_,SIGNAL(timeout(QPrivateSignal)),this,SLOT(InternalTimerTimeout_()));
	SetTimeRemained(sec);
}

void CountdownTimer::Start()
{
	if(dead_)
		tick_->start(remain_sec_);
}

void CountdownTimer::Pause()
{
	paused_ = true;
}

void CountdownTimer::Resume()
{
	paused_ = false;
}

void CountdownTimer::InternalTimerTimeout_()
{
	if(!dead_ || !paused_)
		if(--remain_sec_ == 0) {
			emit(TimeOut());
			dead_ = true;
		}
}

void CountdownTimer::SetTimeRemained(int sec)
{
	if(sec > 0)
		remain_sec_ = sec;
}
