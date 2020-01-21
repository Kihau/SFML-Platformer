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
	InitResources& res;
	Collision coll;

	Animation standAnim;
	Animation walkAnim;
	Animation jumpAnim;
	//Animation fallAnim;
	Animation dashAnim;

	// Class veriables
	const int height = 102 + 13;
	const int width = 72;
	double display_speed = 0.1;
	Vector2u player_scale;

	/* Temporary veriable */
	float groung_height = 400.0f;
	Rect <float> hitbox;

	Vector2f velocity;

	const float movement_speed = 0.4f;
	const float jump_speed = 1.5f;
	const float jump_height = 200.0f;
	const float gravity = 0.01f;

	bool faceRight = true;
	bool can_jump = true;

private:
	// Class funtions
	void HandleInputs(double dt);
	void DisplayAnimations(double dt);
	void PlayerFall();
	void UpdateHitboxes();

	// Delete later
	void TempFunc(RenderWindow* window);

	// Initializing functions used in constructor
	void InitFrames();

public:
	// Constructor, destructor, main function
	Player(InitResources& res);
	~Player();
	void Render(RenderWindow* window, double dt);
	void Console();
};

