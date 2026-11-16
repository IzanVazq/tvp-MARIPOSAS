#pragma once

#include "GameObject.h"
#include "rectangle.h"
class Game;
class SceneObject : public GameObject
{
protected:
    Rectangle position;
public:
    SceneObject(Game* game, const Rectangle& position);
    virtual ~SceneObject();
    bool hit(const Rectangle& rect) const;
};
