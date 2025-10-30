//
// Created by pablovepo on 10/26/25.
//

#ifndef HOMESCREEN_H
#define HOMESCREEN_H
#include <resources/QtCommon.h>
#include <src/core/btApplication.h>
class btShell;

class homeScreen : public QWidget {
    btShell* mainShell;
public:
    homeScreen(btShell* shell);
    QWidget* returnHomeScreen();
    void buttonStyle(QWidget* button);
    void appButtonPressed(btApplication* app);
    void screenAppsSetup(QVBoxLayout* scrollArea);
};



#endif //HOMESCREEN_H
