#include "gamelogic.h"

using namespace Jewelsare;


TimeOutMode::TimeOutMode()
{
	timer_= new CountdownTimer(180,this);
	connect(timer_,&CountdownTimer::TimeOut,this,&TimeOutMode::TimeOut);
}
