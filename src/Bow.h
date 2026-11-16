#pragma once
#include "SceneObject.h"
#include "SDL3/SDL.h"
#include "rectangle.h"
#include "vector2D.h"
#include "texture.h"
class Bow : SceneObject
{
private:
	Texture* textura;
	float dir = 0.0f; //Dirección de movimiento vertical
	float speed = 200.0f; //Velocidad de movimiento
	int arrowsLeft = 10;
	bool charged = false; //Estado del arco
public:
	Bow(Texture* textura, Game* game);
	~Bow();
	void render() const;
	bool update(float delta);
	void handleEvent(const SDL_Event& event);	
	int getArrowsLeft() const {
		return arrowsLeft;
	}
	void setArrowsLeft(int n) {
		arrowsLeft = n;
	}
};

