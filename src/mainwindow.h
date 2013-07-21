#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <utility>
#include "util/jewelwidget.h"
#include "board.h"

namespace Jewelsare {
	class GameState;
}

namespace Ui {
class MainWindow;
}

class QFrame;
class QButtonGroup;
class QColor;
class QGridLayout;

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
	void StartClicked();
	void ScoreClicked();
	void GoClicked();
	void OnSwap(Jewelsare::SwapDirection);
    
private:
	bool ui_drawing_; // lock
	bool animation_drawing_; // internal lock

	static const int kJewelWidgetSize = 50;
	// Three StartXXX functions affects only GUI
	void StartHome_();
	void StartSelect_();
	void StartGame_();
	void DrawBoardEventent(Jewelsare::BoardEvent);
	bool SwapJewelInMap_(int x,int y,Jewelsare::SwapDirection);
	QFrame *current_frame_;
	QButtonGroup *mode_group_;
	QButtonGroup *difficulty_group_;
    Ui::MainWindow *ui;
	Jewelsare::GameState *game_state_;
	std::pair<Jewelsare::Color,JewelWidget*> map_[Jewelsare::Board::kLargeSize][Jewelsare::Board::kLargeSize];
	int board_size_;
};

#endif // MAINWINDOW_H
