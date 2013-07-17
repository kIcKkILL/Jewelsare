#include "scoresystem.h"
using namespace Jewelsare;

ScoreSystem::ScoreSystem() :
	combo(0)
{
}

void ScoreSystem::FirstGain(int gain)
{
	total_score_ += gain;
	++combo;
}

void ScoreSystem::MoreGain(int gain)
{
	total_score_ += gain + combo;
	++combo;
}

void ScoreSystem::FinishMove()
{
	combo = 0;
}
