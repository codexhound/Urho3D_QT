#include "RenderWidget.h"
#include "WindowMain.h"
#include "UniQApp.h"
#include <QtWidgets>
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
#include <Urho3D/Scene/Scene.h>
#include <Urho3D/Core/Context.h>

////////////////////////////////////////////////////////////////////

RenderWidget::RenderWidget(Context* context, QWidget* parent) : WidgetObject(context)
{
    m_AppTimer = new QTimer(this);
    m_AppTimer->setInterval(17);

    m_Scene = new Scene(context_);
    setFocusPolicy(Qt::StrongFocus);

    SubscribeToEvent(E_UPDATE, URHO3D_HANDLER(RenderWidget, HandleUpdate));

    InstallShortcut(Qt::Key_W, new KeyDef(Qt::Key_W));
    InstallShortcut(Qt::Key_S, new KeyDef(Qt::Key_S));
    InstallShortcut(Qt::Key_A, new KeyDef(Qt::Key_A));
    InstallShortcut(Qt::Key_D, new KeyDef(Qt::Key_D));
    InstallShortcut(Qt::Key_E, new KeyDef(Qt::Key_E));
    InstallShortcut(Qt::Key_Q, new KeyDef(Qt::Key_Q));
    InstallShortcut(Qt::Key_PageUp, new KeyDef(Qt::Key_PageUp));
    InstallShortcut(Qt::Key_PageDown, new KeyDef(Qt::Key_PageDown));
    InstallShortcut(Qt::Key_Shift, new KeyDef(Qt::Key_Shift));
    InstallShortcut(Qt::Key_Tab, new KeyDef(Qt::Key_Tab));

    m_Pitch = 0;
    m_Yaw = 0;
    m_Roll = 0;

    m_inputOn = true;
    m_InputTimer = new QTimer(this);
    m_InputTimer->setInterval(17);
    m_InputTimer->start();

    m_MoveSpeed = 400.0f / 50.0f;
    m_ShiftSpeedModifier = 30.0f;

    isPitchMode = false;

    connect(m_AppTimer, &QTimer::timeout, this, &RenderWidget::OnRenderInterval);
    connect(m_InputTimer, &QTimer::timeout, this, &RenderWidget::CheckKeyInputs);
}

////////////////////////////////////////////////////////////////////

bool RenderWidget::EnableKeyDef(Qt::Key key, bool en)
{
    bool succ = false;
    auto it = m_ShortcutMap.find(key);
    if (it != m_ShortcutMap.end()) {
        succ = true;
        it->second->m_isDown = en;
    }
    return succ;
}

////////////////////////////////////////////////////////////////////

bool RenderWidget::GetIsDown(Qt::Key key)
{
    bool down = false;
    auto it = m_ShortcutMap.find(key);
    if (it != m_ShortcutMap.end()) {
        if (it->second->m_isDown) {
            down = true;
        }
    }
    return down;
}

////////////////////////////////////////////////////////////////////

bool RenderWidget::event(QEvent* evt) {
    Input* input = GetSubsystem<Input>();
    QKeyEvent* key = (QKeyEvent*)evt;
    Qt::Key keyEnum = (Qt::Key)key->key();
    if (evt->type() == QEvent::KeyPress) {
        if (EnableKeyDef(keyEnum, true)) {
            key->accept();
            return true;
        }
    }
    else if (evt->type() == QEvent::KeyRelease) {
        if (keyEnum == Qt::Key_Tab) {
            isPitchMode = !isPitchMode;
        }
        if (EnableKeyDef(keyEnum, false)) {
            key->accept();
            return true;
        }
    }
    return QWidget::event(evt);
}

////////////////////////////////////////////////////////////////////

