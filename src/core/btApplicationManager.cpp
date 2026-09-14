//
// Created by pablovepo on 11/14/25.
//

#include "btApplicationManager.h"


QStringList btApplicationManager::appName(){
    return _applications.keys();
}
btApplication* btApplicationManager::retrieve(QString application){
    return _applications.value(application);
}
int btApplicationManager::size(){
    return _applications.size();
}

QMap<QString, btApplication*> btApplicationManager::returnQMap(){
    return _applications;
}
