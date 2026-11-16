#include "MobileObject.h"

MobileObject::MobileObject(Game* game, const Rectangle& position, const Vector2D<>& velocity)
    : SceneObject(game, position) {
    this->velocity = velocity;
}

MobileObject::~MobileObject() {
}

bool MobileObject::update(float delta) {
    position.move(velocity * delta);
    return true;
}
