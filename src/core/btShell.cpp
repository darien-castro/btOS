//
// Created by pablovepo on 10/25/25.
//

#include "btShell.h"

#include "src/applications/homeScreen.h"
#include "src/core/screenManager.h"
#include "src/ui/btTopBar.h"

void btShell::setupShellScreen(){

}


btShell::btShell(int h, int w) : height(h), width(w) {
    mainState = new btState;

    // create the QWidget for the shell
    shellScreen = new QWidget();

    // create the btTopBar controller
    topBar = new btTopBar();

    mainScreenManager = new screenManager;
    homeScreen* mainHome = new homeScreen(this);

    mainScreenManager->addWidget(mainHome->returnHomeScreen());

    QWidget* localTopBar = topBar->returnTopBar();
    localTopBar->setMaximumHeight(80);


    QVBoxLayout* mainScreen = new QVBoxLayout(shellScreen);
    mainScreen->addWidget(localTopBar);
    mainScreen->addWidget(mainScreenManager->returnStack());

    connect(mainScreenManager, &screenManager::stateChanged,
        this, &btShell::updateUi);


    shellScreen->setLayout(mainScreen);
    shellScreen->setFixedSize(width, height);

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


void btShell::updateUi(){
    shellScreen->update();
    qDebug() << "update" << shellScreen;
}



