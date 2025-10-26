//
// Created by pablovepo on 10/25/25.
//

#ifndef BTTOPBAR_H
#define BTTOPBAR_H
#include <resources/QtCommon.h>
#include <src/core/btState.h>

class btShell;

class btTopBar : public QObject{
    Q_OBJECT
    QWidget* topBar;
    //todo decide if these variables are necessary
    QString time;
    QString battery;
    QString connection;
public:
    btTopBar();
    void btTopBar_setup();
    QWidget* returnTopBar();
};



#endif //BTTOPBAR_H
