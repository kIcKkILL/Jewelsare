#include <QGridLayout>
#include <QColor>
#include <QPixmap>
#include <QRadioButton>
#include <QButtonGroup>
#include <QLabel>
#include <QFrame>
#include "util/jewelbutton.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gamestate.h"

#include <cassert>

using namespace Jewelsare;
using namespace std;

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	game_state_ = new GameState();

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
	current_frame_->show();
	QObject::connect(start_button,SIGNAL(clicked()),this,SLOT(StartClicked()));
	QObject::connect(score_button,SIGNAL(clicked()),this,SLOT(ScoreClicked()));
}

void MainWindow::StartClicked()
{
	StartSelect_();
}

void MainWindow::ScoreClicked()
{

}

void MainWindow::StartSelect_()
{
	if(current_frame_)
		delete current_frame_;

	current_frame_ = new QFrame(ui->centralWidget);
	QGridLayout* layout = new QGridLayout(current_frame_);

	JewelButton *go_button = new JewelButton(current_frame_);
	go_button->setText(tr("GO"));
	layout->addWidget(go_button,2,0);
	connect(go_button,SIGNAL(clicked()),this,SLOT(GoClicked()));

	QButtonGroup *mode_group = new QButtonGroup(current_frame_);
	QButtonGroup *difficulty_group = new QButtonGroup(current_frame_);
	//TODO add mode and difficulty select, also a "HOME" button
	QRadioButton *time_radio = new QRadioButton("Time Limited Mode",current_frame_);
	QRadioButton *reaction_radio = new QRadioButton("Reaction Mode",current_frame_);
	QRadioButton *easy = new QRadioButton("EASY",current_frame_);
	QRadioButton *medium = new QRadioButton("MEDIUM",current_frame_);
	QRadioButton *hard = new QRadioButton("HARD",current_frame_);
	mode_group->addButton(time_radio,0);
	mode_group->addButton(reaction_radio,1);
	difficulty_group->addButton(easy,0);
	difficulty_group->addButton(medium,1);
	difficulty_group->addButton(hard,2);
	layout->addWidget(time_radio,0,0);
	layout->addWidget(reaction_radio,0,1);
	layout->addWidget(easy,1,0);
	layout->addWidget(medium,1,1);
	layout->addWidget(hard,1,2);

	//default
	easy->setChecked(true);
	time_radio->setChecked(true);

	mode_group_ = mode_group;
	difficulty_group_ = difficulty_group;
	current_frame_->show();
}

void MainWindow::GoClicked()
{
	if(mode_group_->checkedId() == 1)
		game_state_->SetMode(Mode::FAST_REACTION);
	else
		game_state_->SetMode(Mode::TIME_LIMIT);

	switch(difficulty_group_->checkedId()) {
	case 0:
		board_size_ = Board::kLargeSize;
		game_state_->SetDifficulty(Difficulty::EASY);
		break;
	case 1:
		board_size_ = Board::kMediumSize;
		game_state_->SetDifficulty(Difficulty::MEDIUM);
		break;
	case 2:
		board_size_ = Board::kSmallSize;
		game_state_->SetDifficulty(Difficulty::HARD);
		break;
	default:
		board_size_ = Board::kLargeSize;
		game_state_->SetDifficulty(Difficulty::EASY);
		break;
	}

	StartGame_();
}

void MainWindow::OnSwap(Jewelsare::SwapDirection direction)
{
	JewelWidget *sender = (JewelWidget*)this->sender();
	int x = sender->geometry().y()/50;
	int y = sender->geometry().x()/50;
	JewelPos pos(x,y);

	//swap first
	if(!SwapJewelInMap_(x,y,direction))
		return;
	update();

	auto events = game_state_->Swap(pos,direction);
	bool swaped = false;
	for(BoardEvent event : events) {
		swaped = true;
		DrawBoardEventent(event);
	}
	if(!swaped) {
		assert(SwapJewelInMap_(x,y,direction));
		update();
	}
}

