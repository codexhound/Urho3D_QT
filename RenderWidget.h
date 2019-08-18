#pragma once

#include "WidgetObject.h"
#include <Urho3D/Graphics/Drawable.h>

class QTimer;

class RenderWidget : public WidgetObject
{
    Q_OBJECT
    URHO3D_OBJECT(RenderWidget, WidgetObject)
public:
    RenderWidget(Context* context, QWidget * parent = nullptr);

    class KeyDef
    {
    public:
        KeyDef(Qt::Key key) {
            m_isDown = false;
            m_key = key;
        }
        KeyDef() {
            m_isDown = false;
            m_key = Qt::Key_W;
        }
        bool m_isDown;
        Qt::Key m_key;
    };

    void CreateScene();
    void StartScene();
    void RunFrame();
    void OnRenderInterval();
    void HandleUpdate(StringHash eventType, VariantMap& eventData);
    bool MouseRaycast(float maxDistance, Vector3& hitPos, Drawable*& hitDrawable);

    Scene* GetScene() { return m_Scene.Get(); }
    Camera* GetCamera() { return m_Camera.Get(); }

    QTimer* m_InputTimer;

    std::map<Qt::Key, std::shared_ptr<KeyDef> > m_ShortcutMap;
    bool InstallShortcut(Qt::Key key, KeyDef *);
    KeyDef * GetShortcut(Qt::Key key);
    bool EnableKeyDef(Qt::Key key, bool en);
    bool event(QEvent* evt) override;
    bool GetIsDown(Qt::Key key);
    void UpdatePitchRoll();
    void ResetPitchRoll();
    bool isPitchMode;

    float m_Pitch;
    float m_Yaw;
    float m_Roll;

    bool m_inputOn;
    float m_MoveSpeed;
    float m_ShiftSpeedModifier;

public slots:
    void CheckKeyInputs();

private:
    SharedPtr<Scene> m_Scene;
    SharedPtr<Camera> m_Camera;
    QTimer* m_AppTimer;
};
