#include <QPainter>
#include <QMouseEvent>
#include "jewelwidget.h"

JewelWidget::JewelWidget(Jewelsare::Color color, QWidget *parent) :
	QWidget(parent),
	color_(color),
	mouse_down_(false)
{

}

void JewelWidget::paintEvent(QPaintEvent *event)
{
	static QPixmap redpix("./res/red.png");
	static QPixmap orangepix("./res/orange.png");
	static QPixmap yellowpix("./res/yellow.png");
	static QPixmap greenpix("./res/green.png");
	static QPixmap bluepix("./res/blue.png");
	static QPixmap transpix("./res/trans.png");
	QPainter painter(this);
	QPixmap *pixmap;
	//FIXME paint pixmap according to color
	switch (color_) {
	case Jewelsare::Color::RED:
		pixmap = &redpix;
		break;
	case Jewelsare::Color::ORANGE:
		pixmap = &orangepix;
		break;
	case Jewelsare::Color::YELLOW:
		pixmap = &yellowpix;
		break;
	case Jewelsare::Color::GREEN:
		pixmap = &greenpix;
		break;
	case Jewelsare::Color::BLUE:
		pixmap = &bluepix;
		break;
	default:
		pixmap = &transpix;
		break;
	}
	painter.drawPixmap(0,0,size().width(),size().height(),*pixmap);
}

void JewelWidget::mousePressEvent(QMouseEvent *event)
{
	mouse_down_ = true;
	mouse_down_pos_ = event->pos();
}

void JewelWidget::mouseMoveEvent(QMouseEvent *event)
{
	if(mouse_down_) {
		const QPointF pos = event->pos();
		// movement
		const qreal dx = pos.x() - mouse_down_pos_.x();
		const qreal dy = pos.y() - mouse_down_pos_.y();
		if(dx > dy) {
			if(dx <= 10)
				return;
			if(dx > 0)
				emit(Swap(Jewelsare::SwapDirection::RIGHT));
			else
				emit(Swap(Jewelsare::SwapDirection::LEFT));
		}
		else {
			if(dy <= 10)
				return;
			if(dy > 0)
				emit(Swap(Jewelsare::SwapDirection::DOWN));
			else
				emit(Swap(Jewelsare::SwapDirection::UP));
		}
		mouse_down_ = false;
	}
}
