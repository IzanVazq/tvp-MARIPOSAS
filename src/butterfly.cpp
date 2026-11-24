#include "butterfly.h"
#include "game.h"

#include <random>

Butterfly::Butterfly(Texture* textura, Game* game,
    const Rectangle& position, const Vector2D<>& velocity)
    : MobileObject(game, position, velocity),
    textura(textura)
{
}

void Butterfly::render() const
{
    SDL_FRect destination = position.to_sdl();

    textura->renderFrame(destination, 0, activeFrame);
}

bool Butterfly::update(float delta)
{
    if (dead)
    {
        velocity = Vector2D<>(0, 150);
        MobileObject::update(delta);

        return position.getTopLeftCorner().getY()
            < Game::WINDOW_HEIGHT;
    }

    directionTimer += delta;

    if (directionTimer >= directionInterval)
    {
        directionTimer = 0;

        static std::random_device rd;
        static std::mt19937 gen(rd());
        static std::uniform_real_distribution<float> dist(-100, 100);

        velocity = Vector2D<>(dist(gen), dist(gen));
    }

    MobileObject::update(delta);

    float x = position.getTopLeftCorner().getX();
    float y = position.getTopLeftCorner().getY();

    if (x <= 0 || x + position.getWidth() >= Game::WINDOW_WIDTH)
        velocity = Vector2D<>(-velocity.getX(), velocity.getY());

    if (y <= 0 || y + position.getHeight() >= Game::WINDOW_HEIGHT)
        velocity = Vector2D<>(velocity.getX(), -velocity.getY());

    //Animacion
    animTime += delta;

    if (animTime >= frameTime)
    {
        animTime = 0.0f;
        activeFrame++;

        if (activeFrame >= 10)
            activeFrame = 0;
    }

    return true;
}

bool Butterfly::hit(const Rectangle& rect)
{
    if (dead)
        return false;

    if (SceneObject::hit(rect))
    {
        die();
        return true;
    }

    return false;
}

void Butterfly::die()
{
    dead = true;
}
