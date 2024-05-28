#pragma once
#include "Scene.h"

struct PlayerConfig { int SR, CR, FR, FG, FB, OR, OG, OB, OT, V; float S; };
struct EnemyConfig { int SR, CR, OR, OG, OB, OT, VMIN, VMAX, L, SI; float SMIN, SMAX; };
struct BulletConfig { int SR, CR, FR, FG, FB, OR, OG, OB, OT, V, L; float S; };
struct FontConfig { std::string F; int S, R, G, B; };


class ScenePlay :
    public Scene
{
    FontConfig				m_fontConfig;
    PlayerConfig			m_playerConfig;
    EnemyConfig				m_enemyConfig;
    BulletConfig			m_bulletConfig;

    EntityManager			m_entities;	//vector of entities to maintain
    sf::Font				m_font;		//the font to use
    sf::Text				m_text;		//the score text to be drawn on screen


    sf::RectangleShape		m_rectFill;
    sf::RectangleShape		m_rectOutline;

    std::shared_ptr<Entity> m_player;
    std::string m_levelPath;

    int						m_score{ 0 };
    int						m_highScore{ 0 };



    int						m_lastEnemySpawnTime{ 0 };
    int						m_lastBulletSpawnTime{ 0 };
    int						m_lastSpecialSpawnTime{ 0 };
    int						m_weaponCounter{ 0 };
    bool					m_sWeaponActive{ false };
    bool					m_sWeaponMultiplier{ true };

    void init(const std::string& path);
    ScenePlay(Game* game, const std::string& Levelpath);
    void setPaused(bool paused);
    void loadFont();
    void sEnemySpawner();
    void sCollision();
    void sRender();
    void sMovement();
    void sLifespan();
    void update();
    void updateWeaponState();
    void updateScore(std::shared_ptr<Entity> entity);
    void showScore();
    void showHighScore();
    void spawnPlayer();
    void spawnEnemy();
    void spawnSmallEnemies(std::shared_ptr<Entity> e);
    void spawnBullet(std::shared_ptr<Entity> entity, const Vec2& target);
    void spawnSpecialWeapon();
};

