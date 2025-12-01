//
// Created by pablovepo on 11/27/25.
//

#ifndef WEATHEROBJ_H
#define WEATHEROBJ_H
#include <resources/QtCommon.h>



class weatherObj : public QObject {
    Q_OBJECT
    QString m_city;
    QString m_state = "kljasdf";
public:
    Q_INVOKABLE void store_city(QString city);
    weatherObj(QObject* parent = nullptr);
    Q_INVOKABLE QString returnCity();
    Q_INVOKABLE void terminalOutput();
    void update_state(QString state);
    signals:
    void resultsReady(QString formated);
};



#endif //WEATHEROBJ_H
