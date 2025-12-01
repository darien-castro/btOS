//
// Created by pablovepo on 10/30/25.
//

#ifndef WEATHER_H
#define WEATHER_H
#include <cpr/cpr.h>
#include <src/core/btApplication.h>
#include <resources/models/weatherApp/weatherWebApp.h>
#include <nlohmann/json.hpp>

class weatherScreen : public btApplication {
    Q_OBJECT
    Q_PROPERTY(int temperature READ temperature WRITE setTemperature NOTIFY temperatureChanged)
    Q_PROPERTY(QString description READ description WRITE setDescription NOTIFY descriptionChanged)

private:
    std::string toChangeInfo = "";
    std::string key;
    std::string link;
    std::string units;
    QString name;
    cpr::Response m_response;

    int m_curr_temp = 0;
    QString m_curr_desc = "lmao";
    QString m_curr_country;

    QHBoxLayout* m_qml_holder;
    weatherWebApp* weather_qml;

public:
    weatherScreen(QWidget* parent);
    void setup_layout();
    void setup_widgets();
    void setup_connections();
    void initiate_application();

    void update_response(const QString& name);
    void update_data(const QString& name);
    bool data_error(cpr::Response response);
    bool parse_api_call();
    void weather_api_call(const QString& city);

    void btAPP_SETUP() override;
    QWidget* btAPP_RETURN() override;
    void btAPP_CLOSED() override;
    QString returnAppName() override;

    // Getters
    int temperature() const { return m_curr_temp; }
    QString description() const { return m_curr_desc; }

    // Setters - FIXED
    void setTemperature(int temp) {
        if (m_curr_temp != temp) {
            m_curr_temp = temp;  // ✅ Fixed: assign to m_curr_temp
            emit temperatureChanged();
            qDebug() << "Temperature updated:" << temp;
        }
    }

    void setDescription(const QString& desc) {
        if (m_curr_desc != desc) {  // ✅ Fixed: compare m_curr_desc to desc
            m_curr_desc = desc;
            emit descriptionChanged();
            qDebug() << "Description updated:" << desc;
        }
    }

    signals:
        void temperatureChanged();
        void descriptionChanged();
};


#endif //WEATHER_H
