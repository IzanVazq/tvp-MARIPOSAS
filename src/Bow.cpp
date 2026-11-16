#include "Bow.h"
#include "texture.h"
#include "rectangle.h"
#include <SDL3/SDL.h>
#include "game.h"

Bow::Bow(Texture* textura, Game* game)
	: SceneObject(game, Rectangle(Point2D<>(0.0f, 230.0f), 125.0f, 125.0f)) {
	this->textura = textura;
}

Bow::~Bow() {
}

void Bow::render() const{ //Dibuja arco
	SDL_FRect destination = position.to_sdl();
	if (!charged) textura->renderFrame(destination, 0, 1);
	else textura->renderFrame(destination, 0, 0);
}

bool Bow::update(float delta) { //Mueve el arco dentro de los límites establecidos
	float yPos = position.getTopLeftCorner().getY();
	if((dir < 0.0f && yPos > 20) || (dir > 0.0f && yPos < 450)) position.move(Vector2D<>{0.0f, dir * speed * delta});
	return true;
}

void Bow::handleEvent(const SDL_Event& event)
{
	if (event.type == SDL_EVENT_KEY_DOWN) { //Establece la dirección según la flecha presionada
		if (event.key.key == SDLK_UP) dir = -1.0f;
		else if (event.key.key == SDLK_DOWN) dir = 1.0f;
		else if (event.key.key == SDLK_LEFT && arrowsLeft > 0) charged = true;
		else if (event.key.key == SDLK_RIGHT && charged) {
			game->shootArrow(Rectangle(position.getTopLeftCorner() + Point2D<>(0, 55), 125.0f, 25.0f));
			charged = false;
			arrowsLeft--;
		}
	}
	else if (event.type == SDL_EVENT_KEY_UP) { //Vuelve 0.0f la dirección si se levanta la tecla
		if (event.key.key == SDLK_UP && dir < 0.0f || event.key.key == SDLK_DOWN && dir > 0.0f) dir = 0.0f;
	}
}
