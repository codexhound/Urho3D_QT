/********************************************************************************
** Form generated from reading UI file 'MainMenu.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINMENU_H
#define UI_MAINMENU_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_m_MainMenu
{
public:
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_4;
    QVBoxLayout *verticalLayout_3;
    QPushButton *m_StartButton;
    QPushButton *m_OptionsButton;
    QPushButton *m_QuitButton;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *verticalSpacer_2;

    void setupUi(QWidget *m_MainMenu)
    {
        if (m_MainMenu->objectName().isEmpty())
            m_MainMenu->setObjectName(QString::fromUtf8("m_MainMenu"));
        m_MainMenu->resize(573, 379);
        verticalLayout = new QVBoxLayout(m_MainMenu);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_4);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        m_StartButton = new QPushButton(m_MainMenu);
        m_StartButton->setObjectName(QString::fromUtf8("m_StartButton"));

        verticalLayout_3->addWidget(m_StartButton);

        m_OptionsButton = new QPushButton(m_MainMenu);
        m_OptionsButton->setObjectName(QString::fromUtf8("m_OptionsButton"));

        verticalLayout_3->addWidget(m_OptionsButton);

        m_QuitButton = new QPushButton(m_MainMenu);
        m_QuitButton->setObjectName(QString::fromUtf8("m_QuitButton"));

        verticalLayout_3->addWidget(m_QuitButton);


        horizontalLayout_3->addLayout(verticalLayout_3);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);


        verticalLayout->addLayout(horizontalLayout_3);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);


        retranslateUi(m_MainMenu);

        QMetaObject::connectSlotsByName(m_MainMenu);
    } // setupUi

    void retranslateUi(QWidget *m_MainMenu)
    {
        m_MainMenu->setWindowTitle(QCoreApplication::translate("m_MainMenu", "Main Menu", nullptr));
        m_StartButton->setText(QCoreApplication::translate("m_MainMenu", "New Game", nullptr));
        m_OptionsButton->setText(QCoreApplication::translate("m_MainMenu", "Options", nullptr));
        m_QuitButton->setText(QCoreApplication::translate("m_MainMenu", "Quit", nullptr));
    } // retranslateUi

};

namespace Ui {
    class m_MainMenu: public Ui_m_MainMenu {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINMENU_H
