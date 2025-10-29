// notesScreen.cpp
#include "notesScreen.h"
#include <QGraphicsDropShadowEffect>
notesScreen::notesScreen(QWidget* parent) : QWidget(parent) {
    this->setObjectName("notesScreen");
    QVBoxLayout* layout = new QVBoxLayout(this);
    QLabel* text = new QLabel("Notes app is running...");

    text->setStyleSheet("QLabel{"
                        ""
                        "color: #000000;"
                        "}");
    layout->addWidget(text, 0, Qt::AlignCenter);

    setLayout(layout);
    setStyleSheet("QWidget{"
                  ""
                  "}");
}

QWidget* notesScreen::returnNotesWindow() {
    return this;
}
