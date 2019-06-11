#pragma once
#include "NavMesh.h"
#include "Application.h"
#include "Renderer2D.h"
#include "Thief.h"
#include "KeyboardBehaviour.h"
#include "Shadow.h"

#include "Selector.h"
#include "Sequence.h"
#include "StillCondition.h"
#include "SwapVelocityAction.h"
#include "CanSeeTargetCondition.h"
#include "RemainingPathCondition.h"
#include "SeekAction.h"
#include "RecentlyChasedCondition.h"
#include "TimerDecorator.h"
#include "PatrolAction.h"
#include "ReturnAction.h"
#include "ClearPathAction.h"
#include "VeryCloseToTargetCondition.h"
#include "TimeoutDecorator.h"
#include "CloseToTargetCondition.h"
#include "PathAction.h"
#include "WanderAction.h"
#include "AttackAction.h"

class ThiefApp : public aie::Application {
public:

	ThiefApp();
	virtual ~ThiefApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

protected:

	aie::Renderer2D*	m_2dRenderer;
	aie::Font*			m_font;

	NavMesh*			m_navMesh;

	bool m_gameWin;
	bool m_gameLose;
	bool m_gameStart;

	// the object controlled by the character
	Thief* m_thief;
	// moves the thief based on input
	KeyboardBehaviour* m_thiefBehaviour;
	// the shadow of the thief
	Shadow* m_shadow;
	// the object controlledfby the AI
	std::vector<GameObject*> m_guard;
	// the object being guarded
	std::vector<Shadow*> m_treasure;

	// the floor background
	aie::Texture* m_ground;
	// the obstacles
	aie::Texture* m_crates;
	// an exit sign
	aie::Texture* m_sign;
	// the location of the exit
	AABB2* m_exit;

	// a container of AABBs that equal the obstacles made by the nav mesh
	std::vector<AABB2> m_obstacles;

	// allows for multiples of the same behaviour tree
	struct BehaviourTree
	{
		/* first layer */
		// decides if it wants to focus on the thief or the item
		Selector* m_thiefOrItem;
		/* second layer */
		// decides if the object needs to swap its velocity
		Sequence* m_stillTooLong;
		// decides if it should take action on the thief
		Sequence* m_interactWithThief;
		// decides to seek towards the last place the thief was seen
		Sequence* m_lastSeen;
		// decides to wander around in a spot or patrol the item
		Selector* m_wanderOrPatrol;
		/* third layer */
		// checks if the object has been still for too long
		StillCondition* m_still;
		// inverts the object's velocity
		SwapVelocityAction* m_swap;
		// checks if it can see the target
		CanSeeTargetCondition* m_canSee;
		// decides to attack, seek or arrive towards the thief
		Selector* m_attackOrSeek;
		// checks if the object still has a path to travel
		RemainingPathCondition* m_remaining;
		// follows the path despite being unable to see the thief
		SeekAction* m_seekRemaining;
		// decides to wander on the spot
		Sequence* m_wanderOnSpot;
		// decides to patrol the item
		Sequence* m_treasureClose;
		// decides to return to the treasure
		Sequence* m_returnToTreasure;
		/* fourth layer */
		// decides to attack the thief
		Sequence* m_thiefVeryClose;
		// decides to seek towards the thief
		Sequence* m_thiefClose;
		// checks if the target was recently chased
		RecentlyChasedCondition* m_recentlyChased;
		// runs the child behaviour until the timer is up
		TimerDecorator* m_timer;
		// checks if the treasure is close
		CloseToTargetCondition* m_closeTreasure;
		// patrols the treasure
		PatrolAction* m_patrol;
		// determines the path to the treasure
		ReturnAction* m_pathTreasure;
		// follows the path to th treasure
		SeekAction* m_seekTreasure;
		// clears the object's path
		ClearPathAction* m_clear;
		/* fifth layer */
		// checks if the target is very close
		VeryCloseToTargetCondition* m_veryClose;
		// waits an amount of time before running the child behaviour
		TimeoutDecorator* m_timeout;
		// checks if the target is close
		CloseToTargetCondition* m_close;
		// determines the path to the thief
		PathAction* m_path;
		// follows the path
		SeekAction* m_seek;
		// makes the guard wander on the spot
		WanderAction* m_wander;
		/* sixth layer */
		// attacks the thief
		AttackAction* m_attack;
	};

	BehaviourTree m_bt[3];
};