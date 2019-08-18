#include "WindowMain.h"
#include "MainMenuWidget.h"
#include "GameMenuWidget.h"
#include "NewGameWidget.h"
#include "RenderWidget.h"
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

    m_CentralWidget = new QStackedWidget(this);
    m_CentralWidget->setMinimumSize(128, 128);
    setCentralWidget(m_CentralWidget);

    InstallCentralWidget(MAIN_MENU, new MainMenuWidget(context_));
    InstallCentralWidget(GAME_MENU, new GameMenuWidget(context_));
    InstallCentralWidget(OPTIONS_MENU, new QWidget());

    RenderWidget* renderWidget = new RenderWidget(context_);

    InstallCentralWidget(NEW_GAME_MENU, new NewGameWidget(context_));
    InstallCentralWidget(RENDER_WIDGET, renderWidget);

    context_->RegisterSubsystem(renderWidget);

    EnableStackWidget(MAIN_MENU);

    context_->RegisterSubsystem(this);

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
