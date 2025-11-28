//
// Created by pablovepo on 11/25/25.
//

#include "weatherWebApp.h"




weatherWebApp::weatherWebApp(QWidget* parent)
    : QWidget(parent)
{
    view = std::make_unique<QQuickWidget>();
    qml_obj = new weatherObj;

    view->rootContext()->setContextProperty("qmlobj", qml_obj);
    view->rootContext()->setContextProperty("appWidth", parent->width());
    view->rootContext()->setContextProperty("appHeight", parent->height());
    view->setResizeMode(QQuickWidget::SizeRootObjectToView);

    view->setSource(QUrl::fromLocalFile("/home/pablovepo/CLionProjects/btOS/resources/models/weatherApp/qmlFiles/weather.qml"));

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