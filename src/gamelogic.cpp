#include "gamelogic.h"
#include <cassert>

using namespace Jewelsare;

TimeOutMode::TimeOutMode() :
	ModeLogic(nullptr)
{
	timer_->SetTimeRemained(120);
	timer_->Start();
}

ModeLogic::ModeLogic(QObject *parent) :
	QObject(parent)
{
	timer_= new CountdownTimer(0,this);
	connect(timer_,SIGNAL(TimeOut()),this,SIGNAL(TimeOut()));
	connect(timer_,&CountdownTimer::Tick,[=](){
		emit(TimeTick(timer_->GetTimeRemained()));
	});
}

int TimeOutMode::NextGeneration()
{
	if(timer_->GetTimeRemained() >= 60)
		return 3;
	else
		return 4;
}

void ModeLogic::Pause()
{
	timer_->Pause();
}

void ModeLogic::Resume()
{
	timer_->Resume();
}


FastReactionMode::FastReactionMode() :
	ModeLogic(nullptr)
{
	timer_->SetTimeRemained(4);
	timer_->Start();
	diff_ = 4;
	count_ = 0;
}

int FastReactionMode::NextGeneration()
{
	return diff_;
}

void FastReactionMode::IncreaseDifficulty()
{
	if(diff_>1)
		diff_ -= 1;
}

void FastReactionMode::ReduceDifficulty()
{
	diff_ += 1;
}

void FastReactionMode::FinishedOneMove()
{
	int ntime = 4;
	if(count_ > 10)
		ntime = 3;
	if(count_ > 25)
		ntime - 2;
	timer_->SetTimeRemained(4);
	emit(TimeTick(ntime)); // refresh
	++count_;
}
