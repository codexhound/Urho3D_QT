#pragma once

#include <QtWidgets/QMainWindow>
#include <Urho3D/Core/Object.h>
#include "ui_MainWindow.h"
#include <Urho3D/Container/Str.h>
#include <map>

using namespace Urho3D;

class QStackedWidget;

class WindowMain : public QMainWindow, public Object
{
    Q_OBJECT
    URHO3D_OBJECT(WindowMain, Object)
public:
    static Urho3D::String MAIN_MENU;
    static Urho3D::String GAME_MENU;
    static Urho3D::String OPTIONS_MENU;
    static Urho3D::String NEW_GAME_MENU;
    static Urho3D::String RENDER_WIDGET;

    WindowMain(Urho3D::Context* context);

    QStackedWidget* m_CentralWidget;

    std::map<Urho3D::String, QWidget*> m_StackWidgetMap;
    bool InstallCentralWidget(Urho3D::String sName, QWidget* widget);
    bool RemoveCentralWidget(Urho3D::String sName);
    bool EnableStackWidget(Urho3D::String sName);
    QWidget* GetStackWidget(Urho3D::String sName);

    void HandleUpdate(StringHash eventType, VariantMap& eventData);

    void OnClose();
    void closeEvent(QCloseEvent* event) override;

    Ui::MainWindowClass ui;
private:
    bool m_isClosing;
    bool m_closeEventCalled;
};


