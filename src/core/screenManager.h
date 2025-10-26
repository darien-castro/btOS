//
// Created by pablovepo on 10/25/25.
//

#ifndef SCREENMANAGER_H
#define SCREENMANAGER_H
#include <resources/QtCommon.h>

class btShell;

class screenManager {
    QStackedWidget* stack;
    public:
    screenManager();
    screenManager(QStackedWidget* init_stack);
    void addWidget(QWidget* add_widget);
    void removeWidget(QWidget* rem_widget);
    void switchTo(QWidget* state_widget);
    QStackedWidget* returnStack();
    QWidget* returnCurrent();
};



#endif //SCREENMANAGER_H
