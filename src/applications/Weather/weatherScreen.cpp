//
// Created by pablovepo on 10/30/25.
//

#include "weatherScreen.h"

#include <iostream>
#include <fstream>
//toDo, weather API, coming soon!.
weatherScreen::weatherScreen(QWidget* parent) : btApplication(parent){
    link = "https://api.openweathermap.org/data/2.5/weather?q=";
    key = "&appid=14a0c28171ba4e585da8f25871450521";
    units = "&units=imperial";
    this->appName = "weather";
    this->setObjectName("weatherScreen");
    application = new QWidget;
    this->application->setObjectName("weatherApp");
}
void weatherScreen::setup_layout(){
    m_qml_holder = new QHBoxLayout(application);
}

void weatherScreen::setup_widgets(){
    weather_qml = new weatherWebApp(this);
}
bool weatherScreen::data_error(cpr::Response response)
{
    if (response.error)
    {
        qDebug() << "Error code: " << response.status_code;
        return true;
    }
    if (response.status_code == 400)
    {
        qDebug() << "Bad Request";
        qDebug() << response.status_code;
        return true;
    }
    if (response.status_code == 401)
    {
        qDebug() << "Unauthorized";
        qDebug() << response.status_code;
        return true;
    }
    if (response.status_code == 429)
    {
        qDebug() << "Too Many Requests";
        qDebug() << m_response.status_code;
        return true;
    }
    if (response.status_code == 404)
    {
        qDebug() << "No Such City: " << name;
        qDebug() << "Error: " << response.status_code;
        return true;
    }
    return false;
}

void weatherScreen::update_response(const QString& name)
{
    std::string fin_link = link + name.toStdString() + key + units;
    cpr::Response l_temp_response = cpr::Get(cpr::Url(fin_link));
    if (data_error(l_temp_response))
    {
        return;
    }
    m_response = l_temp_response;
}
bool weatherScreen::parse_api_call()
{
    nlohmann::json j;
    try
    {
        j=nlohmann::json::parse(m_response.text);
    }
    catch (nlohmann::json_abi_v3_12_0::detail::parse_error)
    {
        qDebug() << "not a valid var";
        return false;
    }

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
    if (api_call_flag == true)
    {
        std::string curr_s_temp = std::to_string(curr_temp) + "°F";
        //to Qstrings
        QString curr_q_temp = QString::fromStdString(curr_s_temp);
        QString curr_desc = QString::fromStdString(main_desc);
        qDebug() << "temperature: " + curr_q_temp;
        qDebug() << "description: " + curr_desc;
    }
    return true;
}

void weatherScreen::update_data(const QString& name){
    update_response(name);
    if (!parse_api_call())
    {
        qDebug() << "something went wrong parsing";
    }
    //update onScreen logic

}

void weatherScreen::setup_connections(){
    connect(weather_qml->return_weatherObj(), &weatherObj::resultsReady, this, [this]()
        {
            QString var = weather_qml->return_city_from_qml();
            update_data(var);
        });
}
void weatherScreen::initiate_application(){
    m_qml_holder->addWidget(weather_qml);
    application->setLayout(m_qml_holder);
}

void weatherScreen::btAPP_SETUP(){
    setup_layout();
    setup_widgets();
    setup_connections();
    initiate_application();
    qDebug()<< "got here";

}
QString weatherScreen::returnAppName(){
    return appName;
}
void weatherScreen::btAPP_CLOSED(){
}
QWidget* weatherScreen::btAPP_RETURN(){
    return this->application;
}