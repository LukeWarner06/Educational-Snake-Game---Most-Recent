#pragma once
#include <SFML/Audio.hpp>
#include <map>
#include <string>

class SoundManager
{
private:
	std::map<std::string, sf::SoundBuffer> buffers;
	std::map<std::string, sf::Sound> sounds;

public:
	void Load(const std::string& name, const std::string& filepath);
	void Play(const std::string& name);
};

