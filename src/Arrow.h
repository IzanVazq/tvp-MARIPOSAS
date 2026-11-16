#pragma once
#include "SDL3/SDL.h"
#include "rectangle.h"
#include "vector2D.h"
#include "texture.h"
class Game;
class Arrow
{
private:
	Rectangle position;
	Texture* textura;
	float dir = 1.0f;
	float speed = 200.0f;
	Game* game;

public:
	Arrow(Texture* textura, Rectangle position, Game* game);
	~Arrow();
	void render() const;
	bool update(float delta);
};
