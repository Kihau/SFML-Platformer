#pragma once

#include "Animation.h"
//#include "InitResources.h"

class Player
{
	// CLEAR CLASS CODE!
private:
	// SFML objects
	Sprite player;

	// Program objects
	Animation standAnim;
	Animation walkAnim;
	Animation jumpAnim;
	Animation dashAnim;

	// Class veriables
	const int height = 102 + 13;
	const int width = 72;
	double display_speed = 0.1;
	Vector2u player_scale;
	Vector2f player_pos;

	Vector2f velocity;

	const float movement_speed = 0.4f;
	const float jump_speed = 1.5f;

	//double progress{};
	const float gravity = 0.01f;

	bool faceRight = true;
	bool can_jump = true;

private:
	// Class funtions
	void HandleInputs(double dt);
	void DisplayAnimations(double dt);

	// Initializing functions used in constructor
	void InitFrames();
	InitResources& res;

public:
	// Constructor, destructor, main function
	Player(InitResources& res);
	~Player();
	void Render(RenderWindow* window, double dt);
	void UpdateConsole();
};