void RenderWidget::CheckKeyInputs()
{
    if (m_Scene.NotNull() && m_Camera.NotNull() && m_inputOn) {
        auto it = m_ShortcutMap.begin();
        bool shiftDown = GetIsDown(Qt::Key_Shift);
        float MOVE_SPEED = m_MoveSpeed;
        if (shiftDown) {
            MOVE_SPEED *= m_ShiftSpeedModifier;
        }
        float timeDiff = 0.017f;

        auto camPos = m_Camera->GetNode()->GetPosition();
        Vector3 tryPos = m_Camera->GetNode()->GetPosition();

        auto camXPos = m_Camera->GetNode()->GetPosition().x_;
        auto camYPos = m_Camera->GetNode()->GetPosition().y_;
        auto camZPos = m_Camera->GetNode()->GetPosition().z_;

        Input* input = GetSubsystem<Input>();

        while (it != m_ShortcutMap.end()) {
            if (it->second->m_isDown) {
                auto key = it->second->m_key;

                if (key == Qt::Key_W) {
                    tryPos = camPos + (Vector3(0, 0, 1) * MOVE_SPEED * timeDiff);
                    if (camYPos < 400.0f) {
                        camPos = tryPos;
                        std::cout << m_Camera->GetNode()->GetPosition() << "A" << std::endl;
                    }
                }
                else if (key == Qt::Key_S) {
                    tryPos = camPos + (Vector3(0, 0, -1) * MOVE_SPEED * timeDiff);
                    if (camYPos > -400.0f) {
                        camPos = tryPos;
                        std::cout << m_Camera->GetNode()->GetPosition() << "B" << std::endl;
                    }
                }
                else if (key == Qt::Key_A) {
                    tryPos = camPos + (Vector3(-1, 0, 0) * MOVE_SPEED * timeDiff);
                    if (camXPos > -400.0f) {
                        camPos = tryPos;
                        std::cout << m_Camera->GetNode()->GetPosition() << "C" << std::endl;
                    }
                }
                else if (key == Qt::Key_D) {
                    tryPos = camPos + (Vector3(1, 0, 0) * MOVE_SPEED * timeDiff);
                    if (camXPos < 400.0f) {
                        camPos = tryPos;
                        std::cout << m_Camera->GetNode()->GetPosition() << "D" << std::endl;
                    }
                }
                else if (key == Qt::Key_PageDown) {
                    tryPos = camPos + (Vector3(0, -1, 0) * MOVE_SPEED * timeDiff);
                    if (camZPos > -400.0f) {
                        camPos = tryPos;
                        std::cout << m_Camera->GetNode()->GetPosition() << "E" << std::endl;
                    }
                }
                else if (key == Qt::Key_PageUp) {
                    tryPos = camPos + (Vector3(0, 1, 0) * MOVE_SPEED * timeDiff);
                    if (camZPos < 400.0f) {
                        camPos = tryPos;
                        std::cout << m_Camera->GetNode()->GetPosition() << "F" << std::endl;
                    }
                }
                else if (key == Qt::Key_Q) {
                    if (isPitchMode || input->GetMouseButtonDown(MOUSEB_RIGHT))
                    {
                        m_Roll += -MOVE_SPEED * timeDiff;
                        UpdatePitchRoll();
                    }
                }
                else if (key == Qt::Key_E) {
                    if (isPitchMode || input->GetMouseButtonDown(MOUSEB_RIGHT))
                    {
                        m_Roll += MOVE_SPEED * timeDiff;
                        UpdatePitchRoll();
                    }
                }
            }
            it++;
        }
        m_Camera->GetNode()->SetPosition(camPos);
    }
    m_InputTimer->start();
}

////////////////////////////////////////////////////////////////////

RenderWidget::KeyDef * RenderWidget::GetShortcut(Qt::Key key)
{
    KeyDef* def = nullptr;
    auto it = m_ShortcutMap.find(key);
    if (it != m_ShortcutMap.end()) {
        def = it->second.get();
    }
    return def;
}

////////////////////////////////////////////////////////////////////

bool RenderWidget::InstallShortcut(Qt::Key key, KeyDef * shortcut)
{
    bool succ = false;
    auto it = m_ShortcutMap.find(key);
    if (it == m_ShortcutMap.end()) {
        succ = true;
        m_ShortcutMap[key] = std::shared_ptr<KeyDef>(shortcut);
    }
    return succ;
}

////////////////////////////////////////////////////////////////////

void RenderWidget::CreateScene()
{
    ResourceCache* cache = GetSubsystem<ResourceCache>();
    m_Scene->CreateComponent<Octree>();

    Zone* zone{ m_Scene->CreateComponent<Zone>() };

    //Skybox
    Node* skybox{ m_Scene->CreateChild() };
    skybox->SetScale(400.0f);
    Skybox* skyBox = skybox->CreateComponent<Skybox>();
    skyBox->SetModel(cache->GetResource<Model>("Models/Box.mdl"));
    skyBox->SetMaterial(cache->GetResource<Material>("Materials/Skybox1.xml"));
    skybox->SetEnabled(true);

    //Light
    Node* lightNode{ m_Scene->CreateChild("Light") };
    lightNode->SetPosition(Vector3(0, 300.0f, 0));
    Light* light{ lightNode->CreateComponent<Light>() };
    light->SetDrawDistance(400.0f);
    light->SetRadius(23.0f);

    //Camera
    Node* cameraNode{ m_Scene->CreateChild("Camera") };
    cameraNode->SetPosition(Vector3(0.0f, 300.0f, 0.0f));
    cameraNode->LookAt(Vector3::ZERO);
    m_Camera = cameraNode->CreateComponent<Camera>();
    m_Camera->SetFov(23.0f);

    StartScene();
}

////////////////////////////////////////////////////////////////////

void RenderWidget::StartScene()
{
    //Scene
    Node* sceneNode{ m_Scene->CreateChild("Scene") };
    StaticModel* model = sceneNode->CreateComponent<StaticModel>();
    ResourceCache* cache = GetSubsystem<ResourceCache>();
    model->SetModel(cache->GetResource<Model>("Models/Box.mdl"));
    model->SetMaterial(cache->GetResource<Material>("Materials/NoTextureAdd.xml"));

    Renderer* renderer = GetSubsystem<Renderer>();
    Urho3D::SharedPtr<Viewport> viewport(new Viewport(context_, m_Scene, m_Camera));
    renderer->SetViewport(0, viewport);

    GetSubsystem<WindowMain>()->EnableStackWidget(WindowMain::RENDER_WIDGET);
    activateWindow();

    RunFrame();

    m_AppTimer->start();
}

