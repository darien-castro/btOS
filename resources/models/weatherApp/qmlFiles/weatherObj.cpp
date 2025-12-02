//
// Created by pablovepo on 11/27/25.
//

#include "weatherObj.h"
#include "src/applications/Weather/weatherScreen.h"  // ✅ Include here instead

// Now you can use weatherScreen methods
weatherObj::weatherObj(QObject* parent) : QObject(parent)
{
}



void weatherObj::store_city(QString city)
{
    m_city = city;
    emit initialresults(city);
    qDebug() << "store city called";

}
QString weatherObj::returnCity(){
    return m_city;
}

void weatherObj::terminalOutput()
{
    qDebug() << "outputting to term!!";
}

void weatherObj::update_state(QString state)
{
    qDebug() << "update State Called";
    m_state = state;
    qDebug() << "weather obj: " + m_state;
}

void weatherObj::update_condition(currentWeather condition)
{
    m_weatherCondition = condition;
    emit weatherConditionChanged();
    qDebug() << "function update_condition: " << m_weatherCondition;
}

