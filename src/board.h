#ifndef BOARD_H
#define BOARD_H
#include "util/jewelwidget.h"
#include <list>
#include <utility>
#include <vector>

class QMouseEvent;
class QPaintEvent;

namespace Jewelsare {

struct JewelPos {
	// (0,0) (0,1) (0,2) ...
	// (1,0) (1,1) (1,2) ...
	// ...
	JewelPos(int x,int y) {this->x=x,this->y=y;}
	int x;
	int y;
};

typedef std::pair<JewelPos,int> JewelInfo;

class Board;

class BoardEvent {
friend class Board;
public:
	enum class EventType {NEW,FALL,DIE};

	BoardEvent(EventType etype);
	const EventType type;

	std::list<JewelInfo> GetNewPos() const {return info1_;}
	std::list<JewelPos> GetDiePos() const {return pos2_;}
	void SetNewPos(std::list<JewelInfo> list) {info1_ = list;}
	void SetDiePos(std::list<JewelPos> list) {pos2_ = list;}
	std::pair<std::list<JewelInfo>,std::list<JewelInfo>> GetFallPos();
private:
	std::list<JewelInfo> info1_;
	std::list<JewelPos> pos2_;
};

class Board
{
static const int kSmallSize = 8;
static const int kMediumSize = 10;
static const int kLargeSize = 12;

public:
	enum Size { SMALL = kSmallSize, MEDIUM = kMediumSize, LARGE = kLargeSize };

	explicit Board(Size);
	std::list<BoardEvent> Swap(JewelPos,JewelWidget::SwapDirection);
	void SetGenerationFactor(int f) {generation_factor_ = f;}
	int GetColorAt(int x,int y) { return board_[x][y]; }
	void Generate();

private:
	typedef std::vector<std::vector<int>> IntTab;
	int PossibleSwap(const IntTab&) const;
	std::list<JewelPos> Eliminatable(const IntTab&) const;
	void Fall(IntTab&);

	IntTab board_;
	int generation_factor_;
	const Size size_;
};

}
#endif // BOARD_H
