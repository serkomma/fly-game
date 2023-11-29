#ifndef GAME_FLY
#define GAME_FLY
#include <SFML/Graphics.hpp>
#include <string>
// Screen
const std::string GAME_NAME = "Fly";
const int WIDTH = 1280;
const int HEIGHT = 720;

// Game Field
const int MIN_HEIGHT = 40;
const int MAX_HEIGHT = HEIGHT - 120;

const int MIN_WIDTH = 40;
const int MAX_WIDTH = WIDTH - 120;

// Player
const int PLAYER_SPEED = 600;

// Types of draw objects
enum class Draw_types{
    rectangle, sprite
};

//Aircrafts
struct game_object{
    int width;
    int height;
    int speed;
    std::string img;
    std::string img_add;
    Draw_types draw_type;
};

const std::map<std::string, game_object> GAME_OBJECTS{
    {"player",     { 100,   40,     800, "Images/player.png",             "",                                  Draw_types::rectangle}},
    {"sky",        { WIDTH, HEIGHT, 800, "Images/sky.jpg",                "",                                  Draw_types::rectangle}},
    {"boeing",     { 100,   40,     800, "Images/plane_boeing_left.png",  "Images/plane_boeing_right.png",     Draw_types::rectangle}},
    {"four_wings", { 100,   40,     200, "Images/plane_boeing_left.png",  "Images/plane_four_wings_right.png", Draw_types::rectangle}},
    {"fighter",    { 100,   40,     800, "Images/plane_fighter_left.png", "Images/plane_fighter_right.png",    Draw_types::rectangle}},
    {"baloon1",    { 100,   40,     50,  "Images/baloon_1_left.png",      "",                                  Draw_types::rectangle}},
    };

// Logic classes
class Game;
class GameObject;
class Player;

// Common class for all objects in the game
class GameObject
{
protected:
    game_object data;
    sf::Vector2f position;
    sf::Texture texture;
    sf::Drawable *object;
    sf::RectangleShape *rect_object;
    sf::Vector2f motion;
    // void draw();
public:
    GameObject(game_object game_object, sf::Vector2f position);
    ~GameObject();
    virtual void move();
    sf::Drawable & get_object();
    void set_motion_x(float xmotion);
    void set_motion_y(float ymotion);
};
// Class describes player
class Player : public GameObject
{
private:

public:
    Player() : GameObject(GAME_OBJECTS.at("player"), sf::Vector2f(MIN_WIDTH,(MAX_HEIGHT + MIN_HEIGHT)/2)){ };
    ~Player() {delete object, rect_object;};
    // void draw() override;
    void move() override;
};
// Common class
class Game
{
private:
    // Time
    sf::Clock clock;
public:
    Player player;
    std::vector<GameObject*> background_objects;
    std::vector<GameObject*> aircraft_objects;
    GameObject * q;
    Game(/* args */);
    ~Game();
    void init_game();
    sf::Clock & get_clock();
    float get_time(int multiplicator);
    void process_events(sf::Event event);
};

// Class describes other aircrafts except player
// class Aircraft : public GameObject
// {
// private:
//     /* data */
// public:
//     Aircraft();
//     ~Aircraft();
// };

int main();

#endif