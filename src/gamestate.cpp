#include <algorithm>
#include <fstream>
#include "gamestate.h"
#include "scoresystem.h"
#include "game.h"


using namespace Jewelsare;
using namespace std;

GameState::GameState(QObject *parent) :
	QObject(parent),
	state_(ENDED)
{
	settings_ = new GameSettings;
}

void GameState::GameEndProcessor_(int score)
{
	delete game_;
	game_ = nullptr;
	state_ = ENDED;
	if(highscores_.NewScore(settings_->mode,score))
		emit(GameEnd(true)); // high score
	else
		emit(GameEnd(false));
}
GameState::State GameState::state() const
{
	return state_;
}

void GameState::SetDifficulty(Difficulty diff)
{
	settings_->difficulty = diff;
}

void GameState::SetMode(Mode mode)
{
	settings_->mode = mode;
}

GameState::~GameState() {

}

BoardEvent GameState::StartNewGame()
{
	game_ = new Game(*settings_);
	connect(game_,SIGNAL(TimeTick(int)),this,SIGNAL(TimeTick(int)));
	connect(game_,SIGNAL(ScoreUpdated(int)),this,SIGNAL(ScoreUpdated(int)));
	connect(game_,SIGNAL(GameEnd(int)),this,SLOT(GameEndProcessor_(int)));
	connect(game_,SIGNAL(Hint(Jewelsare::JewelPos)),this,SIGNAL(Hint(Jewelsare::JewelPos)));

	state_ = INGAME;
	return game_->NewGame();
}

void GameState::Pause()
{
	game_->Pause();
	state_ = PAUSE;
}

void GameState::Resume()
{
	game_->Resume();
	state_ = INGAME;
}

void GameState::Abort()
{
	delete game_;
	game_ = nullptr;
	state_ = ENDED;
}

std::list<BoardEvent> GameState::Swap(JewelPos pos,Jewelsare::SwapDirection direction)
{
	return game_->Swap(pos,direction);
}


HighScoresStorage::HighScoresStorage() :
	tl_scores_(kMaxRecord,0),
	fr_scores_(kMaxRecord,0)
{
	fstream file("hs.dat",ios::in | ios::binary);
	if(file) {
		for(int i=0;i!=kMaxRecord;++i)
			file.read((char*)&(tl_scores_[i]),sizeof(int));
		for(int i=0;i!=kMaxRecord;++i)
			file.read((char*)&(fr_scores_[i]),sizeof(int));
	}
	file.close();
}

bool HighScoresStorage::NewScore(Mode mode,int new_score)
{
	bool ret = false;
	// Determine mode
	vector<int> *target = mode==Mode::TIME_LIMIT? &tl_scores_:&fr_scores_;
	for(int score: *target)
		if(score < new_score) {
			ret = true;
			break;
		}

	if(ret) {
		target->push_back(new_score);
		sort(target->begin(),target->end(),[=](int a,int b){
			return a>=b;
		});
		target->pop_back();

	}
	WriteToFile(); // only happen here
	return ret;
}

int HighScoresStorage::GetScore(Mode mode, int rank)
{
	if(mode == Mode::TIME_LIMIT)
		return tl_scores_[rank];
	else
		return fr_scores_[rank];
}

void HighScoresStorage::WriteToFile()
{
	fstream file("hs.dat",ios::out | ios::binary);
	if(file) {
		for(int i=0;i!=kMaxRecord;++i)
			file.write((char*)&(tl_scores_[i]),sizeof(int));
		for(int i=0;i!=kMaxRecord;++i)
			file.write((char*)&(fr_scores_[i]),sizeof(int));
	}
	file.close();
}
