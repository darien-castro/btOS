//
// Created by pablovepo on 10/25/25.
//

#include "btState.h"


btState::btState(){
    time = QTime::currentTime().toString("hh:mm:ss");
    timeChange.setInterval(1000);
    connect(&timeChange, &QTimer::timeout, this, [this]{
        updateTime();
        emit timeUpdated(this->time);
    });
    timeChange.start();
}


void btState::updateTime() {
    QTime currentTime = QTime::currentTime();
    this->time = currentTime.toString("hh:mm:ss");
}

QString btState::returnTime(){
    return time;
}

std::vector<btApplication*> btState::returnAppVect(){
    return this->applications;
}
