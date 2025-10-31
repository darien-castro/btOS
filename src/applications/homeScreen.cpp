//
// Created by pablovepo on 10/26/25.
//

#include "homeScreen.h"

#include "notesScreen.h"
#include "src/core/btShell.h"
#include "src/core/screenManager.h"

void homeScreen::appButtonPressed(btApplication* app){
    app->btAPP_SETUP();
    this->mainShell->returnScreenManager()->addWidget(app->btAPP_RETURN());
    this->mainShell->returnScreenManager()->returnStack()->setCurrentWidget(app->btAPP_RETURN());
    qDebug() << "app location at creation: " << app->btAPP_RETURN();
}

void homeScreen::screenAppsSetup(QVBoxLayout* scrollArea){
    std::vector<btApplication*> apps = mainShell->returnState()->returnAppVect();
    for (int i = 0; i < apps.size(); i++)
    {
        QPushButton* curr = new QPushButton(apps[i]->appName);
        scrollArea->addWidget(curr);
        buttonStyle(curr);
        QObject::connect(curr, &QPushButton::clicked, [this, apps, i]{
        appButtonPressed(apps[i]);
    });
    }

}


void homeScreen::buttonStyle(QWidget* button){
    button->setStyleSheet("QPushButton{"
                         "color: #000000;"
                         "background-color: rgba(135, 133, 128,15);"
                         "width: 100px;"
                         "height: 30px;"
                         "border-radius: 6px;"
                         ""
                         "}"
                         "QPushButton:hover{"
                         "background: rgba(207,212,198,100);"
                         "border: none;"
                         ""
                         ""
                         "}"
                         "QPushButton:hover:pressed {"
                        "background-color: rgba(207,212,198,40);"
                        "color: #FF0000;"
                        "}");
}


homeScreen::homeScreen(btShell* shell){
    mainShell = shell;

    setAccessibleName("homescreen");

    //toDo need button for applications, and way to print them on homescreen
    //toDo from some application list, for now, just buttons to set connections


    /*QPushButton* phone = new QPushButton("Phone");
    buttonStyle(phone);
    QPushButton* notes = new QPushButton("Notes");
    buttonStyle(notes);
    QPushButton* text = new QPushButton("Message");
    buttonStyle(text);
    QPushButton* manga = new QPushButton("Manga");
    buttonStyle(manga);
    */


    QWidget* content = new QWidget;
    QVBoxLayout* homeScreenLayout = new QVBoxLayout(content);
    homeScreenLayout->setObjectName("homeScreen");
    homeScreenLayout->setSpacing(1);
    homeScreenLayout->setContentsMargins(4,2,4,2);
    QScrollArea* scrollareaMain = new QScrollArea;
    scrollareaMain->setWidgetResizable(true);

    screenAppsSetup(homeScreenLayout);
    scrollareaMain->setWidget(content);

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(scrollareaMain);


    setLayout(mainLayout);
    setObjectName("homeScreen");
    setStyleSheet("QWidget#homeScreen{"
                  "background-color: rgba(0,0,0,0)"
                  "}");
}

QWidget* homeScreen::returnHomeScreen(){
    return this;
}

