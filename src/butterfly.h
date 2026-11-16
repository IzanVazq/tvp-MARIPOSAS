#pragma once

#include "MobileObject.h"
#include "texture.h"

class Butterfly : public MobileObject
{
private:
    Texture* textura;
    bool dead = false;

    float directionTimer = 0.0f;
    float directionInterval = 2.0f;

    //animacion
    int activeFrame = 0;
    float animTime = 0.0f;
    const float frameTime = 0.1f;

public:
    Butterfly(Texture* textura, Game* game,
        const Rectangle& position,
        const Vector2D<>& velocity);

    void render() const override;
    bool update(float delta) override;

    bool hit(const Rectangle& rect);
    void die();
};
