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

	if (Keyboard::isKeyPressed(Keyboard::Space) && can_jump)
	{
		velocity.y = -jump_speed;

		// Checking if player reached jump limit
		if (tile.getGlobalBounds().top - player.getPosition().y > jump_height) can_jump = false;
	}
	else can_jump = false;
}

void Player::PlayerFall()
{
	UpdateHitboxes();

	// Checking if player can fall
	if (coll.CheckCollision(hitbox, tile) && velocity.y >= 0.0f)
	{
		velocity.y = 0.0f;
		coll.FixPosition(hitbox, player, tile);

		// Turning off auto jump using if statement
		if (!Keyboard::isKeyPressed(Keyboard::Space)) can_jump = true;
	}
	else
	{
		if (velocity.y < 10) velocity.y += gravity;
		else velocity.y = 10.0f;
	}
}

void Player::UpdateHitboxes()
{
	hitbox.height = 95;
	hitbox.width = 24;
	hitbox.left = player.getGlobalBounds().left + 30;
	hitbox.top = player.getGlobalBounds().top + 30;
}

void Player::DisplayAnimations(double dt)
{
	if (velocity.x == 0.0f && velocity.y == 0.0f) standAnim.Update(dt, false);
	else if (velocity.x != 0.0f && velocity.y == 0.0f) walkAnim.Update(dt, true);
}

void Player::Render(RenderWindow* window, double dt)
{
	HandleInputs(dt);
	PlayerFall();
	DisplayAnimations(dt);
	TempFunc(window);

	player.move(velocity.x, velocity.y);
	window->draw(player);
}

// This function is going to be deleted later
void Player::TempFunc(RenderWindow *window)
{
	if (player.getPosition().x > 850) player.setPosition(-100.0f, player.getPosition().y);
	if (player.getPosition().x < -100) player.setPosition(850.0f, player.getPosition().y);

	if (player.getPosition().y > 700) player.setPosition(player.getPosition().x, -100.0f);
	if (player.getPosition().y < -100) player.setPosition(player.getPosition().x, 700.0f);

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

	tile.setPosition(250.0f, 410.f);
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

	cout << "\nHITBOX left: " << hitbox.left << endl;
	cout << "HITBOX top: " << hitbox.top << endl;
	cout << "HITBOX width: " << hitbox.width << endl;
	cout << "HITBOX hight: " << hitbox.height << endl;
	if (hitbox.intersects(tile.getGlobalBounds()))
		cout << "COLLSISION!\n";
	else cout << "NO\n";

	cout << "\nTile left: " << tile.getGlobalBounds().left << endl;
	cout << "Tile top: " << tile.getGlobalBounds().top << endl;
	cout << "Tile width: " << tile.getGlobalBounds().width << endl;
	cout << "Tile hight: " << tile.getGlobalBounds().height << endl;

}
