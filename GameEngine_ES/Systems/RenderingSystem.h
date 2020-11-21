#pragma once

#include "..\Engine.h"


class RenderingSystem : public ECS::EntitySystem
{
public:
	RenderingSystem(void);
	~RenderingSystem(void);

	void tick(ECS::World* world, float deltaTime) override;
private:
	// This is a dynamic list with generic types of a Key (String) and a Vlaue (Texture*), respectively, called textureMap
	// Basically, this takes in an object (string) and uniquely maps it a position in memory where it stores a pointer to a Texture
	std::unordered_map<std::string, sf::Texture*> textureMap;

	sf::Texture* LoadTexture(std::string texture);
};

