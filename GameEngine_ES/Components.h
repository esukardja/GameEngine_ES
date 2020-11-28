#pragma once

#include <iostream>

#include <SFML/Graphics.hpp>
#include "ECS.h"

struct Transform
{
	ECS_DECLARE_TYPE;

	float xPos, yPos, rotation;

	Transform(float x, float y)
	{
		this->xPos = x;
		this->yPos = y;

		this->rotation = 0.0f;
	}
};
ECS_DEFINE_TYPE(Transform);

struct Sprite2D
{
public:
	ECS_DECLARE_TYPE;

	sf::Sprite sprite;
	std::string texture;
	unsigned int width, height;

	Sprite2D(std::string filePath) 
	{
		texture = filePath;
	}
};
ECS_DEFINE_TYPE(Sprite2D);

struct Animator
{
public:
	ECS_DECLARE_TYPE;

	int frameWidth, frameHeight;
	int currentColumn, currentRow;
	int totalColumns, totalRows;

	float currentTime, nextTimeFrame;

	bool bIsFacingRight;

	Animator(
		int newWidth, int newHeight,
		float timeBetweenFrames,
		int newColumns, int newRows)
	{
		this->frameWidth = newWidth;
		this->frameHeight = newHeight;
		
		currentColumn = 0;
		currentRow = 0;


		this->nextTimeFrame = timeBetweenFrames;
		this->totalColumns = newColumns;
		this->totalRows = newRows;

		currentTime - 0;

		bIsFacingRight = true;
	}
};
ECS_DEFINE_TYPE(Animator);