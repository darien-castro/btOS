//
// Created by pablovepo on 10/30/25.
//

#include "weatherScreen.h"
//toDo, weather API, coming soon!.

weatherScreen::weatherScreen(){
    this->appName = "weather";
    this->setObjectName("weatherScreen");
}

void weatherScreen::btAPP_SETUP(){
    this->application = new QWidget();
    QVBoxLayout* mainScreen = new QVBoxLayout(this->application);

    QLabel* hello = new QLabel("weather");
    hello->setStyleSheet("QLabel{"
                         "color: #000000;"
                         ""
                         "}");

    mainScreen->addWidget(hello, 0, Qt::AlignCenter);
    this->setLayout(mainScreen);
    this->application->setStyleSheet("QWidget{"
                  "background-color: rgba(0,0,0,100);"
                  "}");
}

QString weatherScreen::returnAppName(){
    return appName;
}

void weatherScreen::btAPP_CLOSED(){
        QWidget* toDel = this->application;
        this->application = nullptr;
        delete toDel;
}

QWidget* weatherScreen::btAPP_RETURN(){
    return this->application;
}

