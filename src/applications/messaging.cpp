//
// Created by pablovepo on 10/29/25.
//

#include "messaging.h"

messaging::messaging(){
    this->appName = "messages";
    setObjectName("messageScreen");
}


QString messaging::returnAppName(){
    return this->appName;
}
void messaging::btAPP_SETUP(){
    std::cout << "messaging setup" <<std::endl;
}

QWidget* messaging::btAPP_RETURN(){
    return this->application;
}

void messaging::btAPP_CLOSED(){
    std::cout << "app set to close!" <<std::endl;
}


