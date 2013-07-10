#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include <QObject>

namespace Jewelsare {

class Board;

class GameLogic : public QObject
{
	Q_OBJECT
public:
	explicit GameLogic(QObject *parent = 0);

signals:

public slots:
	void GenerateBoard(Jewelsare::Board &);
	
};

}
#endif // GAMELOGIC_H
