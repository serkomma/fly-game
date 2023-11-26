#ifndef GAME_FLY
#define GAME_FLY
#include <SFML/Graphics.hpp>
#include <string>
// Screen
// const std::string GAME_NAME = "Fly";
const int WIDTH = 1280;
const int HEIGHT = 720;

// Game Field
const int MIN_HEIGHT = 40;
const int MAX_HEIGHT = HEIGHT - 120;

const int MIN_WIDTH = 40;
const int MAX_WIDTH = WIDTH - 120;

// Media
const std::string SKY_IMG = "Images/sky.jpg";
const std::string PLAYER_IMG = "Images/player.png";

// Player
const int PLAYER_SPEED = 600;

// Time
sf::Clock clock1;

// Logic classes
// Common abstract class for all objects
class GameObject
{
protected:
    sf::Vector2f position;
    sf::Texture texture;
    sf::RectangleShape *object;
public:
    GameObject();
    ~GameObject();
    virtual void draw() = 0;
    virtual void move(sf::Vector2f bias) = 0;
    sf::RectangleShape & get_object();
};
// Class describes player
class Player : public GameObject
{
private:
    /* data */
public:
    Player(/* args */);
    ~Player();
    void draw() override;
    void move(sf::Vector2f bias) override;
};

int main();
#endif

