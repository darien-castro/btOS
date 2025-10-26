//
// Created by pablovepo on 10/25/25.
//

#ifndef BTSTATE_H
#define BTSTATE_H
#include <resources/QtCommon.h>

//state for device
class btState : public QObject{
    //define as qObject so that we can use Object Functions when necessary like a state change
    Q_OBJECT
    QString time;
    QString battery;
    QString connection;
    QTimer timeChange;
    QTimer connectionTest;
public:
    btState();
    QString returnTime();
    QString returnBattery();
    QString returnConnection();
    void updateTime();
    void updateBattery();
    void updateConnection();
};



#endif //BTSTATE_H
