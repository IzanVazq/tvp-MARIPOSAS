#include "balloon.h"
#include "texture.h"
#include "rectangle.h"
#include <SDL3/SDL.h>

balloon::balloon(Texture* textura, Rectangle position, float velocidad, int color) {
		this->position = position,
		this->velocity = Vector2D(0.0f, -velocidad),
		this->color = color,
		this->textura = textura;
}


void balloon::render() const{ //Dibuja globo
	SDL_FRect destination = position.to_sdl();
	textura->renderFrame(destination, color, activeFrame);
}

bool balloon::update(float delta){ //Mueve el globo y devuelve false si sale del límite establecido
	if(!exploted) position.move(velocity * delta);
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

	if (position.hasIntersection(obj)) {	
		exploted = true;	
		return true;
	}
	return false;
}
