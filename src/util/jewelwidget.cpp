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
	static const QPixmap redpix("./res/red.png");
	static const QPixmap orangepix("./res/orange.png");
	static const QPixmap yellowpix("./res/yellow.png");
	static const QPixmap greenpix("./res/green.png");
	static const QPixmap bluepix("./res/blue.png");
	static const QPixmap transpix("./res/trans.png");
	QPainter painter(this);
	QPixmap const *pixmap;
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
		const qreal ox = mouse_down_pos_.x();
		const qreal oy = mouse_down_pos_.y();
		const qreal dx = pos.x() - ox;
		const qreal dy = pos.y() - oy;
		static const double kMarginFactor = 1.15;
		if(abs(dx) > abs(dy)) {
			if(dx > 0 && ox+dx > (this->size().width()) *kMarginFactor)
				emit(Swap(Jewelsare::SwapDirection::RIGHT));
			else if (dx < 0 && ox+dx < -(this->size().width()*(kMarginFactor-1.0)))
				emit(Swap(Jewelsare::SwapDirection::LEFT));
			else
				return;
		}
		else {
			if(dy > 0 && oy+dy > (double)(this->size().height()) *kMarginFactor)
				emit(Swap(Jewelsare::SwapDirection::DOWN));
			else if (dy < 0 && oy+dy < -(this->size().width()*(kMarginFactor-1.0)))
				emit(Swap(Jewelsare::SwapDirection::UP));
			else
				return;
		}
		mouse_down_ = false;
	}
}

void JewelWidget::mouseReleaseEvent(QMouseEvent*)
{
	mouse_down_ = false;
}
