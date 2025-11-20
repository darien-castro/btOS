//
// Created by pablovepo on 10/30/25.
//

#include "weatherScreen.h"
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
#include <iostream>
#include <fstream>
//toDo, weather API, coming soon!.


weatherScreen::weatherScreen(QWidget* parent) : btApplication(parent){
    link = "https://api.openweathermap.org/data/2.5/weather?q=";
    key = "&appid=14a0c28171ba4e585da8f25871450521";
    units = "&units=imperial";
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
    temp_button = new QPushButton("0", application);

    loc_layout->addWidget(search_display, 0, Qt::AlignLeft);
    loc_layout->addWidget(temp_button);
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
                                "color: white;"
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
    weather->setStyleSheet("QLabel{"
                           "margin: 20px 0px 0px 0px "
                           ""
                           "}");
}
void weatherScreen::set_styles(){
    top_weather_layout->setMargin(20);
    search_display->setFixedSize(200,55);
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
    search_display->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    search_display->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    search_display->setLineWrapMode(QTextEdit::NoWrap);
}
void weatherScreen::update_data(const QString& name){
    std::string fin_link = link + name.toStdString() + key + units;
    cpr::Response r = cpr::Get(cpr::Url(fin_link));
    //todo, switch case, cleaner
    if (r.error)
    {
        qDebug() << "Error code: " << r.status_code;
        return;
    }
    if (r.status_code == 400)
    {
        qDebug() << "Bad Request";
        qDebug() << r.status_code;
    }
    if (r.status_code == 401)
    {
        qDebug() << "Unauthorized";
        qDebug() << r.status_code;
    }
    if (r.status_code == 429)
    {
        qDebug() << "Too Many Requests";
        qDebug() << r.status_code;
    }
    if (r.status_code == 404)
    {
        qDebug() << "No Such City: " << name;
        qDebug() << "Error: " << r.status_code;
        return;
    }
    nlohmann::json j = nlohmann::json::parse(r.text);
    QString dump = QString::fromStdString(j.dump(4));
    int curr_temp;
    std::string main_desc;
    bool api_call_flag = true;
    try
    {
        curr_temp = j["main"]["temp"];
        main_desc = j["weather"][0]["main"];
    }
    catch (nlohmann::json_abi_v3_12_0::detail::type_error)
    {

        qDebug() << "not valid Integer or String";
        api_call_flag = false;
    }


    /*if (main_desc == "Clear")
    {
        application->setStyleSheet("QWidget#weather{"
                                   "background-image: url(../resources/appData/weather/clearDay.jpg);"
                                  "}");
    }
    if (main_desc == "Clouds")
    {
        application->setStyleSheet("QWidget#weather{"
                                    "background-image: url(../resources/appData/weather/cloudyDay.jpg);"
                                   "}");
    }
    if (main_desc == "Rain")
    {
        application->setStyleSheet("QWidget#weather{"
                                    "background-image: url(../resources/appData/weather/rainyDay.jpg);"
                                   "}");

    }
    if (main_desc == "Snow")
    {
        application->setStyleSheet("QWidget#weather{"
                                    "background-image: url(../resources/appData/weather/snowDay.jpg);"
                                   "}");
    }*/
    if (api_call_flag == true)
    {
        std::string curr_s_temp = std::to_string(curr_temp) + "°F";
        //to Qstrings
        QString curr_q_temp = QString::fromStdString(curr_s_temp);
        QString curr_desc = QString::fromStdString(main_desc);
        temp->setText(curr_q_temp);
        weather->setText(curr_desc);
    }
}

void weatherScreen::setup_connections(){
    connect(temp_button, &QPushButton::clicked, this, [this](){
        QString cityName = search_display->toPlainText();

        QThread* thread = QThread::create([this, cityName](){
            update_data(cityName);
        });
        // Clean up thread when finished
        connect(thread, &QThread::finished, thread, &QThread::deleteLater);
        thread->start();
    });
}

void weatherScreen::btAPP_SETUP(){
    setup_layout();
    setup_widgets();
    set_styles();
    set_style_sheet();
    setup_connections();
}
QString weatherScreen::returnAppName(){
    return appName;
}
void weatherScreen::btAPP_CLOSED(){
}
QWidget* weatherScreen::btAPP_RETURN(){
    return this->application;
}