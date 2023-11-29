 #include "main.h"
//----------------------------

//-------------------------------------
int main()
{   
    // Window
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), GAME_NAME);
    // Initial game object
    Game game; 
    game.init_game();

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            game.process_events(event);
        }
        game.get_clock().restart();

        window.clear();
        // Background objects
        for (auto bg : game.background_objects)
            window.draw((*bg).get_object());
        // Player object
        game.player.move();
        window.draw(game.player.get_object());
        // Aircraft object
        for (auto ac : game.aircraft_objects)
            window.draw((*ac).get_object());

        window.display();
    }

    return 0;
};

Game::Game(/* args */)
{
}

Game::~Game()
{
}

void Game::init_game(){
    // Sky
    background_objects.push_back(new GameObject(GAME_OBJECTS.at("sky"), sf::Vector2f(0,0)));
    //Player
    Player player;
}
sf::Clock & Game::get_clock(){
    return clock;
}

void Game::process_events(sf::Event event){
    switch (event.type)
        {   // Keys
            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::Up)    player.set_motion_y(-1 * get_time(PLAYER_SPEED));
                if (event.key.code == sf::Keyboard::A || event.key.code == sf::Keyboard::Left)  player.set_motion_x(-1 * get_time(PLAYER_SPEED));
                if (event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down)  player.set_motion_y(get_time(PLAYER_SPEED));
                if (event.key.code == sf::Keyboard::D || event.key.code == sf::Keyboard::Right) player.set_motion_x(get_time(PLAYER_SPEED));
                break;
            case sf::Event::KeyReleased:
                if (event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::Up)    player.set_motion_y(0);
                if (event.key.code == sf::Keyboard::A || event.key.code == sf::Keyboard::Left)  player.set_motion_x(0);
                if (event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down)  player.set_motion_y(0);
                if (event.key.code == sf::Keyboard::D || event.key.code == sf::Keyboard::Right) player.set_motion_x(0);
                break;
        }
};

float Game::get_time(int multiplicator){
    return clock.getElapsedTime().asSeconds() * multiplicator;
}

GameObject::GameObject(game_object game_object, sf::Vector2f position){
    data = game_object;
    switch (game_object.draw_type)
    {
    case Draw_types::rectangle:
        texture.loadFromFile(game_object.img);
        object = new sf::RectangleShape(sf::Vector2f(game_object.width, game_object.height));
        rect_object = (sf::RectangleShape*) (object);
        (*rect_object).setTexture(&texture);
        (*rect_object).setPosition(position);
        object = rect_object;
        rect_object = nullptr;
        break;
    
    default:
        break;
    }
}

GameObject::~GameObject(){
}


void GameObject::move(){
    switch (data.draw_type)
    {
    case Draw_types::rectangle:
        rect_object = (sf::RectangleShape*) (object);
        (*rect_object).move(motion);
        object = rect_object;
        rect_object = nullptr;
        break;
    
    default:
        break;
    }
}

void GameObject::set_motion_x(float xmotion){
    this->motion.x = xmotion;
}

void GameObject::set_motion_y(float ymotion){
    this->motion.y = ymotion;
}

sf::Drawable & GameObject::get_object(){
    return *object;
}

void Player::move(){
    // Player control
    rect_object = (sf::RectangleShape*) (object);
    (*rect_object).move(motion);
    // Borders
    auto position = (*rect_object).getPosition();
    if (position.x > MAX_WIDTH)
        (*rect_object).setPosition(MAX_WIDTH, position.y);
    if (position.y > MAX_HEIGHT)
        (*rect_object).setPosition(position.x, MAX_HEIGHT);
    if (position.x < MIN_WIDTH)
        (*rect_object).setPosition(MIN_WIDTH, position.y);
    if (position.y < MIN_HEIGHT)
        (*rect_object).setPosition(position.x, MIN_HEIGHT);
    if (position.x > MAX_WIDTH && position.y > MAX_HEIGHT)
        (*rect_object).setPosition(MAX_WIDTH, MAX_HEIGHT);
    if (position.x > MAX_WIDTH && position.y < MIN_HEIGHT)
        (*rect_object).setPosition(MAX_WIDTH, MIN_HEIGHT);
    if (position.x < MIN_WIDTH && position.y > MAX_HEIGHT)
        (*rect_object).setPosition(MIN_WIDTH, MAX_HEIGHT);
    if (position.x < MIN_WIDTH && position.y < MIN_HEIGHT)
        (*rect_object).setPosition(MIN_WIDTH, MIN_HEIGHT);
    object = rect_object;
    rect_object = nullptr;
}

// Aircraft::Aircraft()
// {
// }

// Aircraft::~Aircraft()
// {
// }