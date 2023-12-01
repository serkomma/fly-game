 #include "main.h"
//----------------------------

//-------------------------------------
int main()
{   
    // Window
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), GAME_NAME);
    // Init game object
    Game game; 
    game.init_game();

    while (window.isOpen())
    {
        game.create_aircrafts();
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            game.process_events(event);
        }
        game.cycle();
        
        // Background objects
        for (auto bg : game.background_objects)
            window.draw(*(*bg).get_object());
        // Player object
        game.player.move();
        window.draw(*game.player.get_object());
        // Aircraft object
        for (auto & ac : game.aircraft_objects){
            window.draw(*(*ac).get_object());
            ac->move();
        }
        
        window.display();
        window.clear();
        game.delete_aircrafts();
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
    background_objects.push_back(new GameObject(ENVIRONMENT_OBJECTS.at(Environment_types::sky), sf::Vector2f(0,0)));
    //Player
    Player player;
    srand(time(0));
}
// sf::Clock & Game::get_clock_player(){
//     return clock_player;
// }

// sf::Clock & Game::get_clock_aircrafts(){
//     return clock_aircrafts;
// }

void Game::process_events(sf::Event event){
    switch (event.type)
        {   // Keys
            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::Up)    player.set_motion_y(-1 * get_time_player(PLAYER_SPEED));
                if (event.key.code == sf::Keyboard::A || event.key.code == sf::Keyboard::Left)  player.set_motion_x(-1 * get_time_player(PLAYER_SPEED));
                if (event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down)  player.set_motion_y(get_time_player(PLAYER_SPEED));
                if (event.key.code == sf::Keyboard::D || event.key.code == sf::Keyboard::Right) player.set_motion_x(get_time_player(PLAYER_SPEED));
                break;
            case sf::Event::KeyReleased:
                if (event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::Up)    player.set_motion_y(0);
                if (event.key.code == sf::Keyboard::A || event.key.code == sf::Keyboard::Left)  player.set_motion_x(0);
                if (event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down)  player.set_motion_y(0);
                if (event.key.code == sf::Keyboard::D || event.key.code == sf::Keyboard::Right) player.set_motion_x(0);
                break;
        }
};

float Game::get_time_player(int multiplicator){
    return clock_player.getElapsedTime().asSeconds() * multiplicator;
}

float Game::get_time_aircrafts(int multiplicator){
    return clock_aircrafts.getElapsedTime().asSeconds() * multiplicator;
}

float Game::get_time_aircrafts_creation(int multiplicator){
    return clock_aircrafts_creation.getElapsedTime().asSeconds() * multiplicator;
}

void Game::create_aircrafts(){
    Aircraft * aircraft;
    if (get_time_aircrafts_creation(1000) > 2000)
    {
        int plane = rand() % (AIRCRAFT_OBJECTS.size());
        auto aircraft_width = AIRCRAFT_OBJECTS.at(Aircraft_types(plane)).width;
        auto aircraft_height = AIRCRAFT_OBJECTS.at(Aircraft_types(plane)).height;
        if (Aircraft_types(plane) == Aircraft_types::baloon1){
            
            // int x = rand() % (HEIGHT - AIRCRAFT_OBJECTS.at(Aircraft_types(plane)).height + 1);
            int x = rand() % ((WIDTH + aircraft_height));
            aircraft = new Aircraft(Aircraft_types(plane), AIRCRAFT_OBJECTS.at(Aircraft_types(plane)),
                sf::Vector2f(x, HEIGHT + aircraft_height));
            aircraft->set_motion_y(-0.2);
            aircraft->set_motion_x(-0.05);
        }
        else{
            int x = rand() % (HEIGHT - aircraft_height + 1);
            aircraft = new Aircraft(Aircraft_types(plane), AIRCRAFT_OBJECTS.at(Aircraft_types(plane)),
                sf::Vector2f(WIDTH + aircraft_width, x));
            aircraft->set_motion_x(-0.4);//get_time_aircrafts(100));
        }
        aircraft_objects.push_back(aircraft);
        clock_aircrafts_creation.restart();
    }
    
}

void Game::delete_aircrafts(){
    // std::vector<GameObject>::iterator iter;
    // iter = aircraft_objects.begin();
    for (auto & ac : aircraft_objects)
    {   
        sf::RectangleShape* rect_object = (sf::RectangleShape*) (ac->get_object());
        if (rect_object->getPosition().x < (0 - ac->data.width))
        {
            delete ac;
            ac = nullptr;
        }
    }
    // std::vector<GameObject*> aircraft_objects2;
    // std::copy (aircraft_objects.begin(), aircraft_objects.end(), aircraft_objects2.begin());
    // std::erase_if(aircraft_objects,[](auto const & x) { return x == nullptr; }); // C++20

    for (auto first = aircraft_objects.begin(), last = aircraft_objects.end(); first != last;){
        if (!aircraft_objects.empty() and (*first) == nullptr)
            first = aircraft_objects.erase(first);
        else
            ++first;
    }

    // bool deleted;
    // while (true)
    // {   
    //     deleted = false;
    //     for (auto first = aircraft_objects2.begin(), last = aircraft_objects2.end(); first != last;){
    //         if ((*first) == nullptr){
    //             first = aircraft_objects.erase(first);
    //             deleted = true;
    //             break;
    //         }
    //     }
        
    // }
    
}

void Game::cycle(){
    clock_player.restart();
    clock_aircrafts.restart();
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

sf::Drawable * GameObject::get_object(){
    return object;
}

sf::RectangleShape * GameObject::get_rect_object(){
    return rect_object;
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

