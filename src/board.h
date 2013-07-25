#ifndef BOARD_H
#define BOARD_H
#include "util/jewelwidget.h"
#include <list>
#include <utility>
#include <vector>

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
public:
	enum class EventType {NEW,FALL,DIE};

	BoardEvent(const EventType etype);
	EventType type;

	std::list<JewelInfo> GetNewPos() const {return info1_;}
	std::list<JewelPos> GetDiePos() const {return pos2_;}
	std::list<std::pair<JewelPos,JewelPos>> GetFallPos() const {return fall_;}
	void SetFallPos(std::list<std::pair<JewelPos,JewelPos>> fall) {fall_=fall;}
	void SetNewPos(std::list<JewelInfo> list) {info1_ = list;}
	void SetDiePos(std::list<JewelPos> list) {pos2_ = list;}

	// default copy behaviors
	BoardEvent(const BoardEvent&) = default;
	BoardEvent& operator=(const BoardEvent&) = default;

private:
	std::list<std::pair<JewelPos,JewelPos>> fall_;
	std::list<JewelInfo> info1_;
	std::list<JewelPos> pos2_;
};

class Board
{
typedef std::vector<std::vector<int>> IntTab;

public:
	static const int kSmallSize = 8;
	static const int kMediumSize = 10;
	static const int kLargeSize = 12;

	enum Size { SMALL = kSmallSize, MEDIUM = kMediumSize, LARGE = kLargeSize };

	explicit Board(Size);
	std::list<BoardEvent> Swap(JewelPos,Jewelsare::SwapDirection);
	void SetGenerationFactor(int f) {generation_factor_ = f;}
	JewelPos GetPossibleSwap();
	int GetColorAt(int x,int y) {return board_[x][y];}
	BoardEvent Init();

	// copy inhibited
	Board(const Board&) = delete;
	Board& operator=(const Board&) = delete;

private:
	std::list<JewelInfo> Generate(IntTab &tab);
	int PossibleSwap(const IntTab&);
	std::list<JewelPos> Eliminatable(const IntTab&) const;
	std::list<std::pair<JewelPos,JewelPos>> Fall(IntTab&);

	JewelPos last_possible_swap_;
	IntTab board_;
	int generation_factor_;
	const Size size_;
};

}
#endif // BOARD_H
