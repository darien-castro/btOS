//
// Created by pablovepo on 10/30/25.
//

#ifndef WEATHER_H
#define WEATHER_H
#include <src/core/btApplication.h>


class weatherScreen : public btApplication {
    Q_OBJECT;
    std::string toChangeInfo = "";
    std::string key;
    std::string link;
    public:
    weatherScreen();
    QWidget* returnNotesWindow();
    void btAPP_SETUP() override;
    QWidget* btAPP_RETURN() override;
    void btAPP_CLOSED() override;
    QString returnAppName() override;
};



#endif //WEATHER_H
