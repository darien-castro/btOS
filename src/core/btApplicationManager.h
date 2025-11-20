//
// Created by pablovepo on 11/14/25.
//

#ifndef BTAPPLICATIONMANAGER_H
#define BTAPPLICATIONMANAGER_H
#include <resources/QtCommon.h>
#include <QMap>

#include "btApplication.h"


class btApplicationManager{
    QWidget* m_parent;
    public:
    btApplicationManager(QWidget* parent = nullptr) : m_parent(parent){};
    template <typename AppType>
    AppType* addApp(const QString& name) {
        AppType* app = new AppType(m_parent);
        _applications[name] = app;
        return app;
    }
    btApplication* retrieve(QString application);
    QStringList appName();
    QMap<QString, btApplication*> returnQMap();
    int size();
private:
    QMap<QString, btApplication*> _applications;
};



#endif //BTAPPLICATIONMANAGER_H
