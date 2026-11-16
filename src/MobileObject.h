#pragma once

#include "SceneObject.h"
#include "vector2D.h"

class MobileObject : public SceneObject
{
protected:
    Vector2D<> velocity;
public:
    MobileObject(Game* game, const Rectangle& position, const Vector2D<>& velocity);
    virtual ~MobileObject();
    bool update(float delta) override;
};
