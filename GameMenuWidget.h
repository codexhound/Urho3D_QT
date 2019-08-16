#pragma once

#include "ui_GameMenu.h"
#include "WidgetObject.h"

class GameMenuWidget : public WidgetObject
{
    Q_OBJECT
    URHO3D_OBJECT(GameMenuWidget, WidgetObject)
public:
    GameMenuWidget(Context * context, QWidget* parent = nullptr);

    Ui::GameMenu ui;

public slots:
    void OnButtonPress();
};
