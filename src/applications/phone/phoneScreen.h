//
// Created by pablovepo on 10/29/25.
//

#ifndef PHONESCREEN_H
#define PHONESCREEN_H
#include <src/core/btApplication.h>


class phoneScreen : public btApplication{
    Q_OBJECT
    QString phoneNumberInput;
    public:
    phoneScreen(QWidget* parent = nullptr);
    QWidget* returnPhoneWindow();
    void btAPP_SETUP() override;
    QWidget* btAPP_RETURN() override;
    void btAPP_CLOSED() override;
    QString returnAppName() override;
};



#endif //PHONESCREEN_H
