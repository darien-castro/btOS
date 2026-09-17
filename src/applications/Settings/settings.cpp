//
// Created by pablovepo on 10/29/25.
//

#include "settings.h"
#include "../../ui/theme.h"


settings::settings(QWidget* parent) : btApplication(parent){
    this->appName = "settings";
    setObjectName("settingsScreen");
}
void settings::btAPP_SETUP(){

    application = new QWidget();

    QVBoxLayout* settings_main = new QVBoxLayout(this->application);
    settings_main->setAlignment(Qt::AlignTop);
    settings_main->setSpacing(100);

    QLabel* settings_label = new QLabel("Settings");
    Theme::markAsTitle(settings_label);
    settings_main->addWidget(settings_label, 0, Qt::AlignCenter);


    QPushButton* look_and_feel = new QPushButton("look and feel");
    Theme::markAsCard(look_and_feel);
    settings_main->addWidget(look_and_feel, 0, Qt::AlignCenter);
    look_and_feel->setContentsMargins(0,5,0,5);
    look_and_feel->setFixedWidth(340);
    look_and_feel->setFixedHeight(58);



    QPushButton* applications = new QPushButton("application settings");
    Theme::markAsCard(applications);
    settings_main->addWidget(applications, 0, Qt::AlignCenter);
    applications->setContentsMargins(0,5,0,5);
    applications->setFixedWidth(340);
    applications->setFixedHeight(58);


    QPushButton* paths = new QPushButton("directory paths");
    Theme::markAsCard(paths);
    paths->setContentsMargins(0,5,0,5);
    settings_main->addWidget(paths, 0, Qt::AlignCenter);
    paths->setFixedWidth(340);
    paths->setFixedHeight(58);






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

