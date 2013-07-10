#include <QPainter>
#include "board.h"
using namespace Jewelsare;

Board::Board(QWidget *parent,Size size)
	:QWidget(parent)
{
	size_ = size;
}

void Board::paintEvent(QPaintEvent *e)
{
	QPainter painter(this);
	painter.drawRect(20,20,40,40);
}
