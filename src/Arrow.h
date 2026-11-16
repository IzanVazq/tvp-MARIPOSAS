#pragma once
#include "MobileObject.h"
#include "SDL3/SDL.h"
#include "rectangle.h"
#include "vector2D.h"
#include "texture.h"
class Game;
class Arrow : MobileObject
{
private:
	Texture* textura;
	float dir = 1.0f;
	float speed = 200.0f;

public:
	Arrow(Texture* textura, Rectangle position, Game* game);
	~Arrow();
	void render() const;
	bool update(float delta);
};
