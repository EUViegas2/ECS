#include "Game.h"

Game::Game(const std::string& config)
{
	init(config);
}

void Game::init(const std::string& path)
{
	std::ifstream fin(path);

	

	m_window.create(sf::VideoMode(1280, 720), "Assignment 2");
	m_window.setFramerateLimit(60);

	spawnPlayer();
}
void Game::run()
{


	while (m_running)
	{
		m_entities.update();
		sEnemySpawner();
		sCollision();
		sUserInput();
		sRender();


		m_currentFrame++;
	}
}

void Game::setPaused(bool paused)
{
}

void Game::spawnPlayer()
{
	auto entity = m_entities.addEntity("player");

	entity->cTransform = std::make_shared<cTransform>(Vec2(200.f, 200.f), Vec2(1.f, 1.f), 0.f);
	entity->cShape = std::make_shared<cShape>(32.f, 8, sf::Color(10, 10, 10), sf::Color(255, 0, 0), 4.f);
	entity->cInput = std::make_shared<cInput>();
	m_player = entity;
}

void Game::spawnEnemy()
{

	m_lastEnemySpawnTime = m_currentFrame;
}

void Game::spawnSmallEnemies(std::shared_ptr<Entity> e)
{


}

void Game::sEnemySpawner()
{
}

void Game::sCollision()
{
}

void Game::sUserInput()
{
}

void Game::sRender()
{
}

void Game::sMovement()
{
	m_player->c
}

void Game::sLifespan()
{
}

