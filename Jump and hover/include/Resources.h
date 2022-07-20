#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <fstream>
#include <iostream>
#include "Enums.h"




class Resources
{

	std::vector<sf::Texture> m_textures;	// vector of textures
	std::vector<sf::SoundBuffer> m_buffer;	// vector of soundbuffer
	std::vector<sf::Sound> m_sounds;		// vector of sounds
	std::vector<sf::Font> m_fonts;			// vector of fonts

	Resources();
	Resources(const Resources&) = delete;
	Resources& operator=(const Resources&) = delete;

	void loadSoundBuffer();
	void loadSounds();
	void loadTextures();
	void loadFonts();

public:

	static Resources& instance();
	~Resources() = default;

	const sf::Texture& getTexture(const int) const;
	const sf::Font& getFont(const int) const;
	sf::Text makeText(const std::string&, const int, const int = 24, const sf::Color & = sf::Color::White) const;

	void playSound(const int);
	void playMusic();
	void changeVolume();
};