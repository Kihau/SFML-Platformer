#include "Player.h"

Player::Player(InitResources& res)
	:standAnim(player), walkAnim(player), jumpAnim(player), dashAnim(player), res(res)
{
	// Setting the player
	player.setTexture(res.player);
	player.setPosition(300.0f, 200.0f);

	velocity.x = 0.0;
	velocity.y = 0.0;

	InitFrames();

	/* Temporary object */
	tile.setTexture(res.tiles);

	playerHitbox.CreateHitbox(84, 36, 30, 30);

	walkAnim.Update(display_speed, false);
}

void Player::InitFrames()
{
		// Adding standing animation frame
	standAnim.AddFrame({IntRect(0, 0, width, height), display_speed});

		// Adding walking animation frames
	for (int i = 0; i < 504; i += width)
	{
		walkAnim.AddFrame({ IntRect(i + width, 0, width, height), display_speed });
		//if (i == 0) walkAnim.AddFrame({ IntRect(i + 90 - 6, 0, width + 6, height), display_speed });
		//else walkAnim.AddFrame({ IntRect(i + 90, 0, width, height), display_speed });
	}

		// Adding jumping animation frames
	jumpAnim.AddFrame({ IntRect(7 * width, 0, width, height), display_speed });
	
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

	if (Keyboard::isKeyPressed(Keyboard::Space) && can_jump)
	{
		velocity.y = -jump_speed;

		// Checking if player reached jump limit
		//if (player.getPosition().y < fabs(tile.getGlobalBounds().top - jump_height)) can_jump = false;
		if (fabs(jump_height) >= max_jump_height)
		{
			can_jump = false;
			jump_height = 0.0f;
		}
		else jump_height -= velocity.y;
	}
	else can_jump = false;
}

void Player::CollisionAndFall()
{
	playerHitbox.UpdateHitbox(player);

	if (playerHitbox.CheckCollision(tile))
	{
		if (!playerHitbox.FixPositionLeftRight(player, tile))
		{
			if (playerHitbox.FixPositionTop(player, tile))
				velocity.y = 0.0f;
		}
	}

	// Checking if player can fall
	if (playerHitbox.CheckCollision(tile) && velocity.y >= 0.0f)
	{
		if (!playerHitbox.FixPositionLeftRight(player, tile))
		{
			playerHitbox.FixPositionBottom(player, tile);
			velocity.y = 0.0f;
		}

		// Turning off auto jump using if statement
		if (!Keyboard::isKeyPressed(Keyboard::Space)) can_jump = true;
	}
	else
	{
		if (velocity.y < max_velocity_y) velocity.y += gravity;
		else velocity.y = max_velocity_y;
	}
}

void Player::DisplayAnimations(double dt)
{
	if (velocity.x == 0.0f && velocity.y == 0.0f) standAnim.Update(dt, false);
	else if (velocity.x != 0.0f && velocity.y == 0.0f) walkAnim.Update(dt, true);
	else jumpAnim.Update(dt, false);
}

void Player::Render(RenderWindow* window, double dt, bool console)
{
	HandleInputs(dt);
	CollisionAndFall();
	DisplayAnimations(dt);
	TempFunc(window);

	player.move(velocity.x, velocity.y);
	window->draw(player);

	if (console)
	{
		playerHitbox.ShowHitbox(window);
		Collision::ShowHitbox(window, tile);
	}
}

// This function is going to be deleted later
void Player::TempFunc(RenderWindow *window)
{
	if (window->getSize().x == 800 && window->getSize().y == 600)
	{
		if (player.getPosition().x > 900) player.setPosition(-100.0f, player.getPosition().y);
		if (player.getPosition().x < -100) player.setPosition(900.0f, player.getPosition().y);

		if (player.getPosition().y > 700) player.setPosition(player.getPosition().x, -100.0f);
		if (player.getPosition().y < -100) player.setPosition(player.getPosition().x, 700.0f);
		
		tile.setPosition(250.0f, 410.f);
	}
	else
	{
		if (player.getPosition().x > 2080) player.setPosition(-100.0f, player.getPosition().y);
		if (player.getPosition().x < -100) player.setPosition(2080.0f, player.getPosition().y);

		if (player.getPosition().y > 1180) player.setPosition(player.getPosition().x, -100.0f);
		if (player.getPosition().y < -100) player.setPosition(player.getPosition().x, 1180.0f);

		tile.setPosition(250.0f, 910.f);
	}

	/*
	for (int i = -20; i < 5000; i += 210)
	{
		tile.setPosition(float(i), 534.f);
		window->draw(tile);
	}

	for (int i = 0; i < 5000; i += 210)
	{
		tile.setPosition(float(i), 510.f);
		window->draw(tile);
	}
	*/

	window->draw(tile);
}


void Player::Console()
{
	cout << "Player position x: " << player.getPosition().x << endl;
	cout << "Player position y: " << player.getPosition().y << endl;

	cout << "\nPlayer left: " << player.getGlobalBounds().left << endl;
	cout << "Player top: " << player.getGlobalBounds().top << endl;
	cout << "Player width: " << player.getGlobalBounds().width << endl;
	cout << "Player hight: " << player.getGlobalBounds().height << endl;

	cout << "\nPlayer velocity x: " << velocity.x << endl;
	cout << "Player velocity y: " << velocity.y << endl;

	playerHitbox.UpdateConsole();
	playerHitbox.UpdateConsoleCollision(tile);

	cout << "\nTile left: " << tile.getGlobalBounds().left << endl;
	cout << "Tile top: " << tile.getGlobalBounds().top << endl;
	cout << "Tile width: " << tile.getGlobalBounds().width << endl;
	cout << "Tile hight: " << tile.getGlobalBounds().height << endl;

}
