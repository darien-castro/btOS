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

    cityName->setStyleSheet("background-color: none");
    weatherInfo->setStyleSheet("background-color: none");

    QPushButton* enterInfo = new QPushButton("search");

    QTextEdit* weatherSearch = new QTextEdit("Search...");
    weatherSearch->setFixedWidth(200);
    weatherSearch->setFixedHeight(30);
    weatherSearch->setAlignment(Qt::AlignCenter);
    weatherSearch->setStyleSheet("QTextEdit{"
                                 "color: #000000;"
                                 "background-color: rgba(137,81,165,65);"
                                 "border: solid 5px #000000;"
                                 "border-radius: 10px;"
                                 "}");

    enterInfo->setStyleSheet("QPushButton{"
                             "background-color: rgba(63,81,96,150);"
                             "padding: 15px;"
                             "border-radius: 5px;"
                             ""
                             "}"
                             "QPushButton:Hover{"
                             "background-color: rgba(63,81,96,255);"
                             "}");


    connect(enterInfo, &QPushButton::clicked, this, [=]() {
        std::string cityInput = weatherSearch->toPlainText().toStdString();
        std::thread([=]() {
            cpr::Response r = cpr::Get(cpr::Url("https://api.openweathermap.org/data/2.5/weather?q=" + cityInput + "&appid=" + key + "&units=imperial"));
            qDebug() << QString::fromStdString(r.text);
            try {
                auto j = nlohmann::json::parse(r.text);
                QString city = QString::fromStdString(j["name"]);
                QString country = QString::fromStdString(j["sys"]["country"]);
                double temp_double = j["main"]["temp"].get<double>();
                if (temp_double < 60)
                {
                    this->application->setStyleSheet("QWidget{"
                                  "background: rgba(26,20,35,200);"
                                  ""
                                  "}");
                }
                if (temp_double > 60)
                {
                    this->application->setStyleSheet("QWidget{"
                                  "background: rgba(119,76,96,155);"
                                  ""
                                  "}");
                }
                QString temp_final = QString::number(temp_double) + " °F";
                QMetaObject::invokeMethod(application, [=]() {
                cityName->setText(city + ", "  + country);
                weatherInfo->setText(temp_final);
            }, Qt::QueuedConnection);
            } catch (...) {
                QMetaObject::invokeMethod(weatherInfo, [=]() {
                    qDebug() << "error, cannot find Area";
                }, Qt::QueuedConnection);
            }
        }).detach();
    });



    auto* shadow = new QGraphicsDropShadowEffect;
    shadow->setBlurRadius(100);
    shadow->setOffset(3, 3);
    shadow->setColor(Qt::blue);
    weatherSearch->setGraphicsEffect(shadow);

    mainScreen->addWidget(weatherSearch, 0, Qt::AlignCenter);
    mainScreen->addWidget(cityName,0,Qt::AlignCenter);
    mainScreen->addWidget(weatherInfo,0,Qt::AlignCenter);

    mainScreen->addWidget(enterInfo,0,Qt::AlignCenter);

    this->application->setLayout(mainScreen);
    this->application->setStyleSheet("QWidget{"
                  "background-color: rgba(255,255,255,0);"
                  "color: rgba(0,0,0,255);"
                  "}");
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

