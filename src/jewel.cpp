#include <QPainter>
#include "jewel.h"

Jewel::Jewel(Color color, QWidget *parent) :
	QWidget(parent),
	color_(color)
{
	//TODO connect SIGNAL and SLOT

}

void Jewel::paintEvent(QPaintEvent *event)
{
	//TODO paint pixmap according to color
}
