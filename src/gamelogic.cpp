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
	timer_->SetTimeRemained(5);
	timer_->Start();
	diff_ = 4;
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
	timer_->SetTimeRemained(5);
}
