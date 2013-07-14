#include <QPainter>
#include <QMouseEvent>
#include <QPaintEvent>
#include <cstdlib>
#include <ctime>
#include "board.h"
#include "util/jewelwidget.h"

using namespace Jewelsare;
using namespace std;

Board::Board(Size size) :
	size_(size),
	generation_factor_(1),
	board_(size,vector<int>(size,0))
{
	srand(time(NULL));
}

list<BoardEvent> Board::Swap(JewelPos pos,JewelWidget::SwapDirection direction)
{
	list<BoardEvent> events;
	IntTab tab = board_;
	int i = pos.x, j = pos.y;

	switch(direction) {
	case JewelWidget::SwapDirection::UP:
		tab[i][j] = tab[i-1][j];
		tab[i-1][j] = board_[i][j];
		break;
	case JewelWidget::SwapDirection::DOWN:
		tab[i][j] = tab[i+1][j];
		tab[i+1][j] = board_[i][j];
		break;
	case JewelWidget::SwapDirection::LEFT:
		tab[i][j] = tab[i][j-1];
		tab[i][j-1] = board_[i][j];
		break;
	case JewelWidget::SwapDirection::RIGHT:
		tab[i][j] = tab[i][j+1];
		tab[i][j+1] = board_[i][j];
		break;
	default:
		break;
	}
	// get list of eliminated jewelpos
	list<JewelPos> deleted = Eliminatable(tab);
	// if not a valid swap
	if(deleted.size()==0)
		return events; // return blank list
	// a valid swap
	board_ = tab;
	BoardEvent new_event(BoardEvent::EventType::DIE);
	new_event.SetDiePos(deleted);
	events.push_back(new_event);
	for(JewelPos pos :deleted)
		board_[pos.x][pos.y] = 0;
	// TODO fall->eliminate->fall->eliminate-> ...
}

void Board::Generate()
{
	IntTab tmptab = board_;
	do {
		for(int i=0;i!=size_;++i)
			for(int j=0;j!=size_;++j)
				if(board_[i][j] == 0) {
					// random between 1 and 5
					tmptab[i][j] = rand() % 5+1;
				}
	} while(Eliminatable(tmptab).size()==0 && PossibleSwap(tmptab)>=generation_factor_);
	// update
	board_ = tmptab;
}

int Board::PossibleSwap(const IntTab& tab) const
{
	IntTab tab2 = tab;
	int count = 0;
	// swap right
	for(int i=0;i!=size_;++i)
		for(int j=0;j!=size_-1;++j) {
			// swap
			tab2[i][j] = tab2[i][j+1];
			tab2[i][j+1] = tab[i][j];
			if(Eliminatable(tab2).size()!=0)
				++count;
			// revert changes
			tab2[i][j] = tab[i][j];
			tab2[i][j+1] = tab[i][j+1];
		}

	for(int j=0;j!=size_;++j)
		for(int i=0;i!=size_-1;++i) {
			// swap
			tab2[i][j] = tab2[i+1][j];
			tab2[i+1][j] = tab[i][j];
			if(Eliminatable(tab2).size()!=0)
				++count;
			// revert changes
			tab2[i][j] = tab[i][j];
			tab2[i+1][j] = tab[i+1][j];
		}
	return count;
}

list<JewelPos> Board::Eliminatable(const Board::IntTab& tab) const
{
	list<JewelPos> ret;
	// check vertically
	for(int i=0;i!=size_;++i)
		for(int j=0;j!=size_;++j) {
			int current = tab[i][j];
			int k;
			for(k=j;k!=size_;++k)
				if(tab[i][k] != current)
					break;
			if(k-j >=3) {
				// add them to list
				for(int l = j;l<=k;++l)
					ret.push_back(JewelPos(i,l));
			}
		}

	// check horizontally
	for(int j=0;j!=size_;++j)
		for(int i=0;i!=size_;++i) {
			int current = tab[i][j];
			int k;
			for(k=i;k!=size_;++k)
				if(tab[k][j] != current)
					break;
			if(k-i >=3) {
				// add them to list
				for(int l = i;l<=k;++l)
					ret.push_back(JewelPos(l,j));
			}
		}
	return ret;
}

void Board::Fall(Board::IntTab& tab)
{
	// FIXME not implemented yet
	for(int i=1;i!=size_;++i)
		for(int j=0;j!=size_;++j)
			if(tab[i][j] == 0) {

			}
}


BoardEvent::BoardEvent(BoardEvent::EventType etype):
	type(etype)
{
}
