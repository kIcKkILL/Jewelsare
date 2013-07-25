#include "scoresystem.h"
using namespace Jewelsare;

ScoreSystem::ScoreSystem() :
	combo_(0)
{
}

void ScoreSystem::FirstGain(int gain)
{
	total_score_ += gain+(gain-3);
	++combo_;
}

void ScoreSystem::MoreGain(int gain)
{
	total_score_ += gain+(gain-3) + combo_*2;
	++combo_;
}

void ScoreSystem::FinishMove()
{
	combo_ = 0;
}
