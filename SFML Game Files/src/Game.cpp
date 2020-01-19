#include "Game.h"

Game::Game(bool console) :event()
{
    window = new RenderWindow(VideoMode(800, 600), "test window", Style::Close | Style::Titlebar);
	//window.create(VideoMode(800, 600), "test window", Style::Close | Style::Titlebar);
    get_time = std::clock();
    //timer.restart();
    srand((unsigned)time(NULL));

    res = new InitResources(console);
    player = new Player(*res); 

    this->console = console;
}

Game::~Game()
{
    delete player;
    delete res;
    delete window;
}

void Game::Run()
{
	while (window->isOpen())
	{
		Update();
		Render();
	}
}

void Game::Render()
{
    window->clear(Color(100, 100, 100, 0));

    // Rendering stuff here
        /*background*/
    player->Render(window, deltaTime);
        /*map*/

    window->display();
}

void Game::Update()
{
    //cout << "wait time: " << wait << endl;
    if (wait > 500 && console)
    {
        system("cls");
        UpdateConsole();
        wait = {};
    }
    UpdateEvents();
    UpdateTimers();
    UpdateInputs();
}

void Game::UpdateEvents()
{
    while (window->pollEvent(event))
    {
        switch (event.type)
        {
        case Event::Closed:
            window->close();
            break;

        case Event::KeyPressed:
            if (Keyboard::isKeyPressed(Keyboard::Escape))
                window->close();
            if (Keyboard::isKeyPressed(Keyboard::F1))
                ChangeWindow();
            break;

        default:
            break;
        }
    }
}

void Game::UpdateInputs()
{
    if (Keyboard::isKeyPressed(Keyboard::A)) inp.left = true;
    else inp.left = false;

    if (Keyboard::isKeyPressed(Keyboard::D)) inp.right = true;
    else inp.right = false;

    if (Keyboard::isKeyPressed(Keyboard::Space)) inp.jump = true;
    else inp.jump = false;
}

void Game::UpdateConsole()
{
	cout << "Render time: " << deltaTime  << " seconds" << endl;

    cout << endl;
    player->UpdateConsole();
    cout << endl;

    if (inp.right) cout << "Right button is pressed\n";
    else cout << "Right button is NOT pressed\n";

    if (inp.left) cout << "Left button is pressed\n";
    else cout << "Left button is NOT pressed\n";

    if (inp.jump) cout << "Jump button is pressed\n";
    else cout << "Jump button is NOT pressed\n";
}

void Game::UpdateTimers()
{
    deltaTime = timer.restart().asSeconds();
    wait += (std::clock() - get_time);
    //get_time = 0;
    get_time = std::clock();
}

void Game::ChangeWindow()
{
    RenderWindow* window;
    if (!fullres) window = new RenderWindow(VideoMode(1920, 1080), "test window", Style::Fullscreen);
    else window = new RenderWindow(VideoMode(800, 600), "test window", Style::Close | Style::Titlebar);

    fullres = !fullres;

    delete[] this->window;
    this->window = window;
}

