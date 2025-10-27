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
    topBar = new btTopBar(this);

    mainScreenManager = new screenManager;
    homeScreen* mainHome = new homeScreen(this);

    mainScreenManager->addWidget(mainHome->returnHomeScreen());

    topBar->setMaximumHeight(80);


    QVBoxLayout* mainScreen = new QVBoxLayout(shellScreen);
    mainScreen->addWidget(topBar);
    mainScreen->addWidget(mainScreenManager->returnStack());

    connect(mainScreenManager, &screenManager::stateChanged,
        this, &btShell::updateUi);

    shellScreen->setStyleSheet("QWidget{"
                  "background-image: url(/home/pablovepo/CLionProjects/btOS/resources/themes/FrutigerAero/frutigeraero.png)"
                  "}");
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


