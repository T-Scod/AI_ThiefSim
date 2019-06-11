#include "ThiefApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include <time.h>
#include <iostream>
#include <imgui.h>

ThiefApp::ThiefApp() {

}

ThiefApp::~ThiefApp() {

}

bool ThiefApp::startup() {
	
	m_2dRenderer = new aie::Renderer2D();

	m_font = new aie::Font("../bin/font/consolas.ttf", 32);
	
	m_gameWin = false;
	m_gameLose = false;
	m_gameStart = false;

	m_ground = new aie::Texture("../bin/textures/ground.png");
	m_crates = new aie::Texture("../bin/textures/crate.png");
	m_sign = new aie::Texture("../bin/textures/exit.png");
	m_exit = new AABB2(0.0f, 340.0f, 20.0f, 380.0f);

	// sets the size of the nav mesh
	m_navMesh = new NavMesh(1280, 720);

	// seeds the random sequence based on the current time
	srand(time(nullptr));

	// 12 random obstacles
	for (int i = 0; i < 15; ++i)
	{
		// if safe is false then an overlap occured
		bool safe = false;
		// creates a random obstacle then checks if it has overlapped with any other obstacles
		do
		{
			safe = m_navMesh->addObstacle(rand() / float(RAND_MAX) * getWindowWidth() * 0.75f + getWindowWidth() * 0.125f,
				rand() / float(RAND_MAX) * getWindowHeight() * 0.75f + getWindowHeight() * 0.125f,
				60.0f, 60.0f,
				10.0f);
		} while (safe == false);
	}
	
	// transfers the obstacles into AABBs
	for (auto o : m_navMesh->getObstacles())
	{
		m_obstacles.push_back(AABB2(o.x, o.y, o.x + o.w, o.y + o.h));
	}
	// bottom border
	m_obstacles.push_back(AABB2(0.0f, 0.0f, 1280.0f, 10.0f));
	// top border
	m_obstacles.push_back(AABB2(0.0f, 710.0f, 1280.0f, 720.0f));
	// left border first half
	m_obstacles.push_back(AABB2(0.0f, 0.0f, 10.0f, 340.0f));
	// left border second half
	m_obstacles.push_back(AABB2(0.0f, 380.0f, 10.0f, 720.0f));
	// right border
	m_obstacles.push_back(AABB2(1270.0f, 0.0f, 1280.0f, 720.0f));
	
	// builds the nav mesh
	m_navMesh->build();

	// slightly blue version of the thief sprite
	m_shadow = new Shadow("../bin/textures/shadow.png");
		
	// adds three pieces of treasure
	for (unsigned int i = 0; i < 3; i++)
	{
		// sets the texture of the treasure
		m_treasure.push_back(new Shadow("../bin/textures/treasure.png"));
		// sets the size of the bubble
		m_treasure.back()->setBubbleSize(70.0f);
		// sets the identity of the object
		m_treasure.back()->setIdentity(i);
		// ensures that the treasure is visible
		m_treasure.back()->setVisible(true);
	}
	static int timer = 0;
	// sets the position of each treasure piece
	for (auto t : m_treasure)
	{
		// chooses a random node
		Vector2 randNodeTreasure = m_navMesh->getRandomNode()->position;
		t->setPosition(randNodeTreasure.x, randNodeTreasure.y);
		// used to ensure that a position is not overlapping any obstacles
		bool safe = false;
		// chooses a position until its safe
		while (!safe)
		{
			timer++;
			std::cout << timer << std::endl;
			// iterates through each obstacle
			for (auto o : m_obstacles)
			{
				// checks if there is an overlap
				if (t->getBubble().overlaps(o))
				{
					// chooses a new position
					safe = false;
					randNodeTreasure = { rand() / float(RAND_MAX) * getWindowWidth() * 0.75f + getWindowWidth() * 0.125f,
						rand() / float(RAND_MAX) * getWindowHeight() * 0.75f + getWindowHeight() * 0.125f };
					t->setPosition(randNodeTreasure.x, randNodeTreasure.y);
					break;
				}
				else
				{
					safe = true;
				}

				// checks if another treasure is already there
				for (auto t2 : m_treasure)
				{
					if (t->getBubble().overlaps(t2->getBubble()) && t->getIdentity() != t2->getIdentity())
					{
						safe = false;
						break;
					}
				}
			}

			// restarts the program if there are no possible positions for the treasure
			if (timer > 100 && !safe)
			{
				// resets the timer
				timer = 0;

				// cleans up the nav mesh
				delete m_navMesh;
				m_navMesh = nullptr;

				// sets the size of the nav mesh
				m_navMesh = new NavMesh(1280, 720);

				// cleans up the obstacle container
				m_obstacles.clear();

				// 12 random obstacles
				for (int i = 0; i < 15; ++i)
				{
					// if safe is false then an overlap occured
					bool safe = false;
					// creates a random obstacle then checks if it has overlapped with any other obstacles
					do
					{
						safe = m_navMesh->addObstacle(rand() / float(RAND_MAX) * getWindowWidth() * 0.75f + getWindowWidth() * 0.125f,
							rand() / float(RAND_MAX) * getWindowHeight() * 0.75f + getWindowHeight() * 0.125f,
							60.0f, 60.0f,
							10.0f);
					} while (safe == false);
				}

				// transfers the obstacles into AABBs
				for (auto o : m_navMesh->getObstacles())
				{
					m_obstacles.push_back(AABB2(o.x, o.y, o.x + o.w, o.y + o.h));
				}
				// bottom border
				m_obstacles.push_back(AABB2(0.0f, 0.0f, 1280.0f, 10.0f));
				// top border
				m_obstacles.push_back(AABB2(0.0f, 710.0f, 1280.0f, 720.0f));
				// left border first half
				m_obstacles.push_back(AABB2(0.0f, 0.0f, 10.0f, 340.0f));
				// left border second half
				m_obstacles.push_back(AABB2(0.0f, 380.0f, 10.0f, 720.0f));
				// right border
				m_obstacles.push_back(AABB2(1270.0f, 0.0f, 1280.0f, 720.0f));

				// builds the nav mesh
				m_navMesh->build();
			}
		}
	}

	// sets the texture of the player
	m_thief = new Thief("../bin/textures/thief.png");
	// random node position
	Vector2 randNodeThief = m_navMesh->getRandomNode()->position;
	// sets the position of the thief
	m_thief->setPosition(randNodeThief.x, randNodeThief.y);
	// sets the size of the collision around the thief
	m_thief->setBubbleSize(19.0f);
	// sets the maximum speed of the thief
	m_thief->setMaxVelocity(10.0f);
	// gives the thief knowledge of the obstacles
	m_thief->setObstacles(m_obstacles);
	// gives the thief knowledge of the treasure
	m_thief->setTreasure(m_treasure);
	// gives the thief knowledge of the exit
	m_thief->setLocation(*m_exit);
	// sets the behaviour of the thief
	m_thiefBehaviour = new KeyboardBehaviour();
	m_thief->addBehaviour(m_thiefBehaviour);

	for (unsigned int i = 0; i < 3; i++)
	{
		// sets the texture of the enemy
		m_guard.push_back(new GameObject("../bin/textures/guard.png"));
		// sets the position of the guard to the corresponding item to guard
		m_guard.back()->setPosition(m_treasure[i]->getPosition().x, m_treasure[i]->getPosition().y);
		// sets the angle between rays
		m_guard.back()->setAngle(0.59f);
		// sets the length of the rays
		m_guard.back()->setLength(195.0f);
		// sets the size of the range
		m_guard.back()->setRangeSize(195.0f);
		// sets the size of the bubble
		m_guard.back()->setBubbleSize(19.0f);
		// sets the maximum speed of the guard
		m_guard.back()->setMaxVelocity(10.0f);
		// sets the identity of the object
		m_guard.back()->setIdentity(i);
		// gives the guard knowledge of the obstacles
		m_guard.back()->setObstacles(m_obstacles);
	}
	
	// sets up the behaviour trees
	for (unsigned int i = 0; i < 3; i++)
	{
		// dynamically allocates the nodes and sets up their components
		// sixth layer
		m_bt[i].m_attack = new AttackAction(m_thief, 20);
		// fifth layer
		m_bt[i].m_wander = new WanderAction();
		m_bt[i].m_seek = new SeekAction(m_thief);
		m_bt[i].m_path = new PathAction(m_thief, m_navMesh);
		m_bt[i].m_close = new CloseToTargetCondition(m_thief, 200.0f);
		m_bt[i].m_timeout = new TimeoutDecorator(m_bt[i].m_attack, 0.2f);
		m_bt[i].m_veryClose = new VeryCloseToTargetCondition(m_thief, 70.0f);
		// fourth layer
		m_bt[i].m_clear = new ClearPathAction();
		m_bt[i].m_seekTreasure = new SeekAction(m_treasure[i]);
		m_bt[i].m_pathTreasure = new ReturnAction(m_treasure[i], m_navMesh);
		m_bt[i].m_patrol = new PatrolAction(m_treasure[i]);
		m_bt[i].m_closeTreasure = new CloseToTargetCondition(m_treasure[i], m_treasure[0]->getBubble().radius);
		m_bt[i].m_timer = new TimerDecorator(m_bt[i].m_wander, 3.0f, m_thief);
		m_bt[i].m_recentlyChased = new RecentlyChasedCondition(m_thief, m_shadow);
		m_bt[i].m_thiefClose = new Sequence();
		m_bt[i].m_thiefVeryClose = new Sequence();
		// third layer
		m_bt[i].m_returnToTreasure = new Sequence();
		m_bt[i].m_treasureClose = new Sequence();
		m_bt[i].m_wanderOnSpot = new Sequence();
		m_bt[i].m_seekRemaining = new SeekAction(m_thief);
		m_bt[i].m_remaining = new RemainingPathCondition(m_thief, m_shadow);
		m_bt[i].m_attackOrSeek = new Selector();
		m_bt[i].m_canSee = new CanSeeTargetCondition(m_thief, m_bt[i].m_timeout, m_bt[i].m_timer, m_shadow);
		m_bt[i].m_swap = new SwapVelocityAction();
		m_bt[i].m_still = new StillCondition();
		// second layer
		m_bt[i].m_wanderOrPatrol = new Selector();
		m_bt[i].m_lastSeen = new Sequence();
		m_bt[i].m_interactWithThief = new Sequence();
		m_bt[i].m_stillTooLong = new Sequence();
		// first layer
		m_bt[i].m_thiefOrItem = new Selector();

		// set up the structure of the behaviour tree
		// first layer
		m_bt[i].m_thiefOrItem->addChild(m_bt[i].m_stillTooLong);
		m_bt[i].m_thiefOrItem->addChild(m_bt[i].m_interactWithThief);
		m_bt[i].m_thiefOrItem->addChild(m_bt[i].m_lastSeen);
		m_bt[i].m_thiefOrItem->addChild(m_bt[i].m_wanderOrPatrol);
		// second layer
		m_bt[i].m_stillTooLong->addChild(m_bt[i].m_still);
		m_bt[i].m_stillTooLong->addChild(m_bt[i].m_swap);
		m_bt[i].m_interactWithThief->addChild(m_bt[i].m_canSee);
		m_bt[i].m_interactWithThief->addChild(m_bt[i].m_attackOrSeek);
		m_bt[i].m_lastSeen->addChild(m_bt[i].m_remaining);
		m_bt[i].m_lastSeen->addChild(m_bt[i].m_seekRemaining);
		m_bt[i].m_wanderOrPatrol->addChild(m_bt[i].m_wanderOnSpot);
		m_bt[i].m_wanderOrPatrol->addChild(m_bt[i].m_treasureClose);
		m_bt[i].m_wanderOrPatrol->addChild(m_bt[i].m_returnToTreasure);
		// third layer
		m_bt[i].m_attackOrSeek->addChild(m_bt[i].m_thiefVeryClose);
		m_bt[i].m_attackOrSeek->addChild(m_bt[i].m_thiefClose);
		m_bt[i].m_wanderOnSpot->addChild(m_bt[i].m_recentlyChased);
		m_bt[i].m_wanderOnSpot->addChild(m_bt[i].m_timer);
		m_bt[i].m_treasureClose->addChild(m_bt[i].m_closeTreasure);
		m_bt[i].m_treasureClose->addChild(m_bt[i].m_patrol);
		m_bt[i].m_returnToTreasure->addChild(m_bt[i].m_pathTreasure);
		m_bt[i].m_returnToTreasure->addChild(m_bt[i].m_seekTreasure);
		m_bt[i].m_returnToTreasure->addChild(m_bt[i].m_clear);
		// fourth layer
		m_bt[i].m_thiefVeryClose->addChild(m_bt[i].m_veryClose);
		m_bt[i].m_thiefVeryClose->addChild(m_bt[i].m_timeout);
		m_bt[i].m_thiefClose->addChild(m_bt[i].m_close);
		m_bt[i].m_thiefClose->addChild(m_bt[i].m_path);
		m_bt[i].m_thiefClose->addChild(m_bt[i].m_seek);

		// adds the behaviour tree to the agent's behaviour
		m_guard[i]->addBehaviour(m_bt[i].m_thiefOrItem);
	}
	
	return true;
}

