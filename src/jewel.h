#ifndef JEWEL_H
#define JEWEL_H

#include <QWidget>

class Jewel : public QWidget
{
	Q_OBJECT
public:
	explicit Jewel(QWidget *parent = 0);

protected:
	void paintEvent(QPaintEvent *);

signals:
	
public slots:
	
};

#endif // JEWEL_H
