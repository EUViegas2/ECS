#pragma once

#include "Entity.h"
#include "EntityManager.h"

#include<SFML/Graphics.hpp>

struct PlayerConfig { int SR, CR, FR, FG, FB, OR, OG, OB, OT, V; float S; };
struct EnemyConfig { int SR, CR, OR, OG, OB, OT, VMIN, VMAX, L, SI; float SMIN, SMAX; };
struct BulletConfig { int SR, CR, FR, FG, FB, OR, OG, OB, OT, V, L; float S; };
struct WindowConfig { int W, H, FL, FS; };
struct FontConfig { std::string F; int S, R, G, B; };
/*
SR Shape Radius
CR Colision Radius
FR 
FG
FB Fill Colors RGB
OR
OG
OB Outline Colors RGB
OT Outline Thickness
V Vertices / Vmin VMAX vertices
L LifeSpan
S Speed / Smin SMAX speeds
SI Spawn Interval
*/
class Game
{
	sf::RenderWindow		m_window;	//the window to be drawn
	EntityManager			m_entities;	//vector of entities to maintain
	sf::Font				m_font;		//the font to use
	sf::Text				m_text;		//the score text to be drawn on screen
	PlayerConfig			m_playerConfig;
	EnemyConfig				m_enemyConfig;
	BulletConfig			m_bulletConfig;
	WindowConfig			m_windowConfig;
	FontConfig				m_fontConfig;
	sf::Clock				m_deltaClock;

	int						m_score					{ 0 };
	int						m_currentFrame			{ 0 };
	int						m_lastEnemySpawnTime	{ 0 };
	int						m_lastBulletSpawnTime	{ 0 };

	bool					m_paused				{ false };
	bool					m_running				{ true };


	std::shared_ptr<Entity> m_player;



	void init(const std::string& path);
	void setPaused(bool paused);

	void sEnemySpawner();
	void sCollision();
	void sUserInput();
	void sRender();
	void sMovement();
	void sLifespan();

	void spawnPlayer();
	void spawnEnemy();
	void spawnSmallEnemies(std::shared_ptr<Entity> e);
	void spawnBullet(std::shared_ptr<Entity> entity, const Vec2& target);
	void spawnSpecialWeapon();

public:

	Game(const std::string& config);

	void run();
};

