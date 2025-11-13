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
void weatherScreen::setup_layout(){
    application = new QWidget;
    this->application->setObjectName("weather");
    top_weather_layout = new QVBoxLayout(application);
    loc_layout = new QHBoxLayout();
    time_date_layout = new QHBoxLayout();
    temp_weather_layout = new QHBoxLayout();
    next_temps = new QHBoxLayout();
    multi_info_layout = new QHBoxLayout();
    multi_info_widget = new QWidget();
    final_layout = new QHBoxLayout();

    top_weather_layout->addLayout(loc_layout);
    top_weather_layout->addLayout(time_date_layout);
    top_weather_layout->addLayout(temp_weather_layout);
    multi_info_widget->setLayout(next_temps);
    final_layout->addWidget(multi_info_widget,0, Qt::AlignLeft | Qt::AlignTop);
    top_weather_layout->addLayout(final_layout);

}

void weatherScreen::setup_widgets(){
    search_display = new QTextEdit("Search...", application);
    time_date = new QLabel("Today, Nov 13, 13:51",application);
    temp = new QLabel("16 C",application);
    weather = new QLabel("Mostly Cloudy", application);
    next_hour = new QLabel("17C", application);
    seperator = new QFrame;
    next_two_hour = new QLabel("19 C",application);

    loc_layout->addWidget(search_display, 0, Qt::AlignLeft);
    time_date_layout->addWidget(time_date, 0, Qt::AlignLeft);
    temp_weather_layout->addWidget(temp,0,Qt::AlignLeft | Qt::AlignTop);
    temp_weather_layout->addWidget(weather,0,Qt::AlignRight | Qt::AlignTop);
    next_temps->addWidget(next_hour,0,Qt::AlignLeft);
    next_temps->addWidget(seperator,0,Qt::AlignCenter);
    next_temps->addWidget(next_two_hour, 0, Qt::AlignRight);
}

void weatherScreen::set_style_sheet(){
    search_display->setStyleSheet("QTextEdit{"
                                  "background-color: rgba(0,0,0,0);"
                                  "color: #FFFFFF;"
                                  "font-size: 24px;"
                                  "border: none;"
                                  "}");
    application->setStyleSheet("QWidget#weather{"
                               "background-image: url(../resources/appData/weather/cloudyDay.jpg);"
                               "background-repeat: no-repeat;"
                                "background-position: center;"
                                "border: none;"
                               "}");
    time_date->setStyleSheet("QLabel{"
                             "font-size: 12px;"
                             "margin-top: 1ex;"
                             "background: none;"
                             "}");
    temp->setStyleSheet("QLabel{"
                        "color: rgba(255,255,255,199);"
                        "font-size: 124px;"
                        "background: none;"
                        "}");
    multi_info_widget->setStyleSheet("QWidget{"
                                    "border: 2px solid white;"
                                     "border-radius: 16px;"
                                     "}");
    next_hour->setStyleSheet("QLabel{"
                             "border: none;}");
    next_two_hour->setStyleSheet("QLabel{"
                             "border: none;}");
}
void weatherScreen::set_styles(){
    top_weather_layout->setMargin(20);
    search_display->setFixedSize(130,55);
    time_date->setFixedSize(150,45);
    weather->setFixedSize(200,200);
    time_date_layout->setContentsMargins(0,0,0,0);
    temp_weather_layout->setContentsMargins(0,0,0,0);
    multi_info_layout->setContentsMargins(0,0,0,0);
    final_layout->setContentsMargins(0,0,0,0);
    temp->setFixedSize(400,200);
    multi_info_widget->setFixedSize(200,75);
    final_layout->setContentsMargins(0,0,0,0);
    seperator->setGeometry(QRect(320, 150, 118, 3));
    seperator->setFrameShape(QFrame::VLine);
    seperator->setFrameShadow(QFrame::Sunken);
}

void weatherScreen::setup_connections(){

}


void weatherScreen::btAPP_SETUP(){
    setup_layout();
    setup_widgets();
    set_styles();
    set_style_sheet();
}

QString weatherScreen::returnAppName(){
    return appName;
}

void weatherScreen::btAPP_CLOSED(){

}

QWidget* weatherScreen::btAPP_RETURN(){
    return this->application;
}

