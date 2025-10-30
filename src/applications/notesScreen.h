// notesScreen.h
#ifndef NOTESSCREEN_H
#define NOTESSCREEN_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>

#include "src/core/btApplication.h"


class notesScreen : public btApplication {
    Q_OBJECT
public:
    notesScreen();
    QWidget* returnNotesWindow();
    void btAPP_SETUP() override;
    QWidget* btAPP_RETURN() override;
    void btAPP_CLOSED() override;
    QString returnAppName() override;
};

#endif
