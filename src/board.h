#ifndef BOARD_H
#define BOARD_H
#include <QWidget>

class QMouseEvent;
class QPaintEvent;

namespace Jewelsare {

class Jewel;

class Board : public QWidget
{
	Q_OBJECT
friend class GameLogic;
static const int kSmallSize = 8;
static const int kMediumSize = 10;
static const int kLargeSize = 12;

public:
	enum Size { SMALL = kSmallSize, MEDIUM = kMediumSize, LARGE = kLargeSize };

	explicit Board(Size , QWidget *parent = 0);
protected:
	void paintEvent(QPaintEvent *);

signals:
	void RequireGeneration(Board&);

private:
	Size size_;
	Jewel *board_[kLargeSize][kLargeSize];
};

}
#endif // BOARD_H
