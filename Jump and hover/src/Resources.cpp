#include "Resources.h"




Resources::Resources()
{
    try
    {
        loadTextures();
        loadFonts();
        loadSoundBuffer();
        loadSounds();
    }
    catch (const std::exception& e)
    {
        std::cout << e.what();
    }
}

Resources& Resources::instance()
{
    static Resources instance;
    return instance;
}

const sf::Texture& Resources::getTexture(const int index) const
{
    return m_textures[index];
}

const sf::Font& Resources::getFont(const int index) const
{
    return m_fonts[index];
}

sf::Text Resources::makeText(const std::string& string, const int font_index, const int size, const sf::Color& color) const
{
    auto& font = Resources::instance().getFont(font_index);

    sf::Text text;
    text.setFont(font);
    text.setString(string);
    text.setCharacterSize(size);
    text.setStyle(sf::Text::Bold);
    text.setFillColor(color);
    text.setOutlineColor(sf::Color::Black);
    text.setOutlineThickness(1);

    return text;
}

void Resources::playSound(const int index)
{
    if (m_sounds[index].getStatus() == sf::Sound::Status::Stopped)
        m_sounds[index].play();
}

void Resources::playMusic()
{
    m_sounds[BackgroundMusic].setLoop(true);
    m_sounds[BackgroundMusic].setVolume(0);
    m_sounds[BackgroundMusic].play();
}

void Resources::changeVolume()
{
    m_sounds[BackgroundMusic].setVolume(((int)(m_sounds[BackgroundMusic].getVolume() / 50 + 1) % 3) * 50);
}


//loads all the textures from a text file
void Resources::loadTextures()
{
    std::ifstream file;

    //opens the file
    file.open(TexturesList);
    if (!file.is_open())
        throw std::exception(TexturesFileProblem.c_str());

    //reads the image's name and loads the texture into the vector
    for (auto line = std::string(); std::getline(file, line);)
    {
        auto texture = sf::Texture();
        if (!texture.loadFromFile(line))
            throw std::exception((CouldNotLoad + line).c_str());
        m_textures.push_back(texture);
    }
  
    file.close();
}

void Resources::loadFonts()
{
    std::ifstream file;

    //opens the file
    file.open(FontsList);
    if (!file.is_open()) 
        throw std::exception(SoundsFileProblem.c_str());

    //reads the font's name and loads it into the vector
    for (auto line = std::string(); std::getline(file, line);)
    {
        auto font = sf::Font();
        if (!font.loadFromFile(line))
            throw std::exception((CouldNotLoad + line).c_str());
        m_fonts.push_back(font);
    }

    file.close();
}

void Resources::loadSoundBuffer() 
{
    std::ifstream file;

    //opens the file
    file.open(SoundsList);
    if (!file.is_open())
        throw std::exception(FontsFileProblem.c_str());

    for (auto line = std::string(); std::getline(file, line);)
    {
        auto buffer = sf::SoundBuffer();
        if (!buffer.loadFromFile(line))
            throw std::exception((CouldNotLoad + line).c_str());
        m_buffer.push_back(buffer);
    }
}

void Resources::loadSounds()
{
    std::vector<sf::Sound> sounds(m_buffer.size());

    for (int i = 0; i < m_buffer.size(); i++)
        sounds[i].setBuffer(m_buffer[i]);

    m_sounds = sounds;
}