//
// Created by pablovepo on 10/25/25.
//

#include "btShell.h"

#include "../applications/homeScreen/homeScreen.h"
#include "../applications/Settings/settings.h"
#include "src/core/screenManager.h"
#include "src/ui/btTopBar.h"


void btShell::setupShellScreen(){

}


btShell::btShell(int h, int w) : height(h), width(w) {
    shellScreen = new QWidget();
    shellScreen->setFixedSize(w,h);
    qDebug() << "shell Screen width" << shellScreen->width();

    appManager = new btApplicationManager(shellScreen);


    initializeApplications();


    mainState = new btState;
    // create the QWidget for the shell

    // create the btTopBar controller
    topBar = new btTopBar(this);
    mainScreenManager = new screenManager;
    qDebug() << "Debug Here";
    homeScreen* mainHome = new homeScreen(this);
    mainScreenManager->addWidget(mainHome);
    topBar->setMaximumHeight(80);
    QVBoxLayout* mainScreen = new QVBoxLayout(shellScreen);
    mainScreen->addWidget(topBar);
    mainScreen->addWidget(mainScreenManager->returnStack());


    connect(mainScreenManager, &screenManager::stateChanged,
        this, &btShell::updateUi);
    shellScreen->setLayout(mainScreen);
    shellScreen->setFixedSize(width, height);
    shellScreen->setObjectName("shell");
    shellScreen->layout()->setContentsMargins(0, 0, 0, 0);

    qDebug() << "Margins:" << shellScreen->layout()->contentsMargins();

}

QString btShell::returnStateTime(){
    return mainState->returnTime();
}

screenManager* btShell::returnScreenManager() const{
    return mainScreenManager;
}


QWidget* btShell::returnCurrentScreen(){
    return shellScreen;
}

bool btShell::onHome(){
    if (current == CURRAPP::HOMESCREEN)
    {
        return true;
    }
    if (current == CURRAPP::APPLICATION)
    {
        return false;
    }
}


void btShell::updateUi(){
    if (mainScreenManager->returnStack()->currentWidget()->accessibleName() == "homescreen")
    {
        this->current = CURRAPP::HOMESCREEN;
        this->topBar->exitToggle(false);
    }
    else
    {
        this->current = CURRAPP::APPLICATION;
        this->topBar->exitToggle(true);
    }

    shellScreen->update();
    qDebug() << "update" << mainScreenManager->returnStack()->currentWidget();
}

btState* btShell::returnState(){
    return this->mainState;
}

QJsonArray* btShell::returnAppArray(){
    return &appArray;
}

QWidget* btShell::returnShellScreen(){
    return shellScreen;
}
void btShell::initializeApplications(){
    appManager->addApp<settings>("settingsScreen");
}

btApplicationManager* btShell::returnAppManager(){
    return appManager;
}
