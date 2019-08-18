#include "NewGameWidget.h"
#include "WindowMain.h"
#include "RenderWidget.h"

NewGameWidget::NewGameWidget(Context* context, QWidget* parent) : WidgetObject(context, parent)
{
    ui.setupUi(this);

    connect(ui.m_backButton, &QPushButton::clicked, this, &NewGameWidget::OnButtonPress);
    connect(ui.m_startButton, &QPushButton::clicked, this, &NewGameWidget::OnButtonPress);
}

void NewGameWidget::OnButtonPress()
{
    if (sender() == ui.m_backButton) {
        GetSubsystem<WindowMain>()->EnableStackWidget(WindowMain::MAIN_MENU);
    }
    else if (sender() == ui.m_startButton) {
        GetSubsystem<RenderWidget>()->CreateScene();
    }
}
