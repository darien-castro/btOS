//
// Created by pablovepo on 10/26/25.
//

#ifndef HOMESCREEN_H
#define HOMESCREEN_H
#include <resources/QtCommon.h>


class homeScreen : public QObject {
    Q_OBJECT
    QWidget* btHomeScreen;
public:
    homeScreen();
    QWidget* returnHomeScreen();
};



#endif //HOMESCREEN_H
