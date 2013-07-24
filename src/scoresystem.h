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

	// copy inhibited
	ScoreSystem(const ScoreSystem&) = delete;
	ScoreSystem& operator=(const ScoreSystem&) = delete;

private:
	int combo_;
	int total_score_;
};

}
#endif // SCORESYSTEM_H
