//
// Created by pablovepo on 10/25/25.
//

#include "btShell.h"

#include "src/applications/appViewer.h"
#include "src/applications/homeScreen.h"
#include "src/core/screenManager.h"
#include "src/ui/btTopBar.h"
#include <src/applications/appViewer.h>
#include <thread>
#include <chrono>


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

    mainScreenManager->addWidget(mainHome);

    topBar->setMaximumHeight(80);


    QVBoxLayout* mainScreen = new QVBoxLayout(shellScreen);
    mainScreen->addWidget(topBar);
    mainScreen->addWidget(mainScreenManager->returnStack());

    setupKeys();

    connect(mainScreenManager, &screenManager::stateChanged,
        this, &btShell::updateUi);


    shellScreen->setLayout(mainScreen);
    shellScreen->setFixedSize(width, height);
    shellScreen->setObjectName("shell");
    shellScreen->setStyleSheet("QWidget{"
                               "background-color: rgba(255,255,255,255);"
                               "}");


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


void btShell::setupKeys(){
    QShortcut* shortcut = new QShortcut(QKeySequence("Alt+A"), this->shellScreen);
    connect (shortcut, &QShortcut::activated, [this]{
        if (this->returnScreenManager()->returnStack()->currentWidget()->objectName() == "appViewer")
        {
            qDebug() << "cannot change to same screen";
            return;
        }
        mainScreenManager->addWidget(new appViewer(this));
        qDebug() << "pressed";
    });
}

btState* btShell::returnState(){
    return this->mainState;
}

