//
// Created by pablovepo on 10/26/25.
//

#include "homeScreen.h"


homeScreen::homeScreen(){
    btHomeScreen = new QWidget;
    QLabel* btLabel = new QLabel("Hello World");
    QVBoxLayout* homeScreenLayout = new QVBoxLayout;

    homeScreenLayout->addWidget(btLabel, 0, Qt::AlignCenter);

    btHomeScreen->setLayout(homeScreenLayout);
}

QWidget* homeScreen::returnHomeScreen(){
    return btHomeScreen;
}