////////////////////////////////////////////////////////////////////

void RenderWidget::RunFrame()
{
    GetSubsystem<Engine>()->RunFrame();
}

////////////////////////////////////////////////////////////////////

void RenderWidget::OnRenderInterval()
{
    RunFrame();
}

////////////////////////////////////////////////////////////////////

void RenderWidget::HandleUpdate(StringHash eventType, VariantMap& eventData)
{
    if (m_Scene.NotNull() && m_Camera.NotNull() && m_inputOn) {
        float timeStep = eventData[Update::P_TIMESTEP].GetFloat();
        Input* input = GetSubsystem<Input>();
        // Movement speed as world units per second
        float MOVE_SPEED = m_MoveSpeed;

        auto camXPos = m_Camera->GetNode()->GetPosition().x_;
        auto camYPos = m_Camera->GetNode()->GetPosition().y_;
        auto camZPos = m_Camera->GetNode()->GetPosition().z_;

        if (GetIsDown(Qt::Key_Shift))
            MOVE_SPEED *= m_ShiftSpeedModifier;

        auto camPos = m_Camera->GetNode()->GetPosition();
        Vector3 tryPos = m_Camera->GetNode()->GetPosition();

        auto delta = input->GetMouseMoveWheel();
        tryPos = camPos + (Vector3(0, -1, 0) * MOVE_SPEED * delta * 20.0f * timeStep);
        if (tryPos.y_ > -400 && tryPos.y_ < 400) {
            camPos = tryPos; //keep position
        }

        auto mousePos = GetSubsystem<Input>()->GetMousePosition();
        auto xMax = GetSubsystem<Graphics>()->GetWidth();
        auto yMax = GetSubsystem<Graphics>()->GetHeight();
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

        m_Camera->GetNode()->SetPosition(camPos);

        // Mouse sensitivity as degrees per pixel
        const float MOUSE_SENSITIVITY = 0.1f;
        if (isPitchMode || input->GetMouseButtonDown(MOUSEB_RIGHT))
        {
            // Use this frame's mouse motion to adjust camera node yaw and pitch. Clamp the pitch between -90 and 90 degrees
            IntVector2 mouseMove = input->GetMouseMove();
            m_Yaw += MOUSE_SENSITIVITY * mouseMove.x_;
            m_Pitch += MOUSE_SENSITIVITY * mouseMove.y_;
            m_Yaw = Clamp(m_Yaw, -60.0f, 60.0f);
            m_Pitch = Clamp(m_Pitch, -60.0f, 60.0f);
            
            UpdatePitchRoll();
        }
        else {
            ResetPitchRoll();
        }
    }
}

////////////////////////////////////////////////////////////////////

void RenderWidget::UpdatePitchRoll()
{
    m_Camera->GetNode()->SetDirection(Vector3::DOWN);
    m_Camera->GetNode()->Yaw(m_Yaw);
    m_Camera->GetNode()->Pitch(m_Pitch);
    m_Camera->GetNode()->Roll(m_Roll);
}

////////////////////////////////////////////////////////////////////

void RenderWidget::ResetPitchRoll()
{
    m_Yaw = 0;
    m_Roll = 0;
    m_Pitch = 0;

    UpdatePitchRoll();
}

////////////////////////////////////////////////////////////////////


bool RenderWidget::MouseRaycast(float maxDistance, Vector3& hitPos, Drawable*& hitDrawable)
{
    hitDrawable = 0;

    UI* ui = GetSubsystem<UI>();
    IntVector2 pos = ui->GetCursorPosition();
    Input* input = GetSubsystem<Input>();
    // Check the cursor is visible and there is no UI element in front of the cursor
    if (!input->IsMouseVisible() || ui->GetElementAt(pos, true))
        return false;

    Graphics* graphics = GetSubsystem<Graphics>();
    Ray cameraRay = m_Camera->GetScreenRay((float)pos.x_ / (float)graphics->GetWidth(), 
        (float)pos.y_ / (float)graphics->GetHeight());
    // Pick only geometry objects, not eg. zones or lights, only get the first (closest) hit
    PODVector<RayQueryResult> results;
    RayOctreeQuery query(results, cameraRay, RAY_TRIANGLE, maxDistance, DRAWABLE_GEOMETRY);
    m_Scene->GetComponent<Octree>()->Raycast(query);
    if (results.Size())
    {
        for (int i = 0; i < results.Size(); i++) {
            //find models in the ray results, don't want anything else for now
            RayQueryResult& result = results[i];
            Drawable* currentDrawable = result.drawable_;
            StaticModel* model = dynamic_cast<StaticModel*>(currentDrawable);
            if (model != nullptr) {
                hitPos = result.position_;
                hitDrawable = result.drawable_;
                return true;
            }
        }
    }

    return false;
}
