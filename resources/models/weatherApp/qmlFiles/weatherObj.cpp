//
// Created by pablovepo on 11/27/25.
//

#include "weatherObj.h"

weatherObj::weatherObj(QObject* parent) : QObject(parent){}



void weatherObj::store_city(QString city)
{
    m_city = city;
    emit resultsReady();
}
QString weatherObj::returnCity(){
    return m_city;
}

void weatherObj::terminalOutput()
{
    qDebug() << "outputting to term!!";
}

