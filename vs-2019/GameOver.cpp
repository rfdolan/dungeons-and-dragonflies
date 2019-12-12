// engine
#include "EventStep.h"
#include "LogManager.h"
#include "ResourceManager.h"
#include "WorldManager.h"
#include "DisplayManager.h"

// game
#include "GameOver.h"
#include "GameStart.h"
#include "Map.h"

GameOver::GameOver(Map* m, Hero* hero) {

	m_map = m;
	m_p_hero = hero;

	//set type 
	setType("GameOver");
	setVisible(true);

	//set time to live
	time_to_live = 300; //length of game over song?

	// Register for step event.
	registerInterest(df::STEP_EVENT);
	//WM.setViewFollowing(this);

	// Play "game over" sound.
	//df::Sound* p_sound = RM.getSound("game over");
	//p_sound->play();
	

}

// When done, game over so reset things for GameStart.
GameOver::~GameOver() {
	LM.writeLog("Deleting game over object");
	WM.markForDelete(m_p_hero);

	new GameStart();
}

// Handle event.
// Return 0 if ignored, else 1.
int GameOver::eventHandler(const df::Event* p_e) {

	if (p_e->getType() == df::STEP_EVENT) {
		step();
		return 1;
	}

	// If get here, have ignored this event.
	return 0;
}

// Count down to end of message.
void GameOver::step() {
	LM.writeLog("Steppin in gameover");
	time_to_live--;
	LM.writeLog("Time to live is %d", time_to_live);
	if (time_to_live <= 0) {
		LM.writeLog("Game over is done living");
		WM.markForDelete(this);
	}
}


// Override default draw so as not to display "value".
int GameOver::draw() {
	DM.drawCh(getPosition(), 'x', df::WHITE);
	return 0;
}