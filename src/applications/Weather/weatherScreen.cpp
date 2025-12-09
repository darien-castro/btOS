//
// Created by pablovepo on 10/30/25.
//

#include "weatherScreen.h"

#include <iostream>
#include <fstream>
//toDo, weather API, coming soon!.
weatherScreen::weatherScreen(QWidget* parent) : btApplication(parent){
    link = "https://api.openweathermap.org/data/2.5/weather?q=";
    temp_link = "api.openweathermap.org/data/2.5/forecast?q=";
    key = "&appid=14a0c28171ba4e585da8f25871450521";
    units = "&units=imperial";
    this->appName = "weather";
    this->setObjectName("weatherScreen");
    m_futureMap = new QMap<int, FutureData>();
    for (int i = 0; i < 8;i++)
    {
        FutureData curr("6","7");
        m_futureMap->insert(i,curr);
    }
}
void weatherScreen::setup_layout(){
    application = new QWidget;
    this->application->setObjectName("weatherApp");
    m_qml_holder = new QHBoxLayout(this);
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
    std::string string_name = name.toStdString();
    std::string encoded_name;

    for (int i = 0; i < string_name.length(); i++)
    {
        if (string_name[i] == ' ')
        {
            encoded_name += "%20";  // <-- IMPORTANT
        }
        else
        {
            encoded_name += string_name[i];
        }
    }

    std::string fin_link = link + encoded_name + key + units;
    qDebug() << QString::fromStdString(fin_link);

    std::string temp_string = temp_link + encoded_name + key + units;
    test_daily_call(temp_string);


    cpr::Response l_temp_response = cpr::Get(cpr::Url(fin_link));
    if (data_error(l_temp_response))
    {
        return;
    }
    m_response = l_temp_response;
    if (!parse_api_call())
    {
        qDebug() << "something went wrong parsing";
    }
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
    std::string country;
    std::string curr_city;
    std::string condition;
    bool api_call_flag = true;
    try
    {
        qDebug() << dump;
        curr_city = j["name"];
        curr_temp = j["main"]["temp"];
        main_desc = j["weather"][0]["main"];
        country = j["sys"]["country"];
        condition = j["weather"][0]["main"];

        qDebug() <<  QString::fromStdString(country);
    }
    catch (nlohmann::json_abi_v3_12_0::detail::type_error)
    {

        qDebug() << "not valid Integer or String";
        api_call_flag = false;
    }
    if (api_call_flag == true)
    {
        QString curr_desc = QString::fromStdString(main_desc);
        m_curr_country = QString::fromStdString(country);
        QString blah = QString::fromStdString(curr_city);
        setTemperature(curr_temp);
        setDescription(curr_desc);
        set_condition(condition.data());
        weather_qml->updateQmlState(m_curr_country);
        weather_qml->weatherObjEmit();

    }
    return true;
}

void weatherScreen::update_data(const QString& name){
    update_response(name);

}

void weatherScreen::setup_connections(){
    connect(weather_qml->return_weatherObj(), &weatherObj::initialresults, this, [this]()
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
    this->weather_qml->return_weatherObj()->set_qmap(m_futureMap);
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

void weatherScreen::set_condition(const QString& condition)
{
    if (condition == "Rain")
    {
        weather_qml->return_weatherObj()->update_condition(weatherObj::STORMY);
        return;
    }
    if (condition == "Thunderstorm")
    {
        weather_qml->return_weatherObj()->update_condition(weatherObj::STORMY);
        return;
    }
    if (condition == "Drizzle")
    {
        weather_qml->return_weatherObj()->update_condition(weatherObj::DRIZZLY);
        return;

    }
    if (condition == "Snow")
    {
        weather_qml->return_weatherObj()->update_condition(weatherObj::SNOWY);\
        return;

    }
    if (condition == "Clear")
    {
        weather_qml->return_weatherObj()->update_condition(weatherObj::CLEAR);
        return;

    }
    if (condition == "Clouds")
    {
        weather_qml->return_weatherObj()->update_condition(weatherObj::CLOUDY);
        return;
    }

    weather_qml->return_weatherObj()->update_condition(weatherObj::NONE);

}

void weatherScreen::test_daily_call(const std::string& link)
{
    cpr::Response temp_temp = cpr::Get(cpr::Url(link));
    nlohmann::json j;
    if (m_futureMap->count() != 0)
    {
        m_futureMap->clear();
    }
    try
    {
        j = nlohmann::json::parse(temp_temp.text);
    }
    catch (nlohmann::json_abi_v3_12_0::detail::parse_error)
    {
        qDebug() << "error parsing";
    }

    try
    {
        for (int i = 0; i < 7; i++){
            int temp = j["list"][i]["main"]["temp"];
            long timestamp = j["list"][i]["dt"];
            QDateTime utcTime = QDateTime::fromSecsSinceEpoch(timestamp, QTimeZone::utc());
            QDateTime estTime = utcTime.toTimeZone(QTimeZone("America/New_York"));
            QString time = estTime.toString("hh:mm AP");

            FutureData curr(time, QString::number(temp));
            m_futureMap->insert(i, curr);
        }
        for (int i = 0; i < m_futureMap->size(); i++)
        {
            qDebug() << "time: " << m_futureMap->find(i).value().m_time;
            qDebug() << "time: " << m_futureMap->find(i).value().m_temp;

        }
    }
    catch (nlohmann::json_abi_v3_12_0::detail::type_error)
    {
        qDebug() << "type error";
    }
    emit qMapChanged();
}