//
// Created by pablovepo on 10/25/25.
//

#ifndef BTSTATE_H
#define BTSTATE_H
#include <resources/QtCommon.h>

#include "src/applications/messaging.h"
#include "src/applications/notesScreen.h"
#include "src/applications/phoneScreen.h"
#include "src/applications/weatherScreen.h"
#define configLoc "/home/pablovepo/CLionProjects/btOS/resources/config/settings.json"
//state for device
class btState : public QObject{
    //define as qObject so that we can use Object Functions when necessary like a state change
    Q_OBJECT
    QString time;
    QString battery;
    QString connection;
    QTimer timeChange;
    QTimer connectionTest;
    std::string configLocation = configLoc;
    QFile* configSettings;
    QJsonObject mainJson;
    QJsonArray apps;
    notesScreen* notes = new notesScreen;
    phoneScreen* phone = new phoneScreen;
    weatherScreen* weather = new weatherScreen;
    messaging* messageScreen = new messaging;
    std::vector<btApplication*> applications = {phone, messageScreen,notes, weather};
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
