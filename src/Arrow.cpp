	#include "Arrow.h"
	#include "texture.h"
	#include "rectangle.h"
	#include <SDL3/SDL.h>
	#include "game.h"

	Arrow::Arrow(Texture* textura, Rectangle position, Game* game) {
		this->position = position;
		this->textura = textura;
		this->game = game;
	}

	void Arrow::render() const
	{
		SDL_FRect destination = position.to_sdl();
		textura->renderFrame(destination, 0, 0);
	}

	bool Arrow::update(float delta) {
		position.move(Vector2D<>{dir* speed* delta, 0.0f}); //Movimiento de flecha
		
		Point2D<> pos = position.getTopLeftCorner(); //Obtiene la posicion de la flecha
		Rectangle punta(Point2D<>(pos.getX() + position.getWidth() - 20, pos.getY()), 10.0f, 10.0f); //Crea un rectangle en la punta

		game->checkCollision(punta); //Revisa colisión de la punta con los globos
		return (position.getTopLeftCorner().getX() < 900); //Devuelve false si se sale de la pantalla
	}

	Arrow::~Arrow() {

	}
