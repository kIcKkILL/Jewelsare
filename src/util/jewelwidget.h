#ifndef JEWEL_H
#define JEWEL_H

#include <QWidget>
#include <QPointF>

namespace Jewelsare {
	enum Color { NONE = 0, RED = 1, ORANGE = 2, YELLOW = 3, GREEN = 4, BLUE = 5 };
	enum class SwapDirection { UP, RIGHT, DOWN, LEFT };
}

class JewelWidget : public QWidget
{
	Q_OBJECT
public:
	explicit JewelWidget(Jewelsare::Color,QWidget *parent = 0);
	Jewelsare::Color GetColor() const { return color_; }
	void SetColor(Jewelsare::Color c) { color_ = c;}

protected:
	void paintEvent(QPaintEvent *);
	void mousePressEvent(QMouseEvent *);
	void mouseMoveEvent(QMouseEvent *);
	void mouseReleaseEvent(QMouseEvent *);

signals:
	void Swap(Jewelsare::SwapDirection);
	
public slots:
	
private:
	Jewelsare::Color color_;
	bool mouse_down_;
	QPointF mouse_down_pos_;
};

#endif // JEWEL_H
