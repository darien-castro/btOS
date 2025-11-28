//
// Created by pablovepo on 11/25/25.
//

#ifndef WEATHERWEBAPP_H
#define WEATHERWEBAPP_H
#include <resources/QtCommon.h>
#include <resources/models/weatherApp/qmlFiles/weatherObj.h>

class weatherWebApp : public QWidget {
    Q_OBJECT
// ! --------------- variables --------------------
    std::unique_ptr<QQuickWidget> view;
    QUrl main_url;
    QHBoxLayout* main_layout;
    QWidget* widget_holder;
    weatherObj* qml_obj;


    //! ------------ functions ------------------
    void initialize_variables();
    void initialize_quickView();
    void setup_application();

    void set_context(QObject* object);
public:
    weatherWebApp(QWidget* parent = nullptr);
    QWidget* return_widget_state();
    QString return_city_from_qml();
    weatherObj* return_weatherObj();
};



#endif //WEATHERWEBAPP_H
