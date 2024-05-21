#include "Game.h"
#include<fstream>

Game::Game(const std::string& config)
{
	init(config);
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
		if (temp == "Font")
		{
			fin >> m_fontConfig.F		// Font File
				>> m_fontConfig.S		// Font Size
				>> m_fontConfig.R		// RGB Color R
				>> m_fontConfig.G		// RGB Color G
				>> m_fontConfig.B;		// RGB Color B
		}
		if (temp == "Player")
		{
			fin >> m_playerConfig.SR	// Shape Radius
				>> m_playerConfig.CR	// Collision Radius
				>> m_playerConfig.S		// Speed
				>> m_playerConfig.FR	// Fill Color R
				>> m_playerConfig.FG	// Fill Color G
				>> m_playerConfig.FB	// Fill Color B
				>> m_playerConfig.OR	// Outline Color R    
				>> m_playerConfig.OG	// Outline Color G
				>> m_playerConfig.OB	// Outline Color B
				>> m_playerConfig.OT	// Outline Thickness
				>> m_playerConfig.V;	// Shape Vertices
		}
		if (temp == "Enemy")
		{
			fin >> m_enemyConfig.SR		// Shape Radius      
				>> m_enemyConfig.CR		// Collision Radius  
				>> m_enemyConfig.SMIN	// Min Speed   
				>> m_enemyConfig.SMAX	// Max Speed
				>> m_enemyConfig.OR		// Outline Color R     
				>> m_enemyConfig.OG		// Outline Color G
				>> m_enemyConfig.OB		// Outline Color B
				>> m_enemyConfig.OT		// Outline Thickness 
				>> m_enemyConfig.VMIN	// Min Vertices
				>> m_enemyConfig.VMAX	// Max Vertices   
				>> m_enemyConfig.L		// Small Lifespan    
				>> m_enemyConfig.SI;	// Spawn Interval
		}
		if (temp == "Bullet")
		{
			fin >> m_bulletConfig.SR	// Shape Radius     
				>> m_bulletConfig.CR	// Collision Radius 
				>> m_bulletConfig.S		// Speed            
				>> m_bulletConfig.FR	// Fill Color R       
				>> m_bulletConfig.FG	// Fill Color G    
				>> m_bulletConfig.FB	// Fill Color B
				>> m_bulletConfig.OR	// Outline Color R 
				>> m_bulletConfig.OG	// Outline Color G
				>> m_bulletConfig.OB	// Outline Color B
				>> m_bulletConfig.OT	// Outline Thickness
				>> m_bulletConfig.V		// Shape Vertices   
				>> m_bulletConfig.L;	// Small Lifespan   
		}
	}


	

	m_window.create(sf::VideoMode(m_windowConfig.W, m_windowConfig.H), "Assignment 2");
	m_window.setFramerateLimit(m_windowConfig.FL);

	spawnPlayer();
}
void Game::run()
{


	while (m_running)
	{
		while (!m_paused)
		{
			m_entities.update();
			sEnemySpawner();
			sCollision();
			sLifespan();
			sMovement();
			m_currentFrame++;
		}
		sUserInput();
		sRender();	
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

void Game::spawnBullet(std::shared_ptr<Entity> entity, const Vec2& target)
{
}

void Game::spawnSpecialWeapon(std::shared_ptr<Entity> entity)
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

