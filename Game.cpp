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
		if (!m_paused)
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
	auto entity = m_entities.addEntity("enemy");

	float ex = rand() % m_window.getSize().x;
	float ey = rand() % m_window.getSize().y;
	entity->cTransform = std::make_shared<cTransform>(Vec2(ex, ey), Vec2(0.f, 0.f), 0.f);

	entity->cShape = std::make_shared<cShape>(16.f, 3, sf::Color(0, 0, 255), sf::Color(255, 255, 255), 4.f);

	m_lastEnemySpawnTime = m_currentFrame;
}

void Game::spawnSmallEnemies(std::shared_ptr<Entity> e)
{


}

void Game::spawnBullet(std::shared_ptr<Entity> entity, const Vec2& target)
{
	if (m_currentFrame - m_lastBulletSpawnTime > 5)
	{
		Vec2 velocity = target - entity->cTransform->pos;
		velocity /= entity->cTransform->pos.dist(target);
		velocity *= m_bulletConfig.S;

		auto e = m_entities.addEntity("bullet");
		e->cShape = std::make_shared<cShape>
			(
			m_bulletConfig.SR,
			m_bulletConfig.V,
			sf::Color(m_bulletConfig.FR, m_bulletConfig.FG, m_bulletConfig.FB),
			sf::Color(m_bulletConfig.OR, m_bulletConfig.OG, m_bulletConfig.OB),
			m_bulletConfig.OT
			);

		e->cTransform = std::make_shared<cTransform>
			(entity->cTransform->pos, velocity, 0);
		e->cLifespan = std::make_shared<cLifespan>
			(m_bulletConfig.L);
		e->cCollision = std::make_shared<cCollision>
			(m_bulletConfig.CR);

		m_lastBulletSpawnTime = m_currentFrame;
	}
}

void Game::spawnSpecialWeapon(std::shared_ptr<Entity> entity)
{
}

void Game::sEnemySpawner()
{
	if (m_currentFrame - m_lastEnemySpawnTime > m_enemyConfig.SI)
	{
		spawnEnemy();
		m_lastEnemySpawnTime = m_currentFrame;
	}
}

void Game::sCollision()
{
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

			case sf::Keyboard::Space: spawnSpecialWeapon(m_player);
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

void Game::sRender()
{
	m_window.clear();
	
	for (auto e : m_entities.getEntities())
	{
		m_window.draw(e->cShape->circle);
		e->cShape->circle.setPosition(e->cTransform->pos.x, e->cTransform->pos.y);

		e->cTransform->angle += 1.f;
		e->cShape->circle.setRotation(e->cTransform->angle);
	}
	m_window.display();
}

void Game::sMovement()
{
	m_player->cTransform->vel = Vec2(0.0f, 0.0f);
	float speed = 10.0f;
	sf::Vector2u win = m_window.getSize();

	if (m_player->cInput->up)
	{ m_player->cTransform->vel.y -= m_playerConfig.S; }

	if (m_player->cInput->down)
	{ m_player->cTransform->vel.y += m_playerConfig.S; }

	if (m_player->cInput->left)
	{ m_player->cTransform->vel.x -= m_playerConfig.S; }

	if (m_player->cInput->right)
	{ m_player->cTransform->vel.x += m_playerConfig.S; }

	if (m_player->cTransform->vel.x != 0 && m_player->cTransform->vel.y != 0)
		m_player->cTransform->vel.setLength(m_playerConfig.S);

	for (auto& e : m_entities.getEntities())
	{
		e->cTransform->pos += e->cTransform->vel;
	}
}

void Game::sLifespan()
{
}

