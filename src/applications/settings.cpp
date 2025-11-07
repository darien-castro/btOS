//
// Created by pablovepo on 10/29/25.
//

#include "settings.h"


settings::settings(){
    this->appName = "settings";
    setObjectName("settingsScreen");
}
void settings::btAPP_SETUP(){
    application = new QWidget();
    QLabel* construction = new QLabel("under construction");
    QLabel* cat = new QLabel;
    QVBoxLayout* settings_main = new QVBoxLayout(this->application);
    settings_main->addWidget(construction,0,Qt::AlignCenter);

    QPixmap* mypix = new QPixmap("../resources/cat/cat.png");
    cat->setPixmap(*mypix);
    delete mypix;
    settings_main->addWidget(cat,0,Qt::AlignCenter);


}
QString settings::returnAppName(){
    return objectName();
}
QWidget* settings::btAPP_RETURN(){
    return this->application;
}

void settings::btAPP_CLOSED(){
    QWidget* toDel = this->application;
    this->application = nullptr;
    delete toDel;
}

