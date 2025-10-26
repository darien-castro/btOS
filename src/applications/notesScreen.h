// notesScreen.h
#ifndef NOTESSCREEN_H
#define NOTESSCREEN_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>

class notesScreen : public QWidget {
    Q_OBJECT
public:
    explicit notesScreen(QWidget* parent = nullptr);
    QWidget* returnNotesWindow();
};

#endif
