#include "Game.h"
#include<fstream>
#include<iostream>

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

	//weapon bar
	m_rectOutline.setSize(sf::Vector2f(m_fontConfig.S * 8, m_fontConfig.S));
	m_rectFill.setSize(sf::Vector2f(0, m_fontConfig.S));
	m_rectOutline.setFillColor(sf::Color::Transparent);
	m_rectOutline.setOutlineColor(sf::Color::White);
	m_rectOutline.setOutlineThickness(2);
	m_rectOutline.setPosition(5, (m_fontConfig.S + 5) * 2);
	m_rectFill.setFillColor(sf::Color::Red);
	m_rectFill.setPosition(5, (m_fontConfig.S + 5) * 2);

	spawnPlayer();
	loadFont();
}
void Game::run()
{
	while (m_running)
	{
		if (!m_paused)
		{
			m_entities.update();
			sCollision();
			sLifespan();
			sMovement();
			showScore();
			m_currentFrame++;
			if(!m_sWeaponActive)
				sEnemySpawner();
		}
		updateWeaponState();
		sUserInput();
		sRender();
		if (m_sWeaponActive)
			spawnSpecialWeapon();
		if (m_paused)
			showHighScore();
	}
}
void Game::setPaused(bool paused)
{
}
void Game::updateWeaponState()
{
	if(m_lastSpecialSpawnTime<m_rectOutline.getSize().x)
		m_lastSpecialSpawnTime += 1;
	m_rectFill.setSize(sf::Vector2f(m_lastSpecialSpawnTime, m_fontConfig.S));
}
void Game::loadFont()
{
	if (!m_font.loadFromFile(m_fontConfig.F))
	{
		std::cerr << "Could not Load Font!\n";
		exit(-1);
	}

	m_text.setFont(m_font);
	m_text.setString("Score :" + std::to_string(m_score));
	m_text.setCharacterSize(m_fontConfig.S);
	m_text.setFillColor(sf::Color(m_fontConfig.R, m_fontConfig.G, m_fontConfig.B));
	m_text.setPosition(5, 5);


}
void Game::updateScore(std::shared_ptr<Entity> entity)
{
	if (!entity)
	{
		if (m_score > m_highScore) { m_highScore = m_score; }
		m_score = 0;
	}
	else 	m_score += entity->cScore->score;

}
void Game::showScore()
{
	m_text.setString("Score: " + std::to_string(m_score));
}
void Game::showHighScore()
{
	m_text.setString("HighScore : " + std::to_string(m_highScore));
}
void Game::spawnPlayer()
{
	auto entity = m_entities.addEntity("player");

	entity->cTransform = std::make_shared<cTransform>(Vec2(200.f, 200.f), Vec2(1.f, 1.f), 0.f);
	entity->cShape = std::make_shared<cShape>(32.f, 8, sf::Color(10, 10, 10), sf::Color(255, 0, 0), 4.f);
	entity->cInput = std::make_shared<cInput>();
	entity->cCollision = std::make_shared<cCollision>(m_playerConfig.CR);
	m_player = entity;
}
void Game::spawnEnemy()
{
	if(m_currentFrame > m_lastEnemySpawnTime + 5)
	{
		int speed = rand() % (int)(m_enemyConfig.SMAX - m_enemyConfig.SMIN) + m_enemyConfig.SMIN;
		auto entity = m_entities.addEntity("enemy");

		float ex = rand() % (m_window.getSize().x - 2 * m_enemyConfig.SR) + m_enemyConfig.SR;
		float ey = rand() % (m_window.getSize().y - 2 * m_enemyConfig.SR) + m_enemyConfig.SR;
		entity->cTransform = std::make_shared<cTransform>(
			Vec2(ex, ey),
			Vec2(cosf((rand() % 1000) / 500.0f * 3.14159f), sinf((rand() % 1000) / 500.0f * 3.14159f)) * speed ,
			0.f);

		entity->cShape = std::make_shared<cShape>(
			m_enemyConfig.SR,
			(rand()%(m_enemyConfig.VMAX - m_enemyConfig.VMIN)+m_enemyConfig.VMIN),
			sf::Color(rand() % 255, rand() % 255, rand() % 255),
			sf::Color(m_enemyConfig.OR, m_enemyConfig.OG, m_enemyConfig.OB),
			m_enemyConfig.OT);

		entity->cScore = std::make_shared<cScore>(entity->cShape->circle.getPointCount());

		entity->cCollision = std::make_shared<cCollision>(m_enemyConfig.CR);
		//entity->cLifespan = std::make_shared<cLifespan>(m_enemyConfig.L*2);

		if (m_sWeaponActive)
			entity->cTransform->vel *= 0;

		m_lastEnemySpawnTime = m_currentFrame;
	}

}
void Game::spawnSmallEnemies(std::shared_ptr<Entity> e)
{
	int vertices = e->cShape->circle.getPointCount();
	int radius = e->cShape->circle.getRadius();
	sf::Color fill = e->cShape->circle.getFillColor();
	sf::Color outline = e->cShape->circle.getOutlineColor();
	float thickness = e->cShape->circle.getOutlineThickness();
	Vec2 pos = e->cTransform->pos;

	for (int i = 0; i < vertices; i++)
	{
		float ang = i * 2 * 3.14159f / vertices;
		Vec2 vel = Vec2(cosf(ang), sinf(ang)) * e->cTransform->vel.dist(Vec2(0.0f, 0.0f));

		auto smallEnemy = m_entities.addEntity("small");
		smallEnemy->cTransform = std::make_shared<cTransform>(pos, vel, 0);
		smallEnemy->cShape = std::make_shared<cShape>(radius / 2, vertices, fill, outline, thickness / 2);
		smallEnemy->cCollision = std::make_shared<cCollision>(radius / 2);
		smallEnemy->cLifespan = std::make_shared<cLifespan>(m_enemyConfig.L);
		smallEnemy->cScore = std::make_shared<cScore>(1);
	}
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
void Game::spawnSpecialWeapon()
{
	
	if (!m_sWeaponActive)
	{
		m_weaponCounter = m_currentFrame;
		m_sWeaponActive = true;
		m_sWeaponMultiplier = false;
	}
	else if (m_currentFrame == m_weaponCounter + 50)
	{
				m_sWeaponActive = false;
				m_sWeaponMultiplier = true;
				
	}
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
	//Player - bounds collision
	if (m_player->cTransform->pos.x < m_player->cCollision->radius)
		m_player->cTransform->pos.x = m_player->cCollision->radius;
	if (m_player->cTransform->pos.y < m_player->cCollision->radius)
		m_player->cTransform->pos.y = m_player->cCollision->radius;
	if (m_player->cTransform->pos.x > m_window.getSize().x - m_player->cCollision->radius)
		m_player->cTransform->pos.x = m_window.getSize().x - m_player->cCollision->radius;
	if (m_player->cTransform->pos.y > m_window.getSize().y - m_player->cCollision->radius)
		m_player->cTransform->pos.y = m_window.getSize().y - m_player->cCollision->radius;

	//enemy collision
	for (auto& e : m_entities.getEntities("enemy"))
	{
		if (
			(e->cTransform->pos.x < e->cCollision->radius && e->cTransform->vel.x < 0) ||
			(e->cTransform->pos.x > m_window.getSize().x - e->cCollision->radius && e->cTransform->vel.x > 0)
			)
		{
			e->cTransform->vel.x *= -1;
		}

		if (
			(e->cTransform->pos.y < e->cCollision->radius && e->cTransform->vel.y < 0) ||
			(e->cTransform->pos.y > m_window.getSize().y - e->cCollision->radius && e->cTransform->vel.y > 0)
			)
		{
			e->cTransform->vel.y *= -1;
		}

		//enemy-bullet
		for(auto& b: m_entities.getEntities("bullet"))
		{
			if (b->cTransform->pos.dist(e->cTransform->pos) < (b->cCollision->radius + e->cCollision->radius))
			{
				m_score += e->cScore->score;
				b->destroy();
				e->destroy();
				spawnSmallEnemies(e);

				updateScore(e);
			}
		}

		//enemy-player
		if (m_player->cTransform->pos.dist(e->cTransform->pos) < (m_player->cCollision->radius + e->cCollision->radius))
		{
			m_highScore = m_score;
			m_score = 0;
			m_player->destroy();
			e->destroy();
			spawnPlayer();
			updateScore(nullptr);
		}

		for (auto e : m_entities.getEntities("small"))
		{
			// player - small
			if (m_player->cTransform->pos.dist(e->cTransform->pos) < (m_player->cCollision->radius + e->cCollision->radius))
			{
				m_highScore = m_score;
				m_score = 0;
				m_player->destroy();
				e->destroy();
				spawnPlayer();
			}
			// bullet-small
			for (auto& b : m_entities.getEntities("bullet"))
			{
				if (b->cTransform->pos.dist(e->cTransform->pos) < (b->cCollision->radius + e->cCollision->radius))
				{
					m_score += e->cScore->score;
					b->destroy();
					e->destroy();
					updateScore(e);

				}
			}
		}
	}
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
void Game::sRender()
{
	m_window.clear();
	
	for (auto e : m_entities.getEntities())
	{
		
		e->cShape->circle.setPosition(e->cTransform->pos.x, e->cTransform->pos.y);

		e->cTransform->angle += 1.f;
		e->cShape->circle.setRotation(e->cTransform->angle);
		m_window.draw(e->cShape->circle);
	}
	m_window.draw(m_rectOutline);
	m_window.draw(m_rectFill);

	m_window.draw(m_text);
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
		if(e->tag() == "enemy" || e->tag() == "samll")
			e->cTransform->pos += e->cTransform->vel * m_sWeaponMultiplier;
		else
			e->cTransform->pos += e->cTransform->vel;
	}
}
void Game::sLifespan()
{
	// TODO: implement all lifespan functionality
	//
	// for all entities
	for (auto& e : m_entities.getEntities())
	{
		if (!e->cLifespan) 
			continue;

		if (e->cLifespan->remaining > 0) 
			e->cLifespan->remaining -= 1;

		else 
			e->destroy();

		if (e->isActive())
		{
			sf::Color col = e->cShape->circle.getFillColor();
			int alpha = 255 * e->cLifespan->remaining / e->cLifespan->total;
			e->cShape->circle.setFillColor(sf::Color(col.r, col.g, col.b, alpha));
		}

	}
	//	   if it has lifespan and its time is up
	//		  destroy the entity
}