//
// Created by pablovepo on 11/27/25.
//

#ifndef WEATHEROBJ_H
#define WEATHEROBJ_H
#include <resources/QtCommon.h>



class weatherObj : public QObject {
    Q_OBJECT
    QString m_city;
public:
    Q_INVOKABLE void store_city(QString city);
    weatherObj(QObject* parent = nullptr);
    Q_INVOKABLE QString returnCity();
    Q_INVOKABLE void terminalOutput();
    signals:
    void resultsReady();
};



#endif //WEATHEROBJ_H
