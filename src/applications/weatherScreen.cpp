//
// Created by pablovepo on 10/30/25.
//

#include "weatherScreen.h"
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
#include <iostream>
#include <fstream>
//toDo, weather API, coming soon!.


weatherScreen::weatherScreen(){

    link = "https://api.openweathermap.org/data/2.5/weather";
    key = "14a0c28171ba4e585da8f25871450521";
    this->appName = "weather";
    this->setObjectName("weatherScreen");

}

void weatherScreen::btAPP_SETUP(){
    this->application = new QWidget();
    QVBoxLayout* mainScreen = new QVBoxLayout(this->application);
    QLabel* cityName = new QLabel();
    QLabel* weatherInfo = new QLabel();



    QPushButton* enterInfo = new QPushButton("search");

    QTextEdit* weatherSearch = new QTextEdit("Search...");
    weatherSearch->setFixedWidth(200);
    weatherSearch->setFixedHeight(35);
    weatherSearch->setLineWrapMode(QTextEdit::NoWrap);
    weatherSearch->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    weatherSearch->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    weatherSearch->setAlignment(Qt::AlignCenter);
    weatherSearch->setStyleSheet("QTextEdit{"
                                 "border: solid 5px #000000;"
                                 "border-radius: 10px;"
                                 "}");

    enterInfo->setStyleSheet("QPushButton{"
                             "padding: 15px;"
                             "border-radius: 5px;"
                             ""
                             "}"
                             "QPushButton:Hover{"
                             "}");


    connect(enterInfo, &QPushButton::clicked, this, [=]() {
    std::string cityInput = weatherSearch->toPlainText().toStdString();

    std::thread([=]() {
        try {
            cpr::Response r = cpr::Get(cpr::Url(
                "https://api.openweathermap.org/data/2.5/weather?q=" + cityInput +
                "&appid=" + key + "&units=imperial"));
            auto j = nlohmann::json::parse(r.text);
            if (!j.contains("name") || !j.contains("main"))
                throw std::runtime_error("bad json");

            QString city = QString::fromStdString(j["name"]);
            QString country = QString::fromStdString(j["sys"]["country"]);
            double temp_double = j["main"]["temp"].get<double>();
            QString temp_final = QString::number(temp_double) + " °F";

            QMetaObject::invokeMethod(application, [=]() {
                cityName->setText(city + ", " + country);
                weatherInfo->setText(temp_final);
            }, Qt::QueuedConnection);

        } catch (...) {
            QMetaObject::invokeMethod(application, [=]() {
                cityName->setText("Error");
                weatherInfo->setText("Invalid response");
            }, Qt::QueuedConnection);
        }
    }).detach();
});



    mainScreen->addWidget(weatherSearch, 0, Qt::AlignCenter);
    mainScreen->addWidget(cityName,0,Qt::AlignCenter);
    mainScreen->addWidget(weatherInfo,0,Qt::AlignCenter);

    mainScreen->addWidget(enterInfo,0,Qt::AlignCenter);

    this->application->setLayout(mainScreen);
    /*this->application->setStyleSheet("QWidget{"
                  "background-color: rgba(255,255,255,0);"
                  "color: rgba(0,0,0,255);"
                  "}");*/
}

QString weatherScreen::returnAppName(){
    return appName;
}

void weatherScreen::btAPP_CLOSED(){
        QWidget* toDel = this->application;
        this->application = nullptr;
        delete toDel;
}

QWidget* weatherScreen::btAPP_RETURN(){
    return this->application;
}

