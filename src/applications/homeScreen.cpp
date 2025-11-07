//
// Created by pablovepo on 10/26/25.
//

#include "homeScreen.h"

#include "notesScreen.h"
#include "src/core/btShell.h"
#include "src/core/screenManager.h"

//function for
void homeScreen::appButtonPressed(btApplication* app){
    app->btAPP_SETUP();
    this->mainShell->returnScreenManager()->addWidget(app->btAPP_RETURN());
    this->mainShell->returnScreenManager()->returnStack()->setCurrentWidget(app->btAPP_RETURN());
}

//although we may have many applications, the homescreen should only display the ones the user wants, function grabs a
//vector of all variables (within the btState) and looks through config settings to see if "onScreen" bool is true, then places them if so.
void homeScreen::screenAppsSetup(QVBoxLayout* scrollArea){

    //-----------------------------------------------------------------------------------------------
    //font settings for homescreen widgets

    int id = QFontDatabase::addApplicationFont("../resources/fonts/MapleMono-TTF/MapleMono-SemiBoldItalic.ttf");

    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont nerdFont (family);
    nerdFont.bold();
    nerdFont.setPointSize(24);
    //----------------------------------------------------------------------------------------------


    std::vector<btApplication*> apps = mainShell->returnState()->returnAppVect();
    QJsonArray tempAppArr = mainShell->returnState()->returnJsonAppArray();
    for (int i = 0; i < apps.size(); i++){
        for (int j = 0; j < tempAppArr.size(); j++) {
            QJsonValue value = tempAppArr.at(j);
            QJsonObject obj = value.toObject();
            QString name = obj["base_object_name"].toString();
            bool question = (name == apps[i]->objectName());
            bool onHome = obj["on_home_screen"].toBool();
            if (apps[i]->objectName() == name && onHome == true){
                QPushButton* curr = new QPushButton(apps[i]->appName);
                onScreenButtons.push_back(curr);
                curr->setFocusPolicy(Qt::StrongFocus);
                curr->setFixedWidth(200);
                curr->setFixedHeight(45);
                curr->setFont(nerdFont);
                scrollArea->addWidget(curr,0,Qt::AlignCenter);
                buttonStyle(curr);
                QObject::connect(curr, &QPushButton::clicked, [this, apps, i]{
                appButtonPressed(apps[i]);
            });
        }
    };
    }

}

// helper function for button styling in for loop
void homeScreen::buttonStyle(QWidget* button){
    button->setStyleSheet("QPushButton{"
                         "font-size: 22px;"
                         "width: 50px;"
                         "height: 30px;"
                         "border-radius: 8px;"
                         ""
                         "}"
                         "QPushButton:focus {"
                         "border: none;"
                         ""
                         ""
                         "}"
                         "QPushButton:hover:pressed {"
                        "color: #273749;"
                        "}");
}


homeScreen::homeScreen(btShell* shell){
    mainShell = shell;

    setAccessibleName("homescreen");


    QWidget* content = new QWidget;
    QVBoxLayout* homeScreenLayout = new QVBoxLayout(content);
    homeScreenLayout->setObjectName("homeScreen");

    //------------------------------
    homeScreenLayout->setSpacing(1);
    homeScreenLayout->setContentsMargins(4,2,4,2);
    //magic numbers, need to change
    //------------------------------



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

