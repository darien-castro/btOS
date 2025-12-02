//
// Created by pablovepo on 12/2/25.
//

#ifndef FUTUREDATA_H
#define FUTUREDATA_H
struct FutureData
{
    QString m_time;
    QString m_temp;

    // ✅ Add default constructor
    FutureData() : m_time(""), m_temp("") {}

    // Existing constructor
    FutureData(const QString& time, const QString& temp)
        : m_time(time), m_temp(temp) {}
};
#endif //FUTUREDATA_H
