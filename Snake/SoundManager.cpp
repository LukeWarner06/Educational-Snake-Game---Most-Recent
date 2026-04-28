#include "SoundManager.h"
#include <iostream>

// Loads the sound, ready to be played.
void SoundManager::Load(const std::string& name, const std::string& filepath)
{
	sf::SoundBuffer buffer;
	if (!buffer.loadFromFile(filepath))
	{
		std::cout << "Failed to load audio file: " << filepath << "\n";
		return;
	}

	buffers[name] = buffer;

	sounds.emplace(name, sf::Sound(buffers[name]));
}

// Plays the sound using the name from the load function.
void SoundManager::Play(const std::string& name)
{
	auto it = sounds.find(name);

	if (it != sounds.end())
	{
		it->second.play();
	}

	else
	{
		std::cout << "Audio not found: " << name << "\n";
	}
}
