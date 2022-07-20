#include "Controller.h"




void Controller::run(sf::RenderWindow& window, const std::vector<sf::Sprite>& background, const int level_number)
{
    ContactListener listener;
    int level = level_number;
    bool back = false;

    sf::Clock clock;
    float time = 0;
    
    while (window.isOpen() && !back)
    {
        GameManager::instance().reset();
        float delay_time = 0;
        auto game_window = GameWindow(listener, level);

        while (window.isOpen() && GameManager::instance().isGameLive() && !back)
        {
            time = float(clock.getElapsedTime().asSeconds());
            clock.restart();

            keyboardEvents(window, game_window, time, back);
            drawAndUpdate(window, game_window, background, time);
            checkLevelStatus(delay_time, time, level, back);
        }
    }
}




void Controller::keyboardEvents(sf::RenderWindow& window, 
                                GameWindow& game_window, 
                                const float time, 
                                bool& back)
{
    auto event = sf::Event();

    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            window.close();
            break;
        case sf::Event::KeyReleased:
            if (event.key.code == sf::Keyboard::Up ||
                event.key.code == sf::Keyboard::Space)
            {
                GameManager::instance().updateKeyStatus(UnPressed);
                game_window.playerHover(false);
            }

            break;
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))         
        game_window.movePlayer(-Speed * time, 0.f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))        
        game_window.movePlayer(Speed * time, 0.f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || 
        sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            if (!GameManager::instance().isKeyPressed())
            {
                if (game_window.isPlayerOnGround())
                    game_window.movePlayer(0.f, -Force * time);
                else
                    game_window.playerHover(true);

                GameManager::instance().updateKeyStatus(Pressed);
            }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::B))            
        if (!GameManager::instance().isKeyPressed())
        {
            back = true;
            GameManager::instance().updateKeyStatus(Pressed);
        }
}


void Controller::drawAndUpdate(sf::RenderWindow& window, 
                                GameWindow& game_window, 
                                const std::vector<sf::Sprite>& background, 
                                const float time)
{
    window.clear(sf::Color::White);
    for (auto& object : background)
        window.draw(object);
    game_window.drawScreen(window);
    window.display();
    game_window.updateScreen(time);
}


void Controller::checkLevelStatus(float& delay_time, const float time, int& level, bool& back)
{
    if (GameManager::instance().isLevelWon() || GameManager::instance().isLevelLost())
    {
        delay_time += time;

        if (delay_time > 1.3f)
        {
            if (GameManager::instance().isLevelWon())
                level++;
            if (level == NumberOfLevels)
            {
                back = true;
                level--;
            }

            GameManager::instance().updateLevelNumber(level);
            GameManager::instance().nextLevel();
        }
    }
}
