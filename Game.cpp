#include "Game.h"

Game::Game(const std::string& config)
{
	init(config);
}

void Game::changeScene(const std::string& sceneName, std::shared_ptr<Scene> scene, bool endCurrentScene)
{
	m_currentScene = sceneName;
	m_sceneMap[sceneName] = std::move(scene);
}

void Game::init(const std::string& path)
{
	std::ifstream fin(path);
	std::string   temp;
	while (fin >> temp)
	{
		if (temp == "Window")
		{
			fin >> m_windowConfig.W		// Window width
				>> m_windowConfig.H		// Window height
				>> m_windowConfig.FL	// Framerate limit
				>> m_windowConfig.FS;	// Full-screen mode (1) or not (0)
		}
	}
	m_window.create(sf::VideoMode(m_windowConfig.W, m_windowConfig.H), "Assignment 2");
	m_window.setFramerateLimit(m_windowConfig.FL);


}
void Game::run()
{
	while (isRunning()) {
		sUserInput();
		update();
		m_window.display();
	}

}
void Game::quit()
{

	m_running = false;
	m_window.close();
}
void Game::sUserInput()
{


	sf::Event event;
	while (m_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			m_running = false;

		if (event.type == sf::Event::KeyPressed)
		{
			switch (event.key.code)
			{
			case sf::Keyboard::W: m_player->cInput->up = true;
				break;

			case sf::Keyboard::A: m_player->cInput->left = true;
				break;

			case sf::Keyboard::S: m_player->cInput->down = true;
				break;

			case sf::Keyboard::D: m_player->cInput->right = true;
				break;

			case sf::Keyboard::P: m_paused = !m_paused;
				break;

			case sf::Keyboard::Space: spawnSpecialWeapon();
				break;

			default:
				break;
			}
		}
		if (event.type == sf::Event::KeyReleased)
		{
			switch (event.key.code)
			{
			case sf::Keyboard::W: m_player->cInput->up = false;
				break;

			case sf::Keyboard::A: m_player->cInput->left = false;
				break;

			case sf::Keyboard::S: m_player->cInput->down = false;
				break;

			case sf::Keyboard::D: m_player->cInput->right = false;
				break;

			default:
				break;
			}
		}

		if (event.type == sf::Event::MouseButtonPressed)
		{
			if (event.mouseButton.button == sf::Mouse::Left)
				spawnBullet(m_player, Vec2(event.mouseButton.x, event.mouseButton.y));
		}
	}
}
void Game::update()
{
	currentScene()->update();
}

