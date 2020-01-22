#pragma once

#include "Animation.h"
#include "Collision.h"

class Player
{
	// CLEAR CLASS CODE! + make comment wider
private:
	// SFML objects
	Sprite player;
	Sprite tile;

	// Program objects
	InitResources& res; // do I need this?
	Collision playerHitbox;
	Collision tilehitbox;

	Animation standAnim;
	Animation walkAnim;
	Animation jumpAnim;
	//Animation fallAnim;
	Animation dashAnim;

	// Class veriables
	const int height = 114;
	const int width = 96;
	double display_speed = 0.1;
	Vector2u player_scale;

	Vector2f velocity;
	const float movement_speed = 0.4f;
	const float jump_speed = 1.5f;
	const float max_jump_height = 200.0f;
	float jump_height{};
	const float gravity = 0.01f;

	bool faceRight = true;
	bool can_jump = true;

private:
	// Class funtions
	void HandleInputs(double dt);
	void DisplayAnimations(double dt);
	void PlayerFall();

	// Delete later
	void TempFunc(RenderWindow* window);

	// Initializing functions used in constructor
	void InitFrames();

public:
	// Constructor, destructor, main function
	Player(InitResources& res);
	~Player();
	void Render(RenderWindow* window, double dt, bool console);
	void Console();
};

