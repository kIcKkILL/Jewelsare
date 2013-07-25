#include "countdowntimer.h"
#include <QTimer>
#include <cassert>

CountdownTimer::CountdownTimer(int sec,QObject *parent) :
	QObject(parent),
	remain_sec_(0),
	paused_(false),
	dead_(true)
{
	tick_ = new QTimer(this);
	tick_->setInterval(1000);
	tick_->setSingleShot(false); // repeat ticks
	connect(tick_,SIGNAL(timeout()),this,SLOT(InternalTimerTimeout_()));
	SetTimeRemained(sec);
}

void CountdownTimer::Start()
{
	if(dead_) {
		dead_ = false;
		tick_->start();
	}
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
	if(!dead_ && !paused_) {
		if(--remain_sec_ == 0) {
			emit(TimeOut());
			dead_ = true;
		}
		emit(Tick());
	}
}

void CountdownTimer::SetTimeRemained(int sec)
{
	if(sec > 0)
		remain_sec_ = sec;
}
