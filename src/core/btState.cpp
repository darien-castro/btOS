//
// Created by pablovepo on 10/25/25.
//

#include "btState.h"


btState::btState(){
    getSettingsJson();
    time = QTime::currentTime().toString("hh:mm a");
    timeChange.setInterval(1000);
    connect(&timeChange, &QTimer::timeout, this, [this]{
        updateTime();
        emit timeUpdated(this->time);
    });
    timeChange.start();
}


void btState::updateTime() {
    QTime currentTime = QTime::currentTime();
    this->time = currentTime.toString("hh:mm a");
}

QString btState::returnTime(){
    return time;
}

/*
std::vector<btApplication*> btState::returnAppVect(){
    return this->applications;
}
*/

void btState::getSettingsJson(){

    //todo, make sure this isn't storing too much memory, and make sure by copy
    qDebug() << "Settings File Loaded...";
    configSettings = new QFile("/home/pablovepo/CLionProjects/btOS/resources/config/settings.json");
    if (!configSettings->open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open file:" << configSettings->errorString();
        return;
    }
    QByteArray jsonData = configSettings->readAll();
    configSettings->close();
    delete configSettings;
    configSettings= nullptr;
    QJsonParseError parseError;
    QJsonDocument doc =QJsonDocument::fromJson(jsonData, &parseError);

    // Step 3: Check for parsing errors
    if (parseError.error != QJsonParseError::NoError) {
        qDebug() << "JSON parse error:" << parseError.errorString();
        return;
    }
    mainJson = doc.object();
    apps = mainJson["applications"].toArray();
}


QJsonArray btState::returnJsonAppArray(){
    return apps;
}

