/********************************************************************************
** Form generated from reading UI file 'NewGame.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NEWGAME_H
#define UI_NEWGAME_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_NewGame
{
public:
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_4;
    QVBoxLayout *verticalLayout_3;
    QPushButton *m_backButton;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *verticalSpacer_2;

    void setupUi(QWidget *NewGame)
    {
        if (NewGame->objectName().isEmpty())
            NewGame->setObjectName(QString::fromUtf8("NewGame"));
        NewGame->resize(400, 300);
        verticalLayout = new QVBoxLayout(NewGame);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalSpacer = new QSpacerItem(20, 78, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_4);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        m_backButton = new QPushButton(NewGame);
        m_backButton->setObjectName(QString::fromUtf8("m_backButton"));

        verticalLayout_3->addWidget(m_backButton);


        horizontalLayout_3->addLayout(verticalLayout_3);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);


        verticalLayout->addLayout(horizontalLayout_3);

        verticalSpacer_2 = new QSpacerItem(20, 78, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);


        retranslateUi(NewGame);

        QMetaObject::connectSlotsByName(NewGame);
    } // setupUi

    void retranslateUi(QWidget *NewGame)
    {
        NewGame->setWindowTitle(QCoreApplication::translate("NewGame", "Form", nullptr));
        m_backButton->setText(QCoreApplication::translate("NewGame", "Back", nullptr));
    } // retranslateUi

};

namespace Ui {
    class NewGame: public Ui_NewGame {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEWGAME_H
