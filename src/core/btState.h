//
// Created by pablovepo on 10/25/25.
//

#ifndef BTSTATE_H
#define BTSTATE_H
#include <resources/QtCommon.h>

#include "src/applications/notesScreen.h"
#include "src/applications/phoneScreen.h"
//state for device
class btState : public QObject{
    //define as qObject so that we can use Object Functions when necessary like a state change
    Q_OBJECT
    QString time;
    QString battery;
    QString connection;
    QTimer timeChange;
    QTimer connectionTest;
    notesScreen* notes = new notesScreen;
    phoneScreen* phone = new phoneScreen;
    std::vector<btApplication*> applications = {notes, phone};
public:
    btState();
    QString returnTime();
    QString returnBattery();
    QString returnConnection();
    void updateTime();
    void updateBattery();
    void updateConnection();
    std::vector<btApplication*> returnAppVect();
    signals:
    void timeUpdated(QString newTime);

};



#endif //BTSTATE_H
