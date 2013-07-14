#include <QPainter>
#include "jewelwidget.h"
#include <QMouseEvent>

JewelWidget::JewelWidget(QColor color, QWidget *parent) :
	QWidget(parent),
	color_(color),
	mouse_down_(false)
{
	//TODO connect SIGNAL and SLOT (?)

}

void JewelWidget::paintEvent(QPaintEvent *event)
{
	//TODO paint pixmap according to color
	QPainter painter(this);
	painter.setBrush(QBrush(color_));
	painter.drawRect(0,0,50,50);
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
		const qreal dx = pos.x() - mouse_down_pos_.x();
		const qreal dy = pos.y() - mouse_down_pos_.y();
		//TODO
		mouse_down_ = false;
	}
}
