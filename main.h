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

enum class Environment_types{
    player, sky
};

enum class Aircraft_types{
    boeing, four_wings, fighter, baloon1
};

const std::map<Environment_types, game_object> ENVIRONMENT_OBJECTS{
    {Environment_types::player,        { 100,   40,     800, "Images/player.png",             "",                                  Draw_types::rectangle}},
    {Environment_types::sky,           { WIDTH, HEIGHT, 800, "Images/sky.jpg",                "",                                  Draw_types::rectangle}},
    };

const std::map<Aircraft_types, game_object> AIRCRAFT_OBJECTS{
    {Aircraft_types::boeing,     { 200,   80,     800, "Images/plane_boeing_left.png",  "Images/plane_boeing_right.png",     Draw_types::rectangle}},
    {Aircraft_types::four_wings, { 100,   40,     200, "Images/plane_4wings_left.png",  "Images/plane_four_wings_right.png", Draw_types::rectangle}},
    {Aircraft_types::fighter,    { 150,   60,     800, "Images/plane_fighter_left.png", "Images/plane_fighter_right.png",    Draw_types::rectangle}},
    {Aircraft_types::baloon1,    { 150,  220,     50,  "Images/baloon_1_left.png",      "",                                  Draw_types::rectangle}},
    };

// Logic classes
class Game;
class GameObject;
class Player;
class Aircraft;

// Common class for all objects in the game
class GameObject
{
protected:
    sf::Vector2f position;
    sf::Texture texture;
    sf::Drawable *object;
    sf::RectangleShape *rect_object;
    sf::Vector2f motion;
    // void draw();
public:
    game_object data;
    GameObject(game_object game_object, sf::Vector2f position);
    ~GameObject() {delete object, rect_object;};
    virtual void move();
    sf::Drawable * get_object();
    sf::RectangleShape * get_rect_object();
    void set_motion_x(float xmotion);
    void set_motion_y(float ymotion);
};
// Class describes player
class Player : public GameObject
{
private:

public:
    Player() : GameObject(ENVIRONMENT_OBJECTS.at(Environment_types::player), sf::Vector2f(MIN_WIDTH,(MAX_HEIGHT + MIN_HEIGHT)/2)){ };
    ~Player() {};
    // void draw() override;
    void move() override;
};
// Class describes other aircrafts except player
class Aircraft : public GameObject
{
private:
    /* data */
public:
    Aircraft_types aircraft_type;
    Aircraft(Aircraft_types aircraft_type, game_object game_object, sf::Vector2f position)
        : GameObject(game_object, position), aircraft_type(aircraft_type) {};
    ~Aircraft() {};
};
// Common class-fabric
class Game
{
private:
    // Time
    sf::Clock clock_player;
    sf::Clock clock_aircrafts;
    sf::Clock clock_aircrafts_creation;
public:
    Player player;
    std::vector<GameObject*> background_objects;
    std::vector<GameObject*> aircraft_objects;
    GameObject * q;
    Game(/* args */);
    ~Game();
    void init_game();
    float get_time_player(int multiplicator);
    float get_time_aircrafts(int multiplicator);
    float get_time_aircrafts_creation(int multiplicator);
    // float get_time(int multiplicator);
    void process_events(sf::Event event);
    void create_aircrafts();
    void delete_aircrafts();
    void cycle();
};

int main();

#endif