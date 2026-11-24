#include "balloon.h"
#include "texture.h"
#include "rectangle.h"
#include "game.h"
#include <SDL3/SDL.h>

balloon::balloon(Texture* textura, int xSpawn, float velocidad, int color, Game* game)
	: MobileObject(game, Rectangle(Point2D<>(xSpawn, 600.0f), 125.0f, 125.0f), Vector2D<>(0.0f, -velocidad)) {
	this->color = color,
	this->textura = textura;
}


void balloon::render() const{ //Dibuja globo
	SDL_FRect destination = position.to_sdl();
	textura->renderFrame(destination, color, activeFrame);
}

bool balloon::update(float delta){ //Mueve el globo y devuelve false si sale del límite establecido
	if (!exploted) MobileObject::update(delta);
	else {
		animTime += delta;
		if (animTime >= frameTime) {
			animTime = 0.0f;
			activeFrame++;
		}
		if(activeFrame >= 6) animEnd = true;
	}

	return (position.getTopLeftCorner().getY() > -150 && !animEnd);
}

balloon::~balloon() { //Destruye globo

}

bool balloon::hit(const Rectangle& obj) {
	if (exploted) {
		return false;
	}

	if (SceneObject::hit(obj)) {	
		exploted = true;	
		return true;
	}
	return false;
}

int 
balloon::save(std::ostream& os) const {
	Game::ballonData(os, color, exploted, activeFrame, animTime, this->position);
}

void 
balloon::load(std::istream& is) {
	is >> color;
	is >> exploted;
	is >> activeFrame;
	is >> animTime;
	int x, y;
	is >> x;
	is >> y;
	position = Rectangle(Point2D<>(x, y), position.getWidth(), position.getHeight());
}
