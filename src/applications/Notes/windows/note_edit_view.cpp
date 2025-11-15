//
// Created by pablovepo on 11/15/25.
//

#include "note_edit_view.h"


NoteEditView::NoteEditView(QSqlDatabase* parent, int noteId) : m_parent_db(parent), m_noteId(noteId){
    QHBoxLayout* test_layout = new QHBoxLayout;
    test_layout->addWidget(new QLabel("hello World"));
    setLayout(test_layout);
}