void ThiefApp::shutdown() {

	delete m_font;
	delete m_2dRenderer;

	delete m_navMesh;
	m_navMesh = nullptr;
	
	delete m_ground;
	delete m_crates;
	delete m_sign;
	delete m_exit;
	m_exit = nullptr;

	// deletes all behaviour trees
	for (unsigned int i = 0; i < 3; i++)
	{
		// sixth layer
		delete m_bt[i].m_attack;
		m_bt[i].m_attack = nullptr;
		// fifth layer
		delete m_bt[i].m_wander;
		delete m_bt[i].m_seek;
		delete m_bt[i].m_path;
		delete m_bt[i].m_close;
		delete m_bt[i].m_timeout;
		delete m_bt[i].m_veryClose;
		m_bt[i].m_wander = nullptr;
		m_bt[i].m_seek = nullptr;
		m_bt[i].m_path = nullptr;
		m_bt[i].m_close = nullptr;
		m_bt[i].m_timeout = nullptr;
		m_bt[i].m_veryClose = nullptr;
		// fourth layer
		delete m_bt[i].m_clear;
		delete m_bt[i].m_seekTreasure;
		delete m_bt[i].m_pathTreasure;
		delete m_bt[i].m_patrol;
		delete m_bt[i].m_closeTreasure;
		delete m_bt[i].m_timer;
		delete m_bt[i].m_recentlyChased;
		delete m_bt[i].m_thiefClose;
		delete m_bt[i].m_thiefVeryClose;
		m_bt[i].m_clear = nullptr;
		m_bt[i].m_seekTreasure = nullptr;
		m_bt[i].m_pathTreasure = nullptr;
		m_bt[i].m_patrol = nullptr;
		m_bt[i].m_closeTreasure = nullptr;
		m_bt[i].m_timer = nullptr;
		m_bt[i].m_recentlyChased = nullptr;
		m_bt[i].m_thiefClose = nullptr;
		m_bt[i].m_thiefVeryClose = nullptr;
		// third layer
		delete m_bt[i].m_returnToTreasure;
		delete m_bt[i].m_treasureClose;
		delete m_bt[i].m_wanderOnSpot;
		delete m_bt[i].m_seekRemaining;
		delete m_bt[i].m_remaining;
		delete m_bt[i].m_attackOrSeek;
		delete m_bt[i].m_canSee;
		delete m_bt[i].m_swap;
		delete m_bt[i].m_still;
		m_bt[i].m_returnToTreasure = nullptr;
		m_bt[i].m_treasureClose = nullptr;
		m_bt[i].m_wanderOnSpot = nullptr;
		m_bt[i].m_seekRemaining = nullptr;
		m_bt[i].m_remaining = nullptr;
		m_bt[i].m_attackOrSeek = nullptr;
		m_bt[i].m_canSee = nullptr;
		m_bt[i].m_swap = nullptr;
		m_bt[i].m_still = nullptr;
		// second layer
		delete m_bt[i].m_wanderOrPatrol;
		delete m_bt[i].m_lastSeen;
		delete m_bt[i].m_interactWithThief;
		delete m_bt[i].m_stillTooLong;
		m_bt[i].m_wanderOrPatrol = nullptr;
		m_bt[i].m_lastSeen = nullptr;
		m_bt[i].m_interactWithThief = nullptr;
		m_bt[i].m_stillTooLong = nullptr;
		// first layer
		delete m_bt[i].m_thiefOrItem;
		m_bt[i].m_thiefOrItem = nullptr;
	}

	delete m_thief;
	m_thief = nullptr;
	delete m_thiefBehaviour;
	m_thiefBehaviour = nullptr;
	delete m_shadow;
	m_shadow = nullptr;
	for (auto g : m_guard)
	{
		delete g;
		g = nullptr;
	}
	for (auto t : m_treasure)
	{
		delete t;
		t = nullptr;
	}
}

