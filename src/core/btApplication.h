//
// Created by pablovepo on 10/29/25.
//

#ifndef BTAPPLICATION_H
#define BTAPPLICATION_H
#include <resources/QtCommon.h>


class btApplication : public QWidget {
    Q_OBJECT
public:
    QString appName;
    QWidget* application = nullptr;
    virtual void btAPP_SETUP() = 0;
    /*virtual void btAPP_OPENED() = 0;*/
    virtual QWidget* btAPP_RETURN() = 0;
    virtual void btAPP_CLOSED() = 0;
    virtual QString returnAppName() = 0;
};



#endif //BTAPPLICATION_H
