#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Jewelsare {
	class GameState;
	class Game;
}

namespace Ui {
class MainWindow;
}

class QFrame;

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
	void StartClicked();
	void ScoreClicked();

    
private:
	void StartHome_();
	void StartSelect_();
	QFrame *current_frame_;
    Ui::MainWindow *ui;
	Jewelsare::GameState *game_state_;
	Jewelsare::Game *game_;
};

#endif // MAINWINDOW_H
