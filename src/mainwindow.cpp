#include <QGridLayout>
#include <QLabel>
#include <QFrame>
#include "util/jewelbutton.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "game.h"
#include "gamestate.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	current_frame_ = 0;
	StartHome_();
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::StartHome_()
{
	if(current_frame_)
		delete current_frame_;

	current_frame_ = new QFrame(ui->centralWidget);
	QGridLayout* layout = new QGridLayout(current_frame_);

	JewelButton *start_button,*score_button;
	start_button = new JewelButton(current_frame_);
	score_button = new JewelButton(current_frame_);
	QLabel *banner = new QLabel(current_frame_);
	banner->setText(tr("Jewelsare"));
	start_button->setText(tr("START GAME"));
	score_button->setText(tr("SCORE BOARD"));
	layout->addWidget(start_button,1,0);
	layout->addWidget(score_button,2,0);
	layout->addWidget(banner,0,0);
	QObject::connect(start_button,SIGNAL(clicked()),this,SLOT(StartClicked()));
	QObject::connect(score_button,SIGNAL(clicked()),this,SLOT(ScoreClicked()));
}

void MainWindow::StartClicked()
{

}

void MainWindow::ScoreClicked()
{

}

void MainWindow::StartSelect_()
{
	if(current_frame_)
		delete current_frame_;

	//TODO add mode and difficulty select, also a "GO" and "HOME" button
}
