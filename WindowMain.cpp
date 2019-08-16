#include "WindowMain.h"
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
#include "MainMenuWidget.h"
#include "GameMenuWidget.h"
#include "NewGameWidget.h"
#include <QPainter>
#include <QtWidgets>
#include "UniQApp.h"
#include <Urho3D/Core/Context.h>

///////////////////////////////////////////////////////////////////////////

Urho3D::String WindowMain::MAIN_MENU = "MAIN_MENU";
Urho3D::String WindowMain::GAME_MENU = "GAME_MENU";
Urho3D::String WindowMain::OPTIONS_MENU = "OPTIONS_MENU";
Urho3D::String WindowMain::NEW_GAME_MENU = "NEWGAME_MENU";
Urho3D::String WindowMain::RENDER_WIDGET = "RENDER_WIDGET";

///////////////////////////////////////////////////////////////////////////

WindowMain::WindowMain(Urho3D::Context* context) : Object(context), QMainWindow(nullptr, Qt::Window)
{
    ui.setupUi(this);

    m_isClosing = false;
    m_closeEventCalled = false;

    m_AppTimer = new QTimer(this);
    m_AppTimer->setInterval(17);

    m_CentralWidget = new QStackedWidget(this);
    m_CentralWidget->setMinimumSize(128, 128);
    setCentralWidget(m_CentralWidget);

    InstallCentralWidget(MAIN_MENU, new MainMenuWidget(context_));
    InstallCentralWidget(GAME_MENU, new GameMenuWidget(context_));
    InstallCentralWidget(OPTIONS_MENU, new QWidget());
    InstallCentralWidget(NEW_GAME_MENU, new NewGameWidget(context_));
    InstallCentralWidget(RENDER_WIDGET, new QWidget());
    EnableStackWidget(MAIN_MENU);

    m_Scene = new Scene(context_);

    context_->RegisterSubsystem(this);

    connect(m_AppTimer, &QTimer::timeout, this, &WindowMain::OnRenderInterval);

    showMaximized();
}

///////////////////////////////////////////////////////////////////////////

QWidget* WindowMain::GetStackWidget(Urho3D::String sName)
{
    QWidget* widget = nullptr;
    auto it = m_StackWidgetMap.find(sName);
    if (it != m_StackWidgetMap.end()) {
        widget = it->second;
    }
    return widget;
}

///////////////////////////////////////////////////////////////////////////

void WindowMain::closeEvent(QCloseEvent* event)
{
    m_closeEventCalled = true;
    if (!m_isClosing) {
        OnClose();
    }
    QMainWindow::closeEvent(event);
}

///////////////////////////////////////////////////////////////////////////

void WindowMain::OnClose() 
{
    if (!m_isClosing) {
        m_isClosing = true;
        GetSubsystem<UniQApp>()->Close();
        if (!m_closeEventCalled)
            close();
    }
}

///////////////////////////////////////////////////////////////////////////

void WindowMain::OnRenderInterval()
{
    RunFrame();
}

///////////////////////////////////////////////////////////////////////////

void WindowMain::RunFrame()
{
    GetSubsystem<UniQApp>()->RunFrame();
}

///////////////////////////////////////////////////////////////////////////

bool WindowMain::EnableStackWidget(Urho3D::String sName)
{
    bool succ = false;
    auto it = m_StackWidgetMap.find(sName);
    if (it != m_StackWidgetMap.end()) {
        succ = true;
        m_CentralWidget->setCurrentWidget(it->second);
    }
    return succ;
}

///////////////////////////////////////////////////////////////////////////

bool WindowMain::RemoveCentralWidget(Urho3D::String sName)
{
    bool succ = false;
    auto it = m_StackWidgetMap.find(sName);
    if (it != m_StackWidgetMap.end()) {
        succ = true;
        m_CentralWidget->removeWidget(it->second);
        m_StackWidgetMap.erase(it);
    }
    return succ;
}

///////////////////////////////////////////////////////////////////////////

bool WindowMain::InstallCentralWidget(Urho3D::String sName, QWidget* widget)
{
    bool succ = false;
    if (widget != nullptr) {
        auto it = m_StackWidgetMap.find(sName);
        if (it == m_StackWidgetMap.end()) {
            succ = true;
            m_StackWidgetMap[sName] = widget;
            m_CentralWidget->addWidget(widget);
        }
    }
    return succ;
}

///////////////////////////////////////////////////////////////////////////

void WindowMain::CreateScene()
{
    m_Scene->CreateComponent<Octree>();

    Zone* zone{ m_Scene->CreateComponent<Zone>() };
    zone->SetAmbientColor(Color(0.055f, 0.17f, 0.23f));
    zone->SetBoundingBox(BoundingBox(Vector3::ONE * -23.0f, Vector3::ONE * 23.0f));

    //Light
    Node* lightNode{ m_Scene->CreateChild("Light") };
    lightNode->SetPosition(Vector3(-2.0f, 3.0f, -0.23f));
    Light* light{ lightNode->CreateComponent<Light>() };
    light->SetDrawDistance(23.0f);
    light->SetRadius(23.0f);

    //Camera
    Node* cameraNode{ m_Scene->CreateChild("Camera") };
    cameraNode->SetPosition(Vector3(0.0f, 0.0f, -12.0f));
    cameraNode->LookAt(Vector3::ZERO);
    m_Camera = cameraNode->CreateComponent<Camera>();
    m_Camera->SetFov(23.0f);

    //Scene
    Node* sceneNode{ m_Scene->CreateChild("Scene") };
    StaticModel * model = sceneNode->CreateComponent<StaticModel>();
    ResourceCache* cache = GetSubsystem<ResourceCache>();
    model->SetModel(cache->GetResource<Model>("Models/Box.mdl"));
    model->SetMaterial(cache->GetResource<Material>("Materials/NoTextureAdd.xml"));

    StartScene();
}

///////////////////////////////////////////////////////////////////////////

void WindowMain::StartScene()
{
    Renderer* renderer = GetSubsystem<Renderer>();
    Urho3D::SharedPtr<Viewport> viewport(new Viewport(context_, m_Scene, m_Camera));
    renderer->SetViewport(0, viewport);

    RunFrame();

    m_AppTimer->start();
}

///////////////////////////////////////////////////////////////////////////
