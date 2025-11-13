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
    //maybe not necessary, but objects exist
    void setVariablesNull();
    void btAPP_SETUP() override;
    QWidget* btAPP_RETURN() override;
    void btAPP_CLOSED() override;
    QString returnAppName() override;
    ~notesScreen();
private:
    //main ui containers
    QHBoxLayout* _mainNotesLayout;
//----------------------------------
        //left ui containers
    QScrollArea* _leftScrollArea;
    QVBoxLayout* _previousNotesContainer;
    QWidget* _leftAreaWidget;
        //left ui buttons
            //none....
//----------------------------------
        //right ui
    QVBoxLayout* _noteWindow;
    QVBoxLayout* _buttonLayout;
        //widgets
    QWidget* _rightScreen;
    QTextEdit* _notesText;
    QWidget* _buttons;
        //buttons
    QPushButton* _compact;
    QPushButton* _newNote;
};

#endif
