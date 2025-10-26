// notesScreen.cpp
#include "notesScreen.h"

notesScreen::notesScreen(QWidget* parent) : QWidget(parent) {
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(new QLabel("Notes app is running..."), 0, Qt::AlignCenter);
    setLayout(layout);
}

QWidget* notesScreen::returnNotesWindow() {
    return this;
}
