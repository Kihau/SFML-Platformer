#include "Game.h"

Game::Game(bool console) :event()
{
    window = new RenderWindow(VideoMode(800, 600), "SFML GAME", Style::Close | Style::Titlebar);
    get_time = std::clock();
    //timer.restart();
    srand((unsigned)time(NULL));

    res = new InitResources(console);
    player = new Player(*res); 

    window->setIcon(100, 100, res->icon.getPixelsPtr());

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
		Render();
		Update();
	}
}

void Game::Render()
{
    window->clear(Color(100, 100, 100, 0));

    // Rendering stuff here (in correct order)
        /*background*/
        /*map*/
    player->Render(window, deltaTime, console);

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
    UpdateInputs();
    UpdateTimers();
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
            else if (Keyboard::isKeyPressed(Keyboard::F1))
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
    player->Console();
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
    if (!fullres) window = new RenderWindow(VideoMode(), "SFML GAME", Style::Fullscreen);
    else window = new RenderWindow(VideoMode(800, 600), "SFML GAME", Style::Close | Style::Titlebar);

    window->setIcon(100, 100, res->icon.getPixelsPtr());

    fullres = !fullres;

    delete[] this->window;
    this->window = window;
}

