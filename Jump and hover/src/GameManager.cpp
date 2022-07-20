#include "GameManager.h"







GameManager::GameManager()
{
    buildMap(BackgroundFile);
}


void GameManager::buildMap(const std::string& level_name)
{
    m_map.clear();

    std::ifstream file;

    //opens the file
    file.open(level_name);
    if (!file.is_open()) 
        throw std::exception(LevelFileProblem.c_str());

    //reads the level
    for (auto line = std::string(); std::getline(file, line);)
    {
        m_map.push_back(line);
    }

    file.close();
}


GameManager& GameManager::instance()
{
    static GameManager instance;
    return instance;
}


std::vector<sf::Sprite> GameManager::biuldBackground()
{
    std::vector<sf::Sprite> objects;

    for (int row = 0; row < m_map.size(); row++)
    {
        for (int col = 0; col < m_map[row].size(); col++)
        {
            const sf::Texture* texture;

            if (m_map[row][col] == WallObject || m_map[row][col] == GroundObject)
                texture = &Resources::instance().getTexture(WallTexture);
            else
                texture = &Resources::instance().getTexture(BackgroundTexture);

            auto object = sf::Sprite(*texture);
            auto position = convertPosition({ (float)col, (float)row }, (*texture).getSize());
            object.setPosition(position);
            objects.push_back(object);
        }
    }
    return objects;
}


void GameManager::buildGameObjects(b2World* world,
                                    Player& player,
                                    std::vector<std::unique_ptr<DynamicObject>>& dynamic_objects, 
                                    std::vector<std::unique_ptr<StaticObject>>& static_objects,
                                    const int level_number)
{
    auto name = std::to_string(level_number) + ".txt";
    this->buildMap(name);

    for (int row = 0; row < m_map.size(); row++)
    {
        for (int col = 0; col < m_map[row].size(); col++) 
        {
            if (m_map[row][col] == EmptyObject)
                continue;
   
            try
            {
                buildObject(m_map[row][col], sf::Vector2f((float)col, (float)row), world, static_objects, dynamic_objects, player);
            }
            catch (const std::invalid_argument& e)
            {
                std::cout << e.what() << "\n";
            }
        }
    }
}


void GameManager::buildObject(char name, 
                              const sf::Vector2f& position, 
                              b2World* world, 
                              std::vector<std::unique_ptr<StaticObject>>& static_objects, 
                              std::vector<std::unique_ptr<DynamicObject>>& dynamic_objects, 
                              Player& player)
{    
    if (auto static_obj = Factory<StaticObject>::create((Objects)name, position, world))
        static_objects.push_back(std::move(static_obj));

    else if (auto dynamic_obj = Factory<DynamicObject>::create((Objects)name, position, world))
        dynamic_objects.push_back(std::move(dynamic_obj));

    else if (auto player_obj = Factory<Player>::create((Objects)name, position, world))
        player = *player_obj.get();

    else
        throw std::invalid_argument((CouldNotLoad + name).c_str());
}


sf::Vector2f GameManager::convertPosition(const sf::Vector2f& position, const sf::Vector2u& texture_size)
{
    return sf::Vector2f(float(position.x * texture_size.x), float(position.y * texture_size.y));
}

void GameManager::reset()
{
    m_level_lost = false;
    m_level_won = false;
    m_repeat_level = false;
    m_next_level = false;
}

void GameManager::updateLevelNumber(const int level)
{
    m_current_level = level;
    if (level > m_top_level_achieved)
        m_top_level_achieved = level;
}

void GameManager::levelLost()
{
    m_level_lost = true;
}

void GameManager::levelWon()
{
    m_level_won = true;
}

void GameManager::repeatLevel()
{
    m_repeat_level = true;
}

void GameManager::nextLevel()
{
    m_next_level = true;
}

void GameManager::updateKeyStatus(const bool state)
{
    m_key_pressed = state;
}

void GameManager::loadData()
{
    std::ifstream file;

    //opens the file
    file.open(LogFile);
    if (!file.is_open())
        throw std::exception(LogFileProblem.c_str());

    for (auto line = std::string(); std::getline(file, line);)
    {
        m_top_level_achieved = std::stoi(line);
    }

    file.close();
}

void GameManager::saveData()
{
    std::ofstream file;

    //opens the file
    file.open(LogFile);
    if (!file.is_open())
        throw std::exception(LogFileProblem.c_str());

    file << m_top_level_achieved;
    file.close();
}

bool GameManager::isGameLive() const
{
    return !m_repeat_level && !m_next_level;
}

bool GameManager::isLevelLost() const
{
    return m_level_lost;
}

bool GameManager::isLevelWon() const
{
    return m_level_won;
}

bool GameManager::isKeyPressed() const
{
    return m_key_pressed;
}

int GameManager::currentLevel() const
{
    return m_current_level;
}

int GameManager::topLevelAchieved() const
{
    return m_top_level_achieved;
}
