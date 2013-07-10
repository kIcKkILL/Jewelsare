#ifndef JEWEL_H
#define JEWEL_H

#include <QWidget>

class Jewel : public QWidget
{
	Q_OBJECT
public:
	enum Color { NONE = 0, RED, ORANGE, YELLOW, GREEN, BLUE };
	enum class SwapDirection { UP, RIGHT, DOWN, LEFT };
	explicit Jewel(Color,QWidget *parent = 0);
	Color GetColor() { return color_; }

protected:
	void paintEvent(QPaintEvent *);

signals:
	void Swap(SwapDirection);
	
public slots:
	void OnDrag(); //TODO add appropriate parameter
	
private:
	Color color_;
};

#endif // JEWEL_H
