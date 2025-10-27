//
// Created by pablovepo on 10/25/25.
//

#include "screenManager.h"
#include "btShell.h"


void screenManager::addWidget(QWidget* add_widget){
        stack->addWidget(add_widget);
        stack->setCurrentWidget(add_widget);
        emit stateChanged();
}
void screenManager::removeWidget(QWidget* rem_widget){
        stack->removeWidget(rem_widget);
        emit stateChanged();
}

void screenManager::switchTo(QWidget* state_widget){
        stack->setCurrentWidget(state_widget);
}

screenManager::screenManager(){
        stack = new QStackedWidget;
}


QStackedWidget* screenManager::returnStack(){
        return stack;
}


QWidget* screenManager::returnCurrent(){
        return stack->currentWidget();
}



void screenManager::delApp(){
        this->removeWidget(this->returnCurrent());
}
