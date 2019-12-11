// Engine includes.
#include "EventStep.h"
#include "LogManager.h"
#include "WorldManager.h"
#include "utility.h"
#include "EventCollision.h"
#include "EventPlayerHit.h"
#include "EventMonsterHit.h"

// Game includes.
#include "Monster.h"

Monster::Monster(Hero* p_hero) {

	// Basic Muonster attributes.
	m_move_countdown = MOVE_TIME_WANDER;
	m_think_countdown = THINK_TIME_WANDER;
	m_damage_countdown = TAKE_DAMAGE;
	setType("Monster");
	setAltitude(3);
	setSpeed(0);

	// Default sprite, standing.
	setSprite("monster-walk");
	stopAnimation(true);

	//dealing with damage 
	health = 3;
	currentSprite = 0;

	// Mummy keeps track of Hero.
	m_p_hero = p_hero;

	//states
	m_state_wander = StateWander();
	m_state_chase = StateChase();
	m_state_search = StateSearch();

	//set up state machine. Starts in "wonder" state. 
	m_machine = df::StateMachine();
	m_machine.setOwner(this);
	m_machine.setState(getStateWander());
	m_machine.changeState(getStateWander());

	// Get step events.
	registerInterest(df::STEP_EVENT);


	//Debugging
	LM.writeLog("Monster initialized");
}

// Start or stop animation.
void Monster::stopAnimation(bool stop) {
	df::Animation animation = getAnimation();
	if (stop) {
		if (animation.getSlowdownCount() != -1) {
			animation.setSlowdownCount(-1);
			animation.setIndex(0);
		}
	}
	else {
		if (animation.getSlowdownCount() == -1) {
			animation.setSlowdownCount(0);
			animation.setIndex(0);
		}
	}
	setAnimation(animation);
}

// Handle event.
// Return 0 if ignored, else 1
int Monster::eventHandler(const df::Event* e) {

	if (e->getType() == df::STEP_EVENT) {
		m_machine.Update(); //update state machine 
		return 1;
	}

	if (e->getType() == df::COLLISION_EVENT) {
		const df::EventCollision* p_collision_event = dynamic_cast <df::EventCollision const*> (e);
		hit(p_collision_event);
		return 1;
	}
	// If we get here, we have ignored this event.
	return 0;
}

// Return true if Hero is within sensing distance.
bool Monster::senseHero() {
	df::Vector hero_pos = getHero()->getPosition();
	float xChange = hero_pos.getX() - getPosition().getX();
	float yChange = hero_pos.getY() - getPosition().getY();
	yChange /= 4;
	float pythag = sqrt(pow(xChange, 2) + pow(yChange, 2));
	if (pythag < SENSE_DISTANCE){
		return true;
	}
	return false; // Can't sense.
}

// If can see Hero and can sense Hero, return direction
// else return (0,0).
df::Vector Monster::seeHero() {
	// Check if in range for sensing hero.
	if (senseHero()) {

		// Check if line from hero to mummy has wall.
		// if not, the chase begins, return normalized vector.

		df::Vector monster_pos = getPosition();
		df::Vector hero_pos = getHero()->getPosition();
		df::Vector v = hero_pos - monster_pos;
		float minX = 0;
		float minY = 0;
		if (monster_pos.getX() <= hero_pos.getX()) {
			minX = monster_pos.getX();
		}
		else {
			minX = hero_pos.getX();
		}
		if (monster_pos.getY() <= hero_pos.getY()) {
			minY = monster_pos.getY();
		}
		else {
			minY = hero_pos.getY();
		}
		df::Vector corner = df::Vector(minX, minY);
		float width = abs(monster_pos.getX() - hero_pos.getX());
		float height = abs(monster_pos.getY() - hero_pos.getY());
		//LM.writeLog("Making box with corner (%.1f, %.1f) width: %.1f height %.1f", corner.getX(), corner.getY(), width, height);
		df::Box b = df::Box(corner, width, height);

		// Get all of the walls to check collisions with.
		df::ObjectList walls = WM.objectsOfType("Wall");
		df::ObjectListIterator i = df::ObjectListIterator(&walls);
		bool blocked = false;
		while (!i.isDone()) {
			df::Object* curr = i.currentObject();
			df::Box box = df::getWorldBox(curr);
			// If there is a wall in our way, return vector (0,0).
			if (df::boxIntersectsBox(box, b)) {
				blocked = true;
			}
			i.next();
		}
		// No intersections, we can see!
		if (!blocked) {
			v.normalize();
			return v;
		}
	}
	return df::Vector(0, 0);  // Can't see.
}

