// notesScreen.h
#ifndef NOTESSCREEN_H
#define NOTESSCREEN_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QDir>
#include <QDebug>

#include "src/core/btApplication.h"


class notesScreen : public btApplication {
    Q_OBJECT
    QSqlDatabase db;
    int _current_db_size;
    int _current_note;

public:
    notesScreen();
    //layout construction
    void setup_layouts();
    void setup_buttons();
    void populate_prev_notes();
    void initiate_connections();

    //adding widgets
    void add_widgits();

    //db functions
    void initiate_db();
    void add_note_db();

    //destruction functions
    void setVariablesNull();


    void btAPP_SETUP() override;
    QWidget* btAPP_RETURN() override;
    void btAPP_CLOSED() override;
    QString returnAppName() override;
    ~notesScreen();
private:
    //ui containers
    QHBoxLayout* _mainLayout;
    QScrollArea* _leftScrollArea;
    QWidget* _leftAreaContainer;
    QVBoxLayout* _previousNotesContainer;
    //left side
    QVBoxLayout* _noteWindow;
    //right side
    QWidget* _rightScreen;
    QWidget* _buttons;
    // ui widgets
    QTextEdit* _notesText;
    QPushButton* _compact;
    QPushButton* _newNote;

    QVBoxLayout* _buttonLayout;
};

#endif
