//
// Created by pablovepo on 10/25/25.
//

#ifndef BTTOPBAR_H
#define BTTOPBAR_H
#include <resources/QtCommon.h>
#include <src/core/btState.h>

class btShell;

class btTopBar : public QWidget{
    Q_OBJECT
    QWidget* topBar;
    btShell* shell = nullptr;
    QWidget* exitButton;
    //todo decide if these variables are necessary
    QString time;
    QString battery;
    QString connection;
public:
    btTopBar(btShell* parent);
    void btTopBar_setup();
    QWidget* returnTopBar();
    void exitToggle(bool x);
    void styleWidget(QWidget* someWidget);
    signals:
    void buttonPressed();
};



#endif //BTTOPBAR_H
