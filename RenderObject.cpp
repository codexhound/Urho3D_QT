#include "RenderObject.h"
#include <Urho3D/Graphics/Graphics.h>
#include <Urho3D/Graphics/Octree.h>
#include <Urho3D/Graphics/Zone.h>
#include <Urho3D/Graphics/Light.h>
#include <Urho3D/Graphics/Camera.h>
#include <Urho3D/Graphics/GraphicsEvents.h>
#include <Urho3D/Graphics/StaticModel.h>
#include <Urho3D/Resource/ResourceCache.h>
#include <Urho3D/Graphics/Model.h>
#include <Urho3D/Resource/Resource.h>
#include <Urho3D/Graphics/Material.h>
#include <Urho3D/Core/CoreEvents.h>
#include <Urho3D/Graphics/Renderer.h>
#include <Urho3D/Graphics/Skybox.h>
#include <Urho3D/UI/UI.h>
#include <Urho3D/Input/Input.h>
#include "RenderWidget.h"

RenderObject::RenderObject(Urho3D::Context* context) : Urho3D::LogicComponent(context)
{

}

void RenderObject::Update(float timeStep)
{
    RenderWidget* renderWidget = GetSubsystem<RenderWidget>();
    Scene* scene = renderWidget->GetScene();
    Camera* camera = renderWidget->GetCamera();
    using namespace Update;
    if (scene != nullptr && camera != nullptr) {
        

        // Movement speed as world units per second
        float MOVE_SPEED = 400 / 50;
        // Mouse sensitivity as degrees per pixel
        const float MOUSE_SENSITIVITY = 0.1f;

        auto camXPos = camera->GetNode()->GetPosition().x_;
        auto camYPos = camera->GetNode()->GetPosition().y_;
        auto camZPos = camera->GetNode()->GetPosition().z_;

        Input* input = GetSubsystem<Input>();

        if (input->GetKeyDown(KEY_SHIFT))
            MOVE_SPEED *= 30;

        auto camPos = camera->GetNode()->GetPosition();
        Vector3 tryPos = camera->GetNode()->GetPosition();

        auto delta = input->GetMouseMoveWheel();
        tryPos = camPos + (Vector3(0, -1, 0) * MOVE_SPEED * delta * 20.0f * timeStep);
        if (tryPos.y_ > -400 && tryPos.y_ < 400) {
            camPos = tryPos; //keep position
        }

        if (input->GetKeyDown(KEY_W)) {
            std::cout << input->GetKeyDown(KEY_W) << std::endl;
        }


        if (input->GetKeyDown(KEY_PAGEUP)) {
            tryPos = camPos + (Vector3(0, 1, 0) * MOVE_SPEED * timeStep);
            if (tryPos.y_ < 400) {
                camPos = tryPos;
            }
        }
        else if (input->GetKeyDown(KEY_PAGEDOWN)) {
            tryPos = camPos + (Vector3(0, -1, 0) * MOVE_SPEED * timeStep);
            if (tryPos.y_ > -400) {
                camPos = tryPos;
            }
        }

        if (input->GetKeyDown(KEY_W)) {
            tryPos = camPos + (Vector3(0, 0, 1) * MOVE_SPEED * timeStep);
            if (tryPos.z_ < 400) {
                camPos = tryPos;
            }
        }
        else if (input->GetKeyDown(KEY_S)) {
            tryPos = camPos + (Vector3(0, 0, -1) * MOVE_SPEED * timeStep);
            if (tryPos.z_ > -400) {
                camPos = tryPos;
            }
        }
        if (input->GetKeyDown(KEY_A)) {
            tryPos = camPos + (Vector3(-1, 0, 0) * MOVE_SPEED * timeStep);
            if (tryPos.x_ > -400) {
                camPos = tryPos;
            }
        }
        else if (input->GetKeyDown(KEY_D)) {
            tryPos = camPos + (Vector3(1, 0, 0) * MOVE_SPEED * timeStep);
            if (tryPos.x_ < 400) {
                camPos = tryPos;
            }
        }

        auto mousePos = GetSubsystem<Input>()->GetMousePosition();
        auto xMax = renderWidget->height();
        auto yMax = renderWidget->width();
        auto xPos = mousePos.x_;
        auto yPos = mousePos.y_;

        if (xPos >= xMax - 1 || xPos <= 0 ||
            yPos >= yMax - 1 || yPos <= 0)
        {
            if (xPos >= xMax - 1) {
                tryPos = camPos + (Vector3(1, 0, 0) * MOVE_SPEED * timeStep);
                if (tryPos.x_ < 400) {
                    camPos = tryPos;
                }
            }
            if (xPos <= 0) {
                tryPos = camPos + (Vector3(-1, 0, 0) * MOVE_SPEED * timeStep);
                if (tryPos.x_ > -400) {
                    camPos = tryPos;
                }
            }
            if (yPos >= yMax - 1) {
                tryPos = camPos + (Vector3(0, 0, -1) * MOVE_SPEED * timeStep);
                if (tryPos.z_ < 400) {
                    camPos = tryPos;
                }
            }
            if (yPos <= 0) {
                tryPos = camPos + (Vector3(0, 0, 1) * MOVE_SPEED * timeStep);
                if (tryPos.z_ > -400) {
                    camPos = tryPos;
                }
            }
        }

        camera->GetNode()->SetPosition(camPos);

        static float yaw_ = 0;
        static float pitch_ = 0;
        if (!input->IsMouseVisible() || input->GetMouseButtonDown(MOUSEB_MIDDLE))
        {
            // Use this frame's mouse motion to adjust camera node yaw and pitch. Clamp the pitch between -90 and 90 degrees
            IntVector2 mouseMove = input->GetMouseMove();
            yaw_ += MOUSE_SENSITIVITY * mouseMove.x_;
            yaw_ = Clamp(yaw_, -60.0f, 60.0f);
            pitch_ += MOUSE_SENSITIVITY * mouseMove.y_;
            pitch_ = Clamp(pitch_, -60.0f, 60.0f);
            camera->GetNode()->SetDirection(Vector3::DOWN);
            camera->GetNode()->Yaw(yaw_);
            camera->GetNode()->Pitch(pitch_);
        }
        else {
            camera->GetNode()->SetDirection(Vector3::DOWN);
            yaw_ = 0;
            pitch_ = 0;
        }
    }
}
