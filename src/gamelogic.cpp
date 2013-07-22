#include "gamelogic.h"

using namespace Jewelsare;

TimeOutMode::TimeOutMode()
{
	timer_= new CountdownTimer(180,this);
	connect(timer_,SIGNAL(TimeOut()),this,SIGNAL(TimeOut()));
	//connect(timer_,SIGNAL(Tick()),this,SLOT(TickHelper_()));
	connect(timer_,&CountdownTimer::Tick,[=](){
		emit(TimeTick(timer_->GetTimeRemained()));
	});
	timer_->Start();
}

void TimeOutMode::Pause()
{
	timer_->Pause();
}

void TimeOutMode::Resume()
{
	timer_->Resume();
}