void Monster::setMoveCountdown(int new_move_countdown) {
	m_move_countdown = new_move_countdown;
}

int Monster::getMoveCountdown() {
	return m_move_countdown;
}

void Monster::setThinkCountdown(int new_think_countdown) {
	m_think_countdown = new_think_countdown;
}

int Monster::getThinkCountdown() {
	return m_think_countdown;
}

Hero* Monster::getHero() {
	return m_p_hero;
}

StateWander *Monster::getStateWander() {
	return &m_state_wander;
}

df::StateMachine* Monster::getStateMachine() {
	return &m_machine;
}

StateChase *Monster::getStateChase() {
	return &m_state_chase;
}

StateSearch *Monster::getStateSearch() {
	return &m_state_search;
}

//called when monster collides 
void Monster::hit(const df::EventCollision* p_collision_event) {

	//if Monster on Monster ignore.
	if ((p_collision_event->getObject1()->getType() == "Monster") &&
		(p_collision_event->getObject2()->getType() == "Monster"))
		return;
	
	//if  hero, take away hunger 
	if (((p_collision_event->getObject1()->getType()) == "Hero") ||
		((p_collision_event->getObject2()->getType()) == "Hero")) {
		//create "hit player" event and send to interested objects 
		EventPlayerHit hitPlayer;
		WM.onEvent(&hitPlayer);
	}

	//if attack obj decrease health 
	if ((p_collision_event->getObject1()->getType()) == "AttackObj") {
		//decrease health 
		m_damage_countdown--;

		if (m_damage_countdown < 1) { //time to loose health
			health--;
			m_damage_countdown = TAKE_DAMAGE; //reset
			currentSprite++;
			//change sprite 
			switch (currentSprite) {
			case 1:
				setSprite("monster-hurt2");
				stopAnimation(false);
				break;
			case 2:
				setSprite("monster-hurt3");
				stopAnimation(false);
				break;
			case 3:
				setSprite("monster-hurt3");
				stopAnimation(false);
				break;
			default:
				//setSprite("monster-hurt3");
				break;
			}
		}

		//send event indicating that at least one monster was hit 
		EventMonsterHit monsterHit;
		WM.onEvent(&monsterHit);

		if (health < 1) { //monster is dead 
			WM.markForDelete(p_collision_event->getObject2()); //delete monster
		}
	}
	if ((p_collision_event->getObject2()->getType()) == "AttackObj") {
		
		//decrease health 
		m_damage_countdown--;

		if (m_damage_countdown < 1) { //time to loose health
			health--;
			m_damage_countdown = TAKE_DAMAGE; //reset
			currentSprite++;
			//change sprite 
			switch (currentSprite) {
			case 1:
				setSprite("monster-hurt2");
				stopAnimation(false);
				break;
			case 2:
				setSprite("monster-hurt3");
				stopAnimation(false);
				break;
			case 3:
				setSprite("monster-hurt3");
				stopAnimation(false);
				break;
			default:
				break;
			}
		}
		

		//send event indicating that at least one monster was hit 
		EventMonsterHit monsterHit;
		WM.onEvent(&monsterHit);
		

		if (health < 1) { //monster is dead 
			WM.markForDelete(p_collision_event->getObject1()); //delete monster
		}
	}
}