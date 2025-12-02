//
// Created by pablovepo on 11/25/25.
//

#include "weatherWebApp.h"




weatherWebApp::weatherWebApp(QWidget* parent)
    : QWidget(parent)
{
    //! =========== Registration ===================
    qmlRegisterUncreatableType<weatherObj>(
        "com.weather", 1, 0, "WeatherCondition",
        "Cannot create WeatherCondition - enum access only"
    );

    view = std::make_unique<QQuickWidget>();
    qml_obj = new weatherObj;


    view->rootContext()->setContextProperty("qmlobj", qml_obj);
    view->rootContext()->setContextProperty("appWidth", parent->width());
    view->rootContext()->setContextProperty("appHeight", parent->height());
    view->rootContext()->setContextProperty("weatherScreen", parent);
    view->setResizeMode(QQuickWidget::SizeRootObjectToView);

    view->setSource(QUrl::fromLocalFile("/home/pablovepo/CLionProjects/btOS/resources/models/weatherApp/qmlFiles/qml_Screens/weather.qml"));

    auto* layout = new QVBoxLayout(this);
    layout->addWidget(view.get());
    qDebug()<< "got here";

}

QString weatherWebApp::return_city_from_qml()
{
    return qml_obj->returnCity();
}

weatherObj* weatherWebApp::return_weatherObj(){
    return qml_obj;
}

void weatherWebApp::updateQmlState(QString state){
    qml_obj->update_state(state);
}
void weatherWebApp::weatherObjEmit()
{
    qml_obj->resultsReady(qml_obj->returnCity() + ", " + qml_obj->returnState());
}
