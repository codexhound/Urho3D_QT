#pragma once

#include <qwidget.h>
#include <Urho3D/Core/Object.h>

using namespace Urho3D;

class WidgetObject : public QWidget, public Object
{
    Q_OBJECT
    URHO3D_OBJECT(WidgetObject, Object)
    public:
        WidgetObject(Urho3D::Context * context, QWidget* parent = nullptr);

};
