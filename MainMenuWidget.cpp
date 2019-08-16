#include "MainMenuWidget.h"
#include "WindowMain.h"

MainMenuWidget::MainMenuWidget(Context* context, QWidget* parent) : WidgetObject(context,parent)
{
    ui.setupUi(this);

    connect(ui.m_StartButton, &QPushButton::clicked, this, &MainMenuWidget::OnButtonPress);
    connect(ui.m_OptionsButton, &QPushButton::clicked, this, &MainMenuWidget::OnButtonPress);
    connect(ui.m_QuitButton, &QPushButton::clicked, this, &MainMenuWidget::OnButtonPress);
}

void MainMenuWidget::OnButtonPress()
{
    if (sender() == ui.m_StartButton) {
        GetSubsystem<WindowMain>()->EnableStackWidget(WindowMain::NEW_GAME_MENU);
    }
    else if (sender() == ui.m_QuitButton) {
        GetSubsystem<WindowMain>()->OnClose();
    }
    else if (sender() == ui.m_OptionsButton) {
        ///
    }
}
