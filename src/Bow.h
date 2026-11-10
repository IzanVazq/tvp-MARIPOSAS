#pragma once
#include "SDL3/SDL.h"
#include "rectangle.h"
#include "vector2D.h"
#include "texture.h"
class Bow
{
private:
	Rectangle position; //Posición del arco
	Texture* textura;
	float dir = 0.0f; //Dirección de movimiento vertical
	float speed = 200.0f; //Velocidad de movimiento
	int arrowsLeft = 10;
	bool charged = false; //Estado del arco
	bool shoot = false; //Estado del disparo
public:
	Bow(Texture* textura, Rectangle position);
	void render() const;
	bool update(float delta);
	void handleEvent(const SDL_Event& event);	
	bool hasShot();
	Point2D<> getPos() const;

	int getArrowsLeft() const {
		return arrowsLeft;
	}

	void setArrowsLeft(int n) {
		arrowsLeft = n;
	}
};

