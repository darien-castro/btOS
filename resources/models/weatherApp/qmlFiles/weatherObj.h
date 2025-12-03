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

    //! ==========================Weather Variables==========================

    QString m_city;
    QString m_state;
    QMap<int,FutureData>* m_futureMap = nullptr;

    //!=======================================================================


    //! ==========================Settings==========================
    bool onScreenAnimations = true; // may change to different thing
    //!=======================================================================

public:

    weatherObj(QObject* parent = nullptr);

    //! ==========================Enum==========================
    enum currentWeather {
        STORMY, DRIZZLY, RAINY, SNOWY, MISTY, CLOUDY, CLEAR, NONE
    };
    Q_ENUM(currentWeather);

    //* enum setting

    currentWeather m_weatherCondition = currentWeather::NONE;
    //!=======================================================================


    //! ==========================Q_Properties===============================
    Q_PROPERTY(currentWeather weatherCondition READ weatherCondition NOTIFY weatherConditionChanged)
    //! =======================================================================



    //! ==========================Getter Functions===============================
    currentWeather weatherCondition() { return m_weatherCondition; }

    QString returnState() { return m_state;}

    //* Q_Invokables

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

    Q_INVOKABLE QString returnCity();

    //! =========================================================================


    //! ==========================Setting Weather Functions===============================


    void update_state(QString state);

    void update_condition(currentWeather condition);\

    void set_qmap(QMap<int,FutureData>* futureMap) {
        m_futureMap = futureMap;
        emit weatherConditionChanged();
    }

    Q_INVOKABLE void store_city(QString city);

    Q_INVOKABLE void terminalOutput();

    //! ==========================Signals===============================

    signals:
        void resultsReady(QString formated);
    void initialresults(QString results);
    void weatherConditionChanged();
};
#endif //WEATHEROBJ_H
