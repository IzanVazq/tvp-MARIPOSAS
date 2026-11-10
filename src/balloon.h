#pragma once

#include "rectangle.h"
#include "vector2D.h"
#include "texture.h"
class balloon
{
private:
	Rectangle position; // Posicion y dimensiones
	Vector2D<> velocity; // Velocidad
	int color; // Indice del coso
	bool exploted = false; //Estado del globo
	Texture* textura;

public:
	balloon(Texture* textura, Rectangle position, float velocidad, int color);
	~balloon();
	void render() const;
	bool update(float delta);
	bool hit(const Rectangle& obj);
};

