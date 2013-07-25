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
class QLabel;
class QPushButton;

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
	void AbortClicked();
	void PauseClicked();
	void UpdateScore_(int new_score);
	void UpdateTimeDisplay(int);
	void OnSwap(Jewelsare::SwapDirection);
	void GameEnd_(bool high_score);
	void StartHome_();
	void HintProcessor_(Jewelsare::JewelPos pos);

private:
	void ShowHint_();
	bool ui_drawing_; // swap lock
	bool animation_drawing_; // internal drawing lock

	static const int kJewelWidgetSize = 50;
	// Three StartXXX functions affects only GUI
	void StartSelect_();
	void StartGame_();
	void DrawBoardEvent_(Jewelsare::BoardEvent);
	bool SwapJewelInMap_(int x,int y,Jewelsare::SwapDirection);

	QFrame *current_frame_;
	QButtonGroup *mode_group_;
	QButtonGroup *difficulty_group_;
	QLabel *score_display_;
	QLabel *time_display_;
	QPushButton *pause_button_;
    Ui::MainWindow *ui;

	Jewelsare::GameState *game_state_;
	std::pair<Jewelsare::Color,JewelWidget*> map_[Jewelsare::Board::kLargeSize][Jewelsare::Board::kLargeSize];
	int board_size_;
	bool hint_; // whether to show hint
	Jewelsare::JewelPos hint_pos_;
};

#endif // MAINWINDOW_H
