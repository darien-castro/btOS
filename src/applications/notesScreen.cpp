// notesScreen.cpp
#include "notesScreen.h"
#include <QGraphicsDropShadowEffect>
notesScreen::notesScreen() {
    this->appName = "notes";
}

QWidget* notesScreen::returnNotesWindow() {
    return this;
}

void notesScreen::btAPP_SETUP(){
    this->application = new QWidget;
    this->application->setObjectName("notesScreen");
    QVBoxLayout* layout = new QVBoxLayout(this);
    QLabel* text = new QLabel("Notes app is running...");

    text->setStyleSheet("QLabel{"
                        ""
                        "color: #000000;"
                        "}");
    layout->addWidget(text, 0, Qt::AlignCenter);

    this->application->setLayout(layout);
    this->application->setStyleSheet("QWidget{"
                  ""
                  "}");
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
