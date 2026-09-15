//
// Created by pablovepo on 10/25/25.
//

#ifndef BTSTATE_H
#define BTSTATE_H
#include <assets/QtCommon.h>

#include "btApplicationManager.h"
#include "../applications/Settings/settings.h"

class btState : public QObject{
    //define as qObject so that we can use Object Functions when necessary like a state change
    Q_OBJECT
    QString time;
    QString battery;
    QString connection;
    QTimer timeChange;
    QTimer connectionTest;
    QFile* configSettings;
    QJsonObject mainJson;
    QJsonArray apps;
public:
    btState();
    QString returnTime();
    QString returnBattery();
    QString returnConnection();
    void updateTime();
    void updateBattery();
    void updateConnection();
    std::vector<btApplication*> returnAppVect();
    void getSettingsJson();
    void writeSettingsJson();
    QJsonArray returnJsonAppArray();
    signals:
    void timeUpdated(QString newTime);

};



#endif //BTSTATE_H
