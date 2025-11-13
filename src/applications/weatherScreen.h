//
// Created by pablovepo on 10/30/25.
//

#ifndef WEATHER_H
#define WEATHER_H
#include <src/core/btApplication.h>


class weatherScreen : public btApplication {
    Q_OBJECT;
    std::string toChangeInfo = "";
    std::string key;
    std::string link;

    //------------ui_setup----------------------

    QVBoxLayout* top_weather_layout;
    QWidget* top_widget;
    QHBoxLayout* loc_layout;
    QHBoxLayout* time_date_layout;
    QHBoxLayout* temp_weather_layout;
    QHBoxLayout* next_temps;
    QHBoxLayout* multi_info_layout;
    QWidget* multi_info_widget;
    QHBoxLayout* final_layout;
        //--------widgets------------------

    QTextEdit* search_display;
    QLabel* time_date;
    QLabel* temp;
    QLabel* weather;
    QLabel* next_hour;
    QFrame* seperator;
    QLabel* next_two_hour;


    // ----------Multi info layouts--------------

    QVBoxLayout* rain_chance_layout;
    QLabel* rain_chance;

    QVBoxLayout* wind_speed_layout;
    QLabel* wind_speed;

    QVBoxLayout* uv_layout;
    QLabel* uv_info;



    //------------------------------------------

    public:
    weatherScreen();
    void setup_layout();
    void setup_widgets();
    void setup_connections();
    void set_styles();
    void set_style_sheet();

    void btAPP_SETUP() override;
    QWidget* btAPP_RETURN() override;
    void btAPP_CLOSED() override;
    QString returnAppName() override;
};



#endif //WEATHER_H
