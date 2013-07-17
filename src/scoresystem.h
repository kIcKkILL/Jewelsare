#ifndef SCORESYSTEM_H
#define SCORESYSTEM_H

namespace Jewelsare {
class ScoreSystem
{
public:
	ScoreSystem();
	void FirstGain(int);
	void MoreGain(int);
	void FinishMove();
	int GetScore() { return total_score_; }

private:
	int combo;
	int total_score_;
};

}
#endif // SCORESYSTEM_H
