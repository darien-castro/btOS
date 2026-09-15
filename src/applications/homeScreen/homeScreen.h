//
// Created by pablovepo on 10/26/25.
//

#ifndef HOMESCREEN_H
#define HOMESCREEN_H

#include <assets/QtCommon.h>
#include <src/core/btApplication.h>
#include "src/ui/theme.h"

class homeScreen : public QWidget {
    Q_OBJECT

    QJsonArray currentApplications; 
    QList<QPushButton*> onScreenButtons;

public:
    explicit homeScreen(QJsonArray ApplicationArray);
    QWidget* returnHomeScreen();
    void screenAppsSetup(QVBoxLayout* scrollArea);

signals:
    void applicationLaunchRequest(const QString& appName);
};

#endif //HOMESCREEN_H
