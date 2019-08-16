#pragma once

#include <Urho3D/Core/Object.h>
#include <QApplication>
#include <Urho3D/Engine/Engine.h>
#include <Urho3D/Container/Ptr.h>

class WindowMain;

using namespace Urho3D;

class UniQApp : public QApplication, public Object
{
    Q_OBJECT
    URHO3D_OBJECT(UniQApp, Object)
public:
    UniQApp(Context* context, int& argc, char** argv);

    int Run();
    void RunFrame();
    void Close();

private:
    SharedPtr<WindowMain> m_MainWindow;
    SharedPtr<Urho3D::Engine> m_Engine;
};
