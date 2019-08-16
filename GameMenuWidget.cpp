#include "GameMenuWidget.h"
#include "WindowMain.h"

///////////////////////////////////////////////////////////////////////////////////

GameMenuWidget::GameMenuWidget(Context * context, QWidget* parent) : WidgetObject(context, parent)
{
    ui.setupUi(this);

    connect(ui.m_ResumeButton, &QPushButton::clicked, this, &GameMenuWidget::OnButtonPress);
    connect(ui.m_QuitMenu, &QPushButton::clicked, this, &GameMenuWidget::OnButtonPress);
    connect(ui.m_OSQuit, &QPushButton::clicked, this, &GameMenuWidget::OnButtonPress);
}

///////////////////////////////////////////////////////////////////////////////////

void GameMenuWidget::OnButtonPress()
{
    if (sender() == ui.m_ResumeButton) {

    }
    else if (sender() == ui.m_OSQuit) {

    }
    else if (sender() == ui.m_QuitMenu) {

    }
}

///////////////////////////////////////////////////////////////////////////////////
