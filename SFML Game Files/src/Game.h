#pragma once

#include "all_headers.h"
#include "Player.h"

class Game
{
private:
	// Program objects
	InitResources* res;
	Player* player;
	
	// SFML objects
	RenderWindow window;
	Clock timer;
	Event event;

	// Class veriables
	double deltaTime{};
	double wait{};
	time_t get_time{};

	/*
	struct Input{
		bool left{};
		bool right{};
		bool jump{};
		bool dash{};
	}inp;
	*/

private:
	// Main program functions
	void Update();
	void Render();

	// Additional program funtions
	void UpdateEvents();
	void UpdateConsole();
	void UpdateTimers();

public:
	// Constructor, destructor, game running function
	Game();
	~Game();
	void Run();
};

