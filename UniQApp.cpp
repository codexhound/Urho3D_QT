#include "UniQApp.h"
#include "WindowMain.h"
#include <Urho3D/Resource/ResourceCache.h>
#include <Urho3D/Engine/EngineDefs.h>
#include <Urho3D/Core/Context.h>
#include <QWidget>

////////////////////////////////////////////////////////////////////////////////////

UniQApp::UniQApp(Context* context, int& argc, char** argv) : Object(context), QApplication(argc, argv)
{
    m_MainWindow = new WindowMain(context);
    m_Engine = new Urho3D::Engine(context);
}

////////////////////////////////////////////////////////////////////////////////////

void UniQApp::RunFrame()
{
    m_Engine->RunFrame();
}

////////////////////////////////////////////////////////////////////////////////////

int UniQApp::Run()
{
    QWidget* renderWidget = m_MainWindow->GetStackWidget(WindowMain::RENDER_WIDGET);
    if (renderWidget == nullptr) {
        return -1;
    }
    else {
        VariantMap engineParameters;
        engineParameters["LogName"] = "Uni.log";
        engineParameters["ExternalWindow"] = (void*)(renderWidget->winId());
        if (!m_Engine->Initialize(engineParameters))
            return -1;

        context_->RegisterSubsystem(this);
        context_->RegisterSubsystem(m_Engine);

        return QApplication::exec();
    }
}

////////////////////////////////////////////////////////////////////////////////////

void UniQApp::Close()
{
    if (m_Engine != nullptr) {
        m_Engine->Exit();
    }
}

////////////////////////////////////////////////////////////////////////////////////