void MainWindow::DrawBoardEventent(BoardEvent event)
{
	switch (event.type) {
	case BoardEvent::EventType::NEW:
		for(JewelInfo info : event.GetNewPos()) {
			map_[info.first.x][info.first.y].first = static_cast<Jewelsare::Color>(info.second);
			map_[info.first.x][info.first.y].second -> SetColor(static_cast<Jewelsare::Color>(info.second));
		}
		break;
	case BoardEvent::EventType::DIE:
		for(JewelPos pos :event.GetDiePos()) {
			map_[pos.x][pos.y].first = Color::NONE;
			map_[pos.x][pos.y].second -> SetColor(Color::NONE);
		}
		break;
	case BoardEvent::EventType::FALL:
		for(pair<JewelPos,JewelPos> fall_pos : event.GetFallPos()) {
			map_[fall_pos.second.x][fall_pos.second.y].first =
					(map_[fall_pos.first.x][fall_pos.first.y].first);
			map_[fall_pos.second.x][fall_pos.second.y].second->SetColor(map_[fall_pos.first.x][fall_pos.first.y].second->GetColor());
			map_[fall_pos.first.x][fall_pos.first.y].first = static_cast<Jewelsare::Color>(0);
			map_[fall_pos.first.x][fall_pos.first.y].second->SetColor(Color::NONE);
		}
		break;
	default:
		break;
	}
	update();
}

void MainWindow::StartGame_()
{
	//TODO Set new UI frame
	delete current_frame_;
	current_frame_ = new QFrame(ui->centralWidget);

	QLabel *board = new QLabel(current_frame_);
	//board->setPixmap(QPixmap("board.png"));
	board->setGeometry(0,0,size().width(),size().height());
	for(int i=0;i!=board_size_;++i)
		for(int j=0;j!=board_size_;++j) {
			map_[i][j].second = new JewelWidget(Color::NONE,board);
			// [i][j] <-> [y][x]
			map_[i][j].second->setGeometry(kJewelWidgetSize*j,kJewelWidgetSize*i,kJewelWidgetSize,kJewelWidgetSize);
			connect(map_[i][j].second,SIGNAL(Swap(Jewelsare::SwapDirection)),this,SLOT(OnSwap(Jewelsare::SwapDirection)));
		}
	current_frame_->show();
	DrawBoardEventent(game_state_->StartNewGame());
}

bool MainWindow::SwapJewelInMap_(int x, int y, SwapDirection direction)
{
	switch (direction) {
	case SwapDirection::DOWN: {
		if(x == board_size_-1)
			return false;
		const std::pair<Jewelsare::Color,JewelWidget*> temp = map_[x][y];
		map_[x][y] = map_[x+1][y];
		map_[x+1][y] = temp;
		const QRect geometry_temp = map_[x+1][y].second->geometry();
		map_[x+1][y].second->setGeometry(map_[x][y].second->geometry());
		map_[x][y].second->setGeometry(geometry_temp);
		break;
	}
	case SwapDirection::UP: {
		if(x == 0)
			return false;
		const std::pair<Jewelsare::Color,JewelWidget*> temp = map_[x][y];
		map_[x][y] = map_[x-1][y];
		map_[x-1][y] = temp;
		const QRect geometry_temp = map_[x-1][y].second->geometry();
		map_[x-1][y].second->setGeometry(map_[x][y].second->geometry());
		map_[x][y].second->setGeometry(geometry_temp);
		break;
	}
	case SwapDirection::LEFT: {
		if(y == 0)
			return false;
		const std::pair<Jewelsare::Color,JewelWidget*> temp = map_[x][y];
		map_[x][y] = map_[x][y-1];
		map_[x][y-1] = temp;
		const QRect geometry_temp = map_[x][y-1].second->geometry();
		map_[x][y-1].second->setGeometry(map_[x][y].second->geometry());
		map_[x][y].second->setGeometry(geometry_temp);
		break;
	}
	case SwapDirection::RIGHT: {
		if(y == board_size_-1)
			return false;
		const std::pair<Jewelsare::Color,JewelWidget*> temp = map_[x][y];
		map_[x][y] = map_[x][y+1];
		map_[x][y+1] = temp;
		const QRect geometry_temp = map_[x][y+1].second->geometry();
		map_[x][y+1].second->setGeometry(map_[x][y].second->geometry());
		map_[x][y].second->setGeometry(geometry_temp);
		break;
	}
	default:
		return false;
		break;
	}
	// No special case happened where swap outside the board
	return true;
}
