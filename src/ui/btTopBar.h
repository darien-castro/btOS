//
// Created by pablovepo on 10/25/25.
//

#ifndef BTTOPBAR_H
#define BTTOPBAR_H
#include <assets/QtCommon.h>
#include <src/core/btState.h>

class Theme;

class btTopBar : public QWidget{
    Q_OBJECT


    QWidget* topBar;
    QWidget* exitButton = nullptr;
    QLabel* labelTime = nullptr;
    //todo decide if these variables are necessary
    QString time = "00:00";
    QString battery;
    QString connection;
public:
    btTopBar(QWidget* parent = nullptr);
    void btTopBar_setup();
    QWidget* returnTopBar();
    void exitToggle(bool x);
    void styleWidget(QWidget* someWidget);
    void setTime(const QString& time);
signals:
    void quitApplicationRequested();
    void buttonPressed();

};



#endif //BTTOPBAR_H
