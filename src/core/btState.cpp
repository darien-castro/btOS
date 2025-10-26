//
// Created by pablovepo on 10/25/25.
//

#include "btState.h"


btState::btState(){
    updateTime();
}


void btState::updateTime(){
    QTime currentTime = QTime::currentTime();
    this->time = currentTime.toString();
}
QString btState::returnTime(){
    return time;
}
