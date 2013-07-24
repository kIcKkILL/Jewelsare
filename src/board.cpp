#include <cstdlib>
#include <ctime>
#include "board.h"
#include "util/jewelwidget.h"

using namespace Jewelsare;
using namespace std;

Board::Board(Size size) :
	board_(size,vector<int>(size,0)),
	generation_factor_(1),
	size_(size)
{
	srand(time(NULL));
}

list<BoardEvent> Board::Swap(JewelPos pos,Jewelsare::SwapDirection direction)
{
	list<BoardEvent> events;
	IntTab tab = board_;
	int i = pos.x, j = pos.y;

	switch(direction) {
	case Jewelsare::SwapDirection::UP:
		if(i == 0)
			return events;
		tab[i][j] = tab[i-1][j];
		tab[i-1][j] = board_[i][j];
		break;
	case Jewelsare::SwapDirection::DOWN:
		if(i == size_-1)
			return events;
		tab[i][j] = tab[i+1][j];
		tab[i+1][j] = board_[i][j];
		break;
	case Jewelsare::SwapDirection::LEFT:
		if(j == 0)
			return events;
		tab[i][j] = tab[i][j-1];
		tab[i][j-1] = board_[i][j];
		break;
	case Jewelsare::SwapDirection::RIGHT:
		if(j == size_-1)
			return events;
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
	// elimination
	for(JewelPos pos :deleted)
		board_[pos.x][pos.y] = 0;
	// TODO fall->eliminate->fall->eliminate-> ...
	do {
		//fall
		new_event = BoardEvent(BoardEvent::EventType::FALL);
		new_event.SetFallPos(Fall(board_));
		events.push_back(new_event);
		deleted = Eliminatable(board_);
		if(deleted.size() > 0) {
			new_event = BoardEvent(BoardEvent::EventType::DIE);
			new_event.SetDiePos(deleted);
			events.push_back(new_event);
			// elimination
			for(JewelPos eles : deleted )
				board_[eles.x][eles.y] = 0;
		}
		else
			break;
	} while(true);
	// generate
	new_event = BoardEvent(BoardEvent::EventType::NEW);
	new_event.SetNewPos(Generate(board_));
	events.push_back(new_event);
	return events;
}

BoardEvent Board::Init()
{
	BoardEvent event(BoardEvent::EventType::NEW);
	event.SetNewPos(Generate(board_));
	return event;
}

list<JewelInfo> Board::Generate(IntTab &tab)
{
	IntTab tmptab = tab;
	list<JewelInfo> infolist;
	do {
		infolist.clear();
		for(int i=0;i!=size_;++i)
			for(int j=0;j!=size_;++j)
				if(board_[i][j] == 0) {
					// random between 1 and 5
					tmptab[i][j] = rand() % 5+1;
					infolist.push_back(pair<JewelPos,int>(JewelPos(i,j),tmptab[i][j]));
				}
	} while(!Eliminatable(tmptab).empty() || PossibleSwap(tmptab) < generation_factor_);
	// update
	tab = tmptab;
	return infolist;
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
			if(!Eliminatable(tab2).empty())
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
			if(!Eliminatable(tab2).empty())
				++count;
			// revert changes
			tab2[i][j] = tab[i][j];
			tab2[i+1][j] = tab[i+1][j];
		}
	return count;
}

list<JewelPos> Board::Eliminatable(const Board::IntTab& tab) const
{
	bool eliminated[kLargeSize][kLargeSize] = {0};
	list<JewelPos> ret;
	// check horizontally
	for(int i=0;i!=size_;++i)
		for(int j=0;j!=size_;++j) {
			if(tab[i][j] == 0)
				continue;

			int current = tab[i][j];
			int k;
			for(k=j+1;k!=size_;++k)
				if(tab[i][k] != current)
					break;
			if(k-j >=3) {
				// add them to list
				for(int l = j;l<=k-1;++l) {
					ret.push_back(JewelPos(i,l));
					eliminated[i][l] = true;
				}
				j = k-1;
			}
		}

	// check vertically
	for(int j=0;j!=size_;++j)
		for(int i=0;i!=size_;++i) {
			if(tab[i][j] == 0)
				continue;

			int current = tab[i][j];
			int k;
			for(k=i;k!=size_;++k)
				if(tab[k][j] != current)
					break;
			if(k-i >=3) {
				// add them to list
				for(int l = i;l<=k-1;++l)
					// Fix duplicate introduced by checking horizontally
					if(!eliminated[l][j])
						ret.push_back(JewelPos(l,j));
				i = k-1;
			}
		}
	return ret;
}

list<pair<JewelPos,JewelPos>> Board::Fall(Board::IntTab& tab)
{
	list<pair<JewelPos,JewelPos>> ret;
	for(int j=0;j!=size_;++j) {
		int count = 0;
		for(int i=size_-1;i>=0;--i) {
			if(tab[i][j] == 0) {
				++count;
				continue;
			}
			if(count > 0) {
				ret.push_back(pair<JewelPos,JewelPos>(JewelPos(i,j),JewelPos(i+count,j)));
				tab[i+count][j] = tab[i][j];
				tab[i][j] = 0;
			}
		}
	}
	return ret;
}


BoardEvent::BoardEvent(const BoardEvent::EventType etype):
	type(etype)
{
}
