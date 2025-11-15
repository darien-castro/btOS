//
// Created by pablovepo on 10/29/25.
//

#ifndef SETTINGS_H
#define SETTINGS_H
#include "src/core/btApplication.h"
#include <qpixmap.h>


class settings : public btApplication {
    Q_OBJECT;
public:
    settings();
    void btAPP_SETUP() override;
    QWidget* btAPP_RETURN() override;
    void btAPP_CLOSED() override;
    QString returnAppName() override;
};



#endif //SETTINGS_H
