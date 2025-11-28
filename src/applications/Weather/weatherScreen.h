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
    Q_OBJECT;
    std::string toChangeInfo = "";
    std::string key;
    std::string link;
    std::string units;
    QString name;
    cpr::Response m_response;
    //------------ui_setup----------------------
    QHBoxLayout* m_qml_holder;

        //--------widgets------------------



    weatherWebApp* weather_qml;

    // ----------Multi info layouts--------------




    //------------------------------------------

    public:
    weatherScreen(QWidget* parent);
    void setup_layout();
    void setup_widgets();
    void setup_connections();
    void initiate_application();

    // api call functions
    void update_response(const QString& name);
    void update_data(const QString& name);
    bool data_error(cpr::Response response);
    bool parse_api_call();

    void weather_api_call(const QString& city);


    void btAPP_SETUP() override;
    QWidget* btAPP_RETURN() override;
    void btAPP_CLOSED() override;
    QString returnAppName() override;
};



#endif //WEATHER_H
