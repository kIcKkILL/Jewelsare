#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
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
	void OnSwap(Jewelsare::JewelPos,JewelWidget::SwapDirection);
    
private:
	// Three StartXXX functions affects only GUI
	void StartHome_();
	void StartSelect_();
	void StartGame_();
	QFrame *current_frame_;
	QButtonGroup *mode_group_;
	QButtonGroup *difficulty_group_;
    Ui::MainWindow *ui;
	Jewelsare::GameState *game_state_;
};

#endif // MAINWINDOW_H
