#include "Player.h"

Player::Player(InitResources& res)
	:standAnim(player), walkAnim(player), jumpAnim(player), dashAnim(player), res(res)
{
	// Setting the player
	player.setTexture(res.player);

	player_pos.x = 300.0f;
	player_pos.y = 200.0f;

	player.setPosition(player_pos);

	velocity.x = 0.0;
	velocity.y = 0.0;

	InitFrames();
}

void Player::InitFrames()
{
		// Adding standing animation frame
	standAnim.AddFrame({IntRect(0, 0, 84, height), display_speed});

		// Adding walking animation frames
	for (int i = 0; i <= 360; i += 72)
	{
		// Changing 2nd frame cuz animator is retarded
		if (i == 0) walkAnim.AddFrame({ IntRect(i + 90 - 6, 0, width + 6, height), display_speed });
		else walkAnim.AddFrame({ IntRect(i + 90, 0, width, height), display_speed });
	}

		// Adding jumping animation frames
	for (int i = 0; i <= NULL; i++)
		jumpAnim.AddFrame({ IntRect(2, i, width, height), NULL });
	
		// Adding dash animation frames
	for (int i = 0; i <= NULL; i++)
		dashAnim.AddFrame({ IntRect(3, i, width, height), NULL });
}

Player::~Player()
{
	/* STUFF */
}

void Player::HandleInputs(double dt)
{
	velocity.x = 0.0f;

	if (Keyboard::isKeyPressed(Keyboard::D))
	{
		if (!faceRight)
		{
			player.setScale(1.0f, 1.0f);
			player.move(-90.0f, 0.0f);
		}
		else velocity.x += movement_speed;

		faceRight = true;
	}

	if (Keyboard::isKeyPressed(Keyboard::A))
	{
		if (faceRight)
		{
			player.setScale(-1.0f, 1.0f);
			player.move(90.0f, 0.0f);
		}
		else velocity.x -= movement_speed;

		faceRight = false;
	}

	if (Keyboard::isKeyPressed(Keyboard::Space))
	{
		if (velocity.y == 0.0f && can_jump)
			velocity.y = -movement_speed;
	}

	if (!can_jump)
	{
		if (progress < jump_time) progress += dt;
		else velocity.y += static_cast<float>(gravity * dt);
	}
	else velocity.y = 0.0f;
}

void Player::DisplayAnimations(double dt)
{
	if (velocity.x == 0.0f && velocity.y == 0.0f) standAnim.Update(dt, false);
	else if (velocity.x != 0.0f && velocity.y == 0.0f) walkAnim.Update(dt, true);
}


void Player::Render(RenderWindow& window, double dt)
{
	//if (PlayerIsWalking(dt)) walkAnim.Update(dt, true);
	//else PlayerIsStanding(dt);

	HandleInputs(dt);
	DisplayAnimations(dt);

	player.move(velocity.x, velocity.y);
	player_pos += velocity;
	window.draw(player);
}


void Player::UpdateConsole()
{
	cout << "Player position x: " << player_pos.x << endl;
	cout << "Player position y: " << player_pos.y << endl;
}
