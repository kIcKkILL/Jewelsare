#include <QPropertyAnimation>
#include <QTimer>
#include <QMessageBox>
#include <QGridLayout>
#include <QPixmap>
#include <QRadioButton>
#include <QButtonGroup>
#include <QLabel>
#include <QFrame>
#include "util/jewelbutton.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gamestate.h"

using namespace Jewelsare;
using namespace std;

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow),
	ui_drawing_(false),
	animation_drawing_(false),
	hint_pos_(0,0)
{
	ui->setupUi(this);
	setWindowIcon(QIcon(QPixmap("./res/green.png")));

	game_state_ = new GameState();
	connect(game_state_,SIGNAL(GameEnd(bool)),this,SLOT(GameEnd_(bool)));

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

	current_frame_ = new QFrame(this);
	setCentralWidget(current_frame_);
	QGridLayout* layout = new QGridLayout(current_frame_);
	JewelButton *start_button,*score_button;
	start_button = new JewelButton(current_frame_);
	score_button = new JewelButton(current_frame_);
	QLabel *banner = new QLabel(current_frame_);
	QFont banner_font;
	banner_font.setPointSize(20);
	banner->setFont(banner_font);
	banner->setText(tr("Welcome to Jewelsare! Enjoy eliminating jewels!"));
	start_button->setText(tr("START GAME"));
	score_button->setText(tr("SCORE BOARD"));
	layout->addWidget(start_button,1,0);
	layout->addWidget(score_button,2,0);
	layout->addWidget(banner,0,0);
	current_frame_->show();
	QObject::connect(start_button,SIGNAL(clicked()),this,SLOT(StartClicked()));
	QObject::connect(score_button,SIGNAL(clicked()),this,SLOT(ScoreClicked()));
}

void MainWindow::HintProcessor_(JewelPos pos)
{
	hint_pos_ = pos;
}

void MainWindow::ShowHint_()
{
	JewelWidget *widget = map_[hint_pos_.x][hint_pos_.y].second;
	int ox=widget->x(), oy = widget->y();

	// the animation
	QPropertyAnimation *animation = new QPropertyAnimation(widget,"geometry");
	animation->setDuration(100);
	// start from a bigger JewelWidget
	animation->setStartValue((QRect(ox-kJewelWidgetSize/2,oy-kJewelWidgetSize/2,kJewelWidgetSize*2,kJewelWidgetSize*2)));
	// resize to normal size
	animation->setEndValue((QRect(ox,oy,kJewelWidgetSize,kJewelWidgetSize)));
	animation_drawing_ = true;
	connect(animation,&QPropertyAnimation::finished,[=](){
		animation_drawing_ = false;
	});
	animation->start();

	while(animation_drawing_)
		QCoreApplication::processEvents(QEventLoop::AllEvents);
}

void MainWindow::StartClicked()
{
	StartSelect_();
}

void MainWindow::ScoreClicked()
{
	// font setup
	QFont larger_font,smaller_font;
	larger_font.setPointSize(18);
	smaller_font.setPointSize(15);
	if(current_frame_)
		delete current_frame_;

	// set up new frame
	current_frame_ = new QFrame(this);
	setCentralWidget(current_frame_);
	QGridLayout *layout = new QGridLayout(current_frame_);
	QLabel *label1 = new QLabel(tr("Time Limited Mode"),current_frame_);
	label1->setFont(larger_font);
	QLabel *label2 = new QLabel(tr("Fast Reaction Mode"),current_frame_);
	label2->setFont(larger_font);
	layout->addWidget(label1,0,0);
	layout->addWidget(label2,0,1);
	QLabel *tl_display[HighScoresStorage::kMaxRecord];
	QLabel *fr_display[HighScoresStorage::kMaxRecord];
	for(int i=0;i!=HighScoresStorage::kMaxRecord;++i) {
		// read from GameState
		tl_display[i] = new QLabel(QString::number(game_state_->GetScore(Mode::TIME_LIMIT,i)),current_frame_);
		tl_display[i]->setFont(smaller_font);
		fr_display[i] = new QLabel(QString::number(game_state_->GetScore(Mode::FAST_REACTION,i)),current_frame_);
		fr_display[i]->setFont(smaller_font);
		layout->addWidget(tl_display[i],i+1,0);
		layout->addWidget(fr_display[i],i+1,1);
	}

	JewelButton *ret_button = new JewelButton(current_frame_);
	ret_button->setText(tr("Return"));
	layout->addWidget(ret_button,HighScoresStorage::kMaxRecord+1,1);
	connect(ret_button,SIGNAL(clicked()),this,SLOT(StartHome_()));
}

