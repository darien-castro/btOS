// notesScreen.cpp
#include "notesScreen.h"
#include <QGraphicsDropShadowEffect>
notesScreen::notesScreen() {
    this->appName = "notes";
    setObjectName("notesScreen");
}

void notesScreen::btAPP_SETUP(){
    this->application = new QWidget;
    QVBoxLayout* layout = new QVBoxLayout(this);
    QLabel* text = new QLabel("Notes app is running...");
    text->setObjectName("test");
    /*text->setStyleSheet("QLabel#test{"
                        "background-color: #ff0000;"
                        "color: #000000;"
                        "}");*/
    layout->addWidget(text, 0, Qt::AlignCenter);

    this->application->setLayout(layout);
}


QWidget* notesScreen::btAPP_RETURN(){
    return this->application;
}

void notesScreen::btAPP_CLOSED(){
    QWidget* toDel = application;
    application = nullptr;
    delete toDel;
}

QString notesScreen::returnAppName(){
    return appName;
}
