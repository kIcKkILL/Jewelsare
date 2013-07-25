#include <QPainter>
#include <ctime>
#include <cstdlib>
#include "jewelbutton.h"

JewelButton::JewelButton(QWidget *parent) :
	QPushButton(parent)
{
	setMaximumHeight(50);
}

void JewelButton::paintEvent(QPaintEvent* event)
{
	static const QIcon red (QPixmap("./res/red.png"));
	static const QIcon yellow (QPixmap("./res/yellow.png"));
	static const QIcon orange (QPixmap("./res/orange.png"));
	static const QIcon green (QPixmap("./res/green.png"));
	static const QIcon blue (QPixmap("./res/blue.png"));
	QPushButton::paintEvent(event);
	// simple implementation by randomizing icon
	srand(time(NULL));
	switch (rand()%5) {
	case 0:
		setIcon(red);
		break;
	case 1:
		setIcon(yellow);
		break;
	case 2:
		setIcon(orange);
		break;
	case 3:
		setIcon(green);
		break;
	case 4:
		setIcon(blue);
		break;
	}
}