void MainWindow::StartSelect_()
{
	if(current_frame_)
		delete current_frame_;

	// set up new frame
	current_frame_ = new QFrame(this);
	setCentralWidget(current_frame_);
	QGridLayout *layout = new QGridLayout(current_frame_);

	JewelButton *go_button = new JewelButton(current_frame_);
	go_button->setText(tr("GO"));
	layout->addWidget(go_button,2,2);
	connect(go_button,SIGNAL(clicked()),this,SLOT(GoClicked()));

	QButtonGroup *mode_group = new QButtonGroup(current_frame_);
	QButtonGroup *difficulty_group = new QButtonGroup(current_frame_);
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
	if(mode_group_->checkedId() == 1) {
		game_state_->SetMode(Mode::FAST_REACTION);
		hint_ = true;
	}
	else {
		game_state_->SetMode(Mode::TIME_LIMIT);
		hint_ = false;
	}

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

void MainWindow::AbortClicked()
{
	game_state_->Abort();
	// Set up initial frame
	StartHome_();
}

void MainWindow::PauseClicked()
{
	if(game_state_->state() == GameState::PAUSE) {
		pause_button_->setText(tr("Pause"));
		game_state_->Resume();
	}
	else {
		pause_button_->setText(tr("Resume"));
		game_state_->Pause();
	}
}

void MainWindow::UpdateTimeDisplay(int remain)
{
	time_display_->setText(QString::number(remain));
	update();
}

void MainWindow::OnSwap(Jewelsare::SwapDirection direction)
{
	if(ui_drawing_ || game_state_->state()!=GameState::INGAME)
		return;

	game_state_->Pause();
	pause_button_->setEnabled(false);
	JewelWidget *sender = (JewelWidget*)this->sender();
	int x = sender->geometry().y()/50;
	int y = sender->geometry().x()/50;
	JewelPos pos(x,y);

	ui_drawing_ = true;
	//swap first
	if(!SwapJewelInMap_(x,y,direction))
		return;

	auto events = game_state_->Swap(pos,direction);
	bool swaped = false;
	for(BoardEvent event : events) {
		swaped = true;
		DrawBoardEvent_(event);
	}
	if(!swaped) {
		SwapJewelInMap_(x,y,direction);
		update();
	}

	if(hint_)
		ShowHint_();

	game_state_->Resume();
	pause_button_->setEnabled(true);
	ui_drawing_ = false;
}

void MainWindow::GameEnd_(bool high_score)
{
	time_display_->setText(QString::number(0));
	if(high_score) {
		QMessageBox info(this);
		info.setWindowTitle(tr("Congratulations!"));
		info.setText(tr("You have achieved a new high score!"));
		info.exec();
	}
	else {
		QMessageBox info(this);
		info.setWindowTitle(tr("Ooops!"));
		info.setText(tr("You didn't' do well this time."));
		info.exec();
	}
	pause_button_->setEnabled(false);
}

void MainWindow::DrawBoardEvent_(BoardEvent event)
{
	switch (event.type) {
	case BoardEvent::EventType::NEW: {
		for(JewelInfo info : event.GetNewPos()) {
			JewelWidget *widget = map_[info.first.x][info.first.y].second;
			map_[info.first.x][info.first.y].first = static_cast<Jewelsare::Color>(info.second);
			map_[info.first.x][info.first.y].second -> SetColor(static_cast<Jewelsare::Color>(info.second));
			QPropertyAnimation *animation = new QPropertyAnimation(widget,"geometry");
			animation->setDuration(200); // smaller than wait time
			animation->setStartValue(QRect(widget->x(),widget->y(),1,1));
			animation->setEndValue(QRect(widget->geometry())); // normal size
			animation->start();
			connect(animation,&QPropertyAnimation::finished,[=](){
				delete dynamic_cast<QPropertyAnimation*>(sender());
			});
		}
		break;
		// wait
		animation_drawing_ = true;
		QTimer timer;
		timer.setInterval(300);
		timer.setSingleShot(true);
		timer.start();
		connect(&timer,&QTimer::timeout,[=](){
			animation_drawing_ = false;
		});
		while(animation_drawing_)
			QCoreApplication::processEvents(QEventLoop::AllEvents);
	}
	case BoardEvent::EventType::DIE: {
		for(JewelPos pos :event.GetDiePos()) {
			map_[pos.x][pos.y].second->SetColor(Color::NONE);
			map_[pos.x][pos.y].first = Color::NONE;
		}

		// wait
		animation_drawing_ = true;
		QTimer timer;
		timer.setInterval(600);
		timer.setSingleShot(true);
		timer.start();
		connect(&timer,&QTimer::timeout,[=](){
			animation_drawing_ = false;
		});
		while(animation_drawing_)
			QCoreApplication::processEvents(QEventLoop::AllEvents);

		break;
	}
	case BoardEvent::EventType::FALL: {
		for(pair<JewelPos,JewelPos> fall_pos : event.GetFallPos()) {
			map_[fall_pos.second.x][fall_pos.second.y].first =
					(map_[fall_pos.first.x][fall_pos.first.y].first);
			map_[fall_pos.second.x][fall_pos.second.y].second->SetColor(map_[fall_pos.first.x][fall_pos.first.y].second->GetColor());
			map_[fall_pos.first.x][fall_pos.first.y].first = static_cast<Jewelsare::Color>(0);
			map_[fall_pos.first.x][fall_pos.first.y].second->SetColor(Color::NONE);
		}
		// wait
		animation_drawing_ = true;
		QTimer timer;
		timer.setInterval(300);
		timer.setSingleShot(true);
		timer.start();
		connect(&timer,&QTimer::timeout,[=](){
			animation_drawing_ = false;
		});
		while(animation_drawing_)
			QCoreApplication::processEvents(QEventLoop::AllEvents);
		break;
	}
	default:
		break;
	}
	update();
}

void MainWindow::StartGame_()
{
	// Set new UI frame
	delete current_frame_;

	current_frame_ = new QFrame(this);
	setCentralWidget(current_frame_);
	QFrame *right_frame = new QFrame(current_frame_);
	QGridLayout *layout = new QGridLayout(current_frame_);
	QGridLayout *right_layout = new QGridLayout(right_frame);

	QLabel *board = new QLabel(current_frame_);
	board->setPixmap(QPixmap("./res/bg.png"));
	board->setMinimumHeight(kJewelWidgetSize*(board_size_));
	board->setMinimumWidth(kJewelWidgetSize*(board_size_));
	board->setMaximumHeight(kJewelWidgetSize*(board_size_));
	board->setMaximumWidth(kJewelWidgetSize*(board_size_));

	// set up appropriate fonts and colors
	QFont big_label_font,smaller_label_font;
	big_label_font.setPointSize(16);
	smaller_label_font.setPointSize(14);
	QPalette blue_pa,red_pa;
	blue_pa.setColor(QPalette::WindowText,Qt::blue);
	red_pa.setColor(QPalette::WindowText,Qt::red);


	QLabel *label1 = new QLabel(tr("Score"),right_frame);
	label1->setFont(big_label_font);
	score_display_ = new QLabel(right_frame);
	score_display_->setFont(smaller_label_font);
	score_display_->setPalette(blue_pa);

	QLabel *label3 = new QLabel(tr("Time Left"),right_frame);
	label3->setFont(big_label_font);
	time_display_ =  new QLabel(right_frame);
	time_display_->setFont(smaller_label_font);
	time_display_->setPalette(red_pa);

	JewelButton *abort_button = new JewelButton(right_frame);
	abort_button->setText(tr("Abort"));
	connect(abort_button,SIGNAL(clicked()),this,SLOT(AbortClicked()));

	pause_button_ = new JewelButton(right_frame);
	pause_button_->setText(tr("Pause"));
	connect(pause_button_,SIGNAL(clicked()),this,SLOT(PauseClicked()));

	right_layout->addWidget(label1,0,0);
	right_layout->addWidget(score_display_,1,0);
	right_layout->addWidget(label3,2,0);
	right_layout->addWidget(time_display_,3,0);
	right_layout->addWidget(pause_button_,4,0);
	right_layout->addWidget(abort_button,5,0);

	layout->addWidget(board,0,0);
	layout->addWidget(right_frame,0,1);

	for(int i=0;i!=board_size_;++i)
		for(int j=0;j!=board_size_;++j) {
			map_[i][j].second = new JewelWidget(Color::NONE,board);
			// [i][j] <-> [y][x]
			map_[i][j].second->setGeometry(kJewelWidgetSize*j,kJewelWidgetSize*i,kJewelWidgetSize,kJewelWidgetSize);
			connect(map_[i][j].second,SIGNAL(Swap(Jewelsare::SwapDirection)),this,SLOT(OnSwap(Jewelsare::SwapDirection)));
		}
	current_frame_->show();

	connect(game_state_,SIGNAL(Hint(Jewelsare::JewelPos)),this,SLOT(HintProcessor_(Jewelsare::JewelPos)));
	DrawBoardEvent_(game_state_->StartNewGame());
	if(hint_)
		ShowHint_();
	connect(game_state_,SIGNAL(TimeTick(int)),this,SLOT(UpdateTimeDisplay(int)));
	connect(game_state_,SIGNAL(ScoreUpdated(int)),this,SLOT(UpdateScore_(int)));
}

void MainWindow::UpdateScore_(int new_score)
{
	score_display_->setText(QString::number(new_score));
	update();
}

bool MainWindow::SwapJewelInMap_(int x, int y, SwapDirection direction)
{
	// TODO animate it
	switch (direction) {
	case SwapDirection::DOWN: {
		if(x == board_size_-1)
			return false;
		const pair<Jewelsare::Color,JewelWidget*> temp = map_[x][y];
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
		const pair<Jewelsare::Color,JewelWidget*> temp = map_[x][y];
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
		const pair<Jewelsare::Color,JewelWidget*> temp = map_[x][y];
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
		const pair<Jewelsare::Color,JewelWidget*> temp = map_[x][y];
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
	update();
	return true;
}