void ThiefApp::update(float deltaTime) {

	// input example
	aie::Input* input = aie::Input::getInstance();

	// only updates if not end of game
	if (m_gameStart && !m_gameLose && !m_gameWin)
	{
		// updates the agents
		m_thief->update(deltaTime);
		for (auto g : m_guard)
		{
			g->update(deltaTime);
		}
	}

	// checks if the thief has collected all the treasure
	if (m_thief->getScore() == m_treasure.size())
	{
		m_gameWin = true;
	}
	// checks if the thief died
	else if (m_thief->getHealth() <= 0)
	{
		m_gameLose = true;
	}
	
	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void ThiefApp::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();

	m_2dRenderer->setRenderColour(1.0f, 1.0f, 1.0f);
	// draws the ground
	m_2dRenderer->drawSprite(m_ground, 640.0f, 360.0f, 1280.0f, 720.0f);

	// draws the exit sign
	m_2dRenderer->drawSprite(m_sign, 14.0f, 360.0f, 50.0f, 50.0f);

	// only draws if not end of game
	if (m_gameStart && !m_gameLose && !m_gameWin)
	{
		// draws the guards
		for (auto g : m_guard)
		{
			m_2dRenderer->drawSpriteTransformed3x3(g->getTexture(), (float*)&g->getTransform());
		}

		// draws the shadow if it is visible
		if (m_shadow->getVisible())
		{
			m_2dRenderer->drawSpriteTransformed3x3(m_shadow->getTexture(), (float*)&m_shadow->getTransform());
		}

		// used to check if the player just got attacked
		static int hp = m_thief->getHealth();
		// used to set a duration for how long the player is displayed as attacked
		static int timer = 0;
		// checks if the player lost health
		if (hp > m_thief->getHealth())
		{
			// if they did lose health then the timer is started
			if (timer <= 50)
			{
				// increments the timer
				timer++;
				// sets the colour of the player to red
				m_2dRenderer->setRenderColour(1.0f, 0.0f, 0.0f);
			}
			// checks if the time is up
			else
			{
				// sets the hp to the current health
				hp = m_thief->getHealth();
				// resets the timer
				timer = 0;
			}
		}
		// draws the thief
		m_2dRenderer->drawSpriteTransformed3x3(m_thief->getTexture(), (float*)&m_thief->getTransform());

		m_2dRenderer->setRenderColour(1.0f, 1.0f, 1.0f);
		// draws the treasure if it is visible
		for (auto t : m_treasure)
		{
			if (t->getVisible())
			{
				m_2dRenderer->drawSprite(t->getTexture(), t->getPosition().x, t->getPosition().y, 30.0f, 30.0f);
			}
		}
	}
	
	
	m_2dRenderer->setRenderColour(1.0f, 1.0f, 1.0f);
	// draw obstacles
	for (int i = 0; i < m_obstacles.size() - 5; i++)
	{
		m_2dRenderer->drawSprite(m_crates, m_obstacles[i].minimum.x + 30.0f, m_obstacles[i].minimum.y + 30.0f);
	}
	// draws the walls
	m_2dRenderer->setRenderColour(0.0f, 0.0f, 1.0f);
	// bottom wall
	m_2dRenderer->drawLine(0.0f, 5.0f, 1280.0f, 5.0f, 10.0f);
	// top wall
	m_2dRenderer->drawLine(0.0f, 715.0f, 1280.0f, 715.0f, 10.0f);
	// left first wall
	m_2dRenderer->drawLine(5.0f, 0.0f, 5.0f, 340.0f, 10.0f);
	// left second wall
	m_2dRenderer->drawLine(5.0f, 380.0f, 5.0f, 720.0f, 10.0f);
	// right wall
	m_2dRenderer->drawLine(1275.0f, 0.0f, 1275.0f, 720.0f, 10.0f);

	// GUI before the game starts
	if (!m_gameStart)
	{
		ImGui::Begin("Menu");
		ImGui::Text("Welcome to the Thief Simulation");
		ImGui::Text("Try to steal the treasure and take it to the exit.");
		ImGui::Text("If a guard hits you, you will lose a piece of treasure.");
		ImGui::Text("");
		ImGui::Text("Controls:");
		ImGui::Text("Use the mouse for direction");
		ImGui::Text("W to move towards the mouse");
		ImGui::Text("S to move away from the mouse");
		ImGui::Text("A to rotate clockwise around the mouse");
		ImGui::Text("D to rotate anti-clockwise around the mouse");
		ImGui::Text("ESC to leave the game");
		ImGui::Text("");
		ImGui::Text("Click 'Start' to begin.");
		//if the start button is pressed then change the state of the game
		if (ImGui::Button("Start"))
		{
			//starts the game
			m_gameStart = true;
		}
		ImGui::End();
	}
	
	//displays the score and health
	ImGui::Begin("");
	ImGui::Text("Score: %d", m_thief->getScore());
	ImGui::Text("Health: %d", m_thief->getHealth());
	ImGui::End();

	m_2dRenderer->setRenderColour(1.0f, 1.0f, 1.0f);
	// checks if the game was lose
	if (m_gameLose)
	{
		m_2dRenderer->drawText(m_font, "Game Over!", 640.0f, 360.0f);
	}
	// checks if the game was won
	else if (m_gameWin)
	{
		m_2dRenderer->drawText(m_font, "You Win!", 640.0f, 360.0f);
	}

	// done drawing sprites
	m_2dRenderer->end();
}