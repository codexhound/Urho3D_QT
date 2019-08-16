#pragma once

#include "ui_MainMenu.h"
#include "WidgetObject.h"

class MainMenuWidget : public WidgetObject
{
    Q_OBJECT
    URHO3D_OBJECT(MainMenuWidget, WidgetObject)
public:
    MainMenuWidget(Context * context, QWidget* parent = nullptr);

    Ui::m_MainMenu ui;

    void OnButtonPress();
};


