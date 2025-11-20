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
#include <resources/models/notesApp/noteCard.h>
#include <resources/models/notesApp/noteTag.h>

class notesScreen : public btApplication {
    Q_OBJECT
    QSqlDatabase db;
    int _current_db_size;
    int _current_note;
public:
    notesScreen(QWidget* parent);
    // construction
    void setup_layouts();
    void setup_widgets();
    void layout_styling();
    //styling
    void widget_styling();

    //connection
    void initiate_connections();
    //adding widgets
    void add_widgits();
    //helper function
    //db
    void initiate_db();
    void add_note_db();
    // deprecated, but can use logic for db
    void populate_prev_notes();
    // deprecated...
    void setVariablesNull();


    //overridden
    void btAPP_SETUP() override;
    QWidget* btAPP_RETURN() override;
    void btAPP_CLOSED() override;
    QString returnAppName() override;
    ~notesScreen();
private:
    // ui variables
    // main containers
    QVBoxLayout* top_notes_layout;
    QWidget* top_notes_widget;
    QHBoxLayout* header_layout;
    QScrollArea* carousel_layout;
    QHBoxLayout* carousel_hbox;
    QWidget* carousel_widget;
    QGridLayout* note_card_view;
    QScrollArea* note_card_scroll;
    // main widgets
    QLabel* header_widget;
    QPushButton* button;
    noteTag* example_tag1;
    noteTag* example_tag2;
    NoteCardModern* card1;
    NoteCardModern* card2;
    NoteCardModern* card3;
    NoteCardModern* card4;
};
#endif