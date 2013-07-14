#ifndef SCORESYSTEM_H
#define SCORESYSTEM_H
#include <QtGlobal>

namespace Jewelsare {
class ScoreSystem
{
public:
	ScoreSystem();
	virtual void FirstGain() = 0;
	virtual void MoreGain() = 0;
	virtual void FinishMove() = 0;
	virtual ~ScoreSystem() = 0;
	qint64 GetScore() { return total_score_; }

private:
	qint64 total_score_;
};

}
#endif // SCORESYSTEM_H