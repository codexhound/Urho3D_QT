#pragma once

#include <Urho3D/Scene/LogicComponent.h>

class Context;

class RenderObject : public Urho3D::LogicComponent
{
    URHO3D_OBJECT(RenderObject, Urho3D::LogicComponent)

public:
    RenderObject(Urho3D::Context* context);

    void Update(float timeStep) override;
};
