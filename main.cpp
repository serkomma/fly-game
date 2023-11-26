#include "main.h"
//----------------------------
const std::string GAME_NAME = "Fly";
//-------------------------------------
int main()
{   
    // Window
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), GAME_NAME);

    // Sky
    sf::Texture textureSky;
    textureSky.loadFromFile(SKY_IMG);
    sf::RectangleShape gamebackground(sf::Vector2f(WIDTH, HEIGHT));
    gamebackground.setTexture(&textureSky);

    //Player
    Player player;
    player.draw();
    sf::Vector2f playerPos;

    while (window.isOpen())
    {
        auto time = clock1.getElapsedTime().asSeconds();
        auto timePlayer = time*PLAYER_SPEED;
        clock1.restart();

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            switch (event.type)
            {   // Keys
                case sf::Event::KeyPressed:
                            if (event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::Up)    playerPos.y = -1 * timePlayer;
                            if (event.key.code == sf::Keyboard::A || event.key.code == sf::Keyboard::Left)  playerPos.x = -1 * timePlayer;
                            if (event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down)  playerPos.y = timePlayer;
                            if (event.key.code == sf::Keyboard::D || event.key.code == sf::Keyboard::Right) playerPos.x = timePlayer;
                    break;
                case sf::Event::KeyReleased:
                            if (event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::Up)    playerPos.y = 0;
                            if (event.key.code == sf::Keyboard::A || event.key.code == sf::Keyboard::Left)  playerPos.x = 0;
                            if (event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down)  playerPos.y = 0;
                            if (event.key.code == sf::Keyboard::D || event.key.code == sf::Keyboard::Right) playerPos.x = 0;
                    break;
            }
        }

        window.clear();
        window.draw(gamebackground);
        player.move(playerPos);
        window.draw(player.get_object());
        window.display();
    }

    return 0;
}

GameObject::GameObject(){
}

GameObject::~GameObject(){
}

sf::RectangleShape & GameObject::get_object(){
    return *object;
}

Player::Player(/* args */){
}

Player::~Player(){
}

void Player::draw(){
    texture.loadFromFile(PLAYER_IMG);
    object = new sf::RectangleShape(sf::Vector2f(100, 40));
    (*object).setTexture(&texture);
    (*object).setPosition(sf::Vector2f(MIN_WIDTH,(MAX_HEIGHT + MIN_HEIGHT)/2));
    
}

void Player::move(sf::Vector2f bias){
    // Player control
    (*object).move(bias);
    // Borders
    auto position = (*object).getPosition();
    if (position.x > MAX_WIDTH)
        (*object).setPosition(MAX_WIDTH, position.y);
    if (position.y > MAX_HEIGHT)
        (*object).setPosition(position.x, MAX_HEIGHT);
    if (position.x < MIN_WIDTH)
        (*object).setPosition(MIN_WIDTH, position.y);
    if (position.y < MIN_HEIGHT)
        (*object).setPosition(position.x, MIN_HEIGHT);
    if (position.x > MAX_WIDTH && position.y > MAX_HEIGHT)
        (*object).setPosition(MAX_WIDTH, MAX_HEIGHT);
    if (position.x > MAX_WIDTH && position.y < MIN_HEIGHT)
        (*object).setPosition(MAX_WIDTH, MIN_HEIGHT);
    if (position.x < MIN_WIDTH && position.y > MAX_HEIGHT)
        (*object).setPosition(MIN_WIDTH, MAX_HEIGHT);
    if (position.x < MIN_WIDTH && position.y < MIN_HEIGHT)
        (*object).setPosition(MIN_WIDTH, MIN_HEIGHT);
}