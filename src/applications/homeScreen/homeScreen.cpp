//
// Created by pablovepo on 10/26/25.
//

#include "homeScreen.h"

#include "src/core/btShell.h"
#include "src/core/screenManager.h"


//although we may have many applications, the homescreen should only display the ones the user wants, function grabs a
//vector of all variables (within the btState) and looks through config settings to see if "onScreen" bool is true, then places them if so.
void homeScreen::screenAppsSetup(QVBoxLayout* scrollArea){

  // instead of passing over whole array, just pass jsonfile with creation of homescreen

      for (const QJsonValue &value : currentApplications) {
          QJsonObject obj = value.toObject();
          QString name = obj["base_object_name"].toString();
          bool onHome = obj["on_home_screen"].toBool();
          qDebug() << name; 
          if (onHome == true){
              QPushButton* curr = new QPushButton(name);
              onScreenButtons.push_back(curr);
              curr->setFocusPolicy(Qt::StrongFocus);
              curr->setFixedWidth(200);
              curr->setFixedHeight(45);
              scrollArea->addWidget(curr,0,Qt::AlignCenter);
              buttonStyle(curr);
              QObject::connect(curr, &QPushButton::clicked, [this,name]{
                  emit applicationLaunchRequest(name);  
          });
      }
    };
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


homeScreen::homeScreen(QJsonArray ApplicationArray): currentApplications(ApplicationArray){

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
                  "background-color: black; "
                  "}");
}

QWidget* homeScreen::returnHomeScreen(){
    return this;
}

