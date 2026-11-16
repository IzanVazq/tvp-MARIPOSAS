#include "SceneObject.h"

SceneObject::SceneObject(Game* game, const Rectangle& position)
    : GameObject(game) {
    this->position = position;
}

SceneObject::~SceneObject() {
}

bool SceneObject::hit(const Rectangle& rect) const {
    return position.hasIntersection(rect);
}
