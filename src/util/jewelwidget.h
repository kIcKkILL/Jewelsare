#ifndef JEWEL_H
#define JEWEL_H

#include <QWidget>
#include <QPointF>
#include <QColor>

namespace Jewelsare {
	//enum class Color { NONE = 0, RED = Qt::red, CYAN = Qt::cyan, YELLOW = Qt::yellow, GREEN = Qt::green, BLUE = Qt::blue };
}

class JewelWidget : public QWidget
{
	Q_OBJECT
public:
	enum class SwapDirection { UP, RIGHT, DOWN, LEFT };
	explicit JewelWidget(QColor,QWidget *parent = 0);
	QColor GetColor() const { return color_; }

protected:
	void paintEvent(QPaintEvent *);
	void mousePressEvent(QMouseEvent *);
	void mouseMoveEvent(QMouseEvent *);

signals:
	void Swap(SwapDirection);
	
public slots:
	
private:
	QColor color_;
	bool mouse_down_;
	QPointF mouse_down_pos_;
};

#endif // JEWEL_H
