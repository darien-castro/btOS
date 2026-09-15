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
    topBar = new btTopBar();
    connect(topBar, &btTopBar::quitApplicationRequested, [this]{
      endActiveApplication();
    });
    connect(mainState, &btState::timeUpdated, topBar, &btTopBar::setTime);


    mainScreenManager = new screenManager;

    qDebug() << "Debug Here";
  
    // home screen instantiation
    homeScreen* mainHome = new homeScreen(mainState->returnJsonAppArray());
    connect(mainHome, &homeScreen::applicationLaunchRequest, [this](QString appName){
        activeApp = appManager->retrieve(appName);
        startActiveApplication();
    });

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
    return current == CURRAPP::HOMESCREEN;
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

void btShell::startActiveApplication(){
  if (activeApp == nullptr){
    qDebug() << "No Active App";
    return;
  }
  activeApp->btAPP_SETUP();
  returnScreenManager()->addWidget(activeApp->btAPP_RETURN());
  returnScreenManager()->returnStack()->setCurrentWidget(activeApp->btAPP_RETURN());
};
void btShell::endActiveApplication(){
  mainScreenManager->removeWidget(mainScreenManager->returnCurrent());
  activeApp->btAPP_CLOSED();
  activeApp = nullptr;
};
