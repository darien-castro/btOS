//
// Created by pablovepo on 10/29/25.
//

#ifndef MESSAGING_H
#define MESSAGING_H
#include <iostream>
#include "src/core/btApplication.h"
#include <resources/QtCommon.h>


class messaging : public btApplication {
public:
    messaging();
    void btAPP_SETUP() override;
    QWidget* btAPP_RETURN() override;
    void btAPP_CLOSED() override;
    QString returnAppName() override;
};



#endif //MESSAGING_H
