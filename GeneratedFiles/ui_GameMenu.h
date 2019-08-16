/********************************************************************************
** Form generated from reading UI file 'GameMenu.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GAMEMENU_H
#define UI_GAMEMENU_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GameMenu
{
public:
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_4;
    QVBoxLayout *verticalLayout_3;
    QPushButton *m_ResumeButton;
    QPushButton *m_QuitMenu;
    QPushButton *m_OSQuit;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *verticalSpacer_2;

    void setupUi(QWidget *GameMenu)
    {
        if (GameMenu->objectName().isEmpty())
            GameMenu->setObjectName(QString::fromUtf8("GameMenu"));
        GameMenu->resize(400, 300);
        verticalLayout = new QVBoxLayout(GameMenu);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalSpacer = new QSpacerItem(20, 78, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_4);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        m_ResumeButton = new QPushButton(GameMenu);
        m_ResumeButton->setObjectName(QString::fromUtf8("m_ResumeButton"));

        verticalLayout_3->addWidget(m_ResumeButton);

        m_QuitMenu = new QPushButton(GameMenu);
        m_QuitMenu->setObjectName(QString::fromUtf8("m_QuitMenu"));

        verticalLayout_3->addWidget(m_QuitMenu);

        m_OSQuit = new QPushButton(GameMenu);
        m_OSQuit->setObjectName(QString::fromUtf8("m_OSQuit"));

        verticalLayout_3->addWidget(m_OSQuit);


        horizontalLayout_3->addLayout(verticalLayout_3);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);


        verticalLayout->addLayout(horizontalLayout_3);

        verticalSpacer_2 = new QSpacerItem(20, 78, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);


        retranslateUi(GameMenu);

        QMetaObject::connectSlotsByName(GameMenu);
    } // setupUi

    void retranslateUi(QWidget *GameMenu)
    {
        GameMenu->setWindowTitle(QCoreApplication::translate("GameMenu", "Form", nullptr));
        m_ResumeButton->setText(QCoreApplication::translate("GameMenu", "Resume", nullptr));
        m_QuitMenu->setText(QCoreApplication::translate("GameMenu", "Quit to Menu", nullptr));
        m_OSQuit->setText(QCoreApplication::translate("GameMenu", "Quit to OS", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GameMenu: public Ui_GameMenu {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAMEMENU_H
