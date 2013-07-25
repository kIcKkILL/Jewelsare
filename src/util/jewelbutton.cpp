#include "jewelbutton.h"
#include <QPainter>

JewelButton::JewelButton(QWidget *parent) :
	QPushButton(parent)
{
	setMaximumHeight(50);
}

void JewelButton::paintEvent(QPaintEvent* event)
{
	QPushButton::paintEvent(event);
	// simple implementation
	if(isEnabled())
		setIcon(QIcon(QPixmap("./res/green.png")));
	else
		setIcon(QIcon(QPixmap("./res/red.png")));
}
