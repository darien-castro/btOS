//
// Created by pablovepo on 10/26/25.
//

#ifndef HOMESCREEN_H
#define HOMESCREEN_H
#include <assets/QtCommon.h>
#include <src/core/btApplication.h>
class btShell;

class homeScreen : public QWidget {
  Q_OBJECT


    QJsonArray currentApplications; 
    QList<QPushButton*> onScreenButtons;
public:
    homeScreen(QJsonArray ApplicationArray);
    QWidget* returnHomeScreen();
    void buttonStyle(QWidget* button);
    void appButtonPressed(btApplication* app);
    void screenAppsSetup(QVBoxLayout* scrollArea);
signals:
    void applicationLaunchRequest(const QString& appName);
};



#endif //HOMESCREEN_H
