//
// Created by pablovepo on 11/27/25.
//

#ifndef WEATHEROBJ_H
#define WEATHEROBJ_H
#include <resources/QtCommon.h>

#include "resources/models/weatherApp/FutureData.h"
struct FutureData;
class weatherScreen;

class weatherObj : public QObject {
    Q_OBJECT
    QString m_city;
    QString m_state;
    bool onScreenAnimations = true;
    QMap<int,FutureData>* m_futureMap = nullptr;

public:
    enum currentWeather {
        STORMY, DRIZZLY, RAINY, SNOWY, MISTY, CLOUDY, CLEAR, NONE
    };
    Q_ENUM(currentWeather);

    currentWeather m_weatherCondition = currentWeather::NONE;

    Q_PROPERTY(currentWeather weatherCondition READ weatherCondition NOTIFY weatherConditionChanged)

    currentWeather weatherCondition() { return m_weatherCondition; }

    Q_INVOKABLE void store_city(QString city);
    weatherObj(QObject* parent = nullptr);
    Q_INVOKABLE QString returnCity();
    QString returnState() { return m_state; }
    Q_INVOKABLE void terminalOutput();
    void update_state(QString state);
    void update_condition(currentWeather condition);

    void set_qmap(QMap<int,FutureData>* futureMap) {
        m_futureMap = futureMap;
        emit weatherConditionChanged();  // ✅ Emit to trigger updates
    }

    Q_INVOKABLE QString getTimeAtIndex(int index) {
        if (m_futureMap != nullptr && m_futureMap->contains(index))
            return m_futureMap->value(index).m_time;
        return "";
    }

    Q_INVOKABLE QString getTempAtIndex(int index) {
        if (m_futureMap != nullptr && m_futureMap->contains(index))
            return m_futureMap->value(index).m_temp;
        return "";
    }

    signals:
        void resultsReady(QString formated);
    void initialresults(QString results);
    void weatherConditionChanged();
};



#endif //WEATHEROBJ_H
