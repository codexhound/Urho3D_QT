#pragma once

#include "ui_NewGame.h"
#include "WidgetObject.h"

class NewGameWidget : public WidgetObject
{
    Q_OBJECT
    URHO3D_OBJECT(NewGameWidget, WidgetObject)
public:
    NewGameWidget(Context* context, QWidget* parent = nullptr);

    Ui::NewGame ui;

    void OnButtonPress();
};


