//
// Created by pablovepo on 11/15/25.
//

#include "note_edit_view.h"


void NoteEditView::initializeLayouts(){
    m_top_layout = new QVBoxLayout();
    m_top_layout->setContentsMargins(0, 0, 0, 0);
    m_top_layout->setSpacing(0);

    m_title_layout = new QHBoxLayout();
    m_title_layout->setContentsMargins(0, 0, 0, 0);
    m_title_layout->setSpacing(0);

    m_text_area = new QScrollArea();
}

void NoteEditView::initializeWidgets(){
    m_note_title = new QLineEdit();
    m_note_title->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    m_note_title->setMinimumHeight(105);

    m_note_text_edit = new QTextEdit();
    m_back_button = new QPushButton();
    m_settings_button = new QPushButton();
}

void NoteEditView::styleWidgets(){
    m_note_title->setStyleSheet("QLineEdit{"
                                "background: black;"
                                "border:1px solid white;"
                                "font-size: 42px;"
                                "padding: 10px;"
                                "}");

    m_text_area->setStyleSheet("QScrollArea{"
                               "border: none;"
                               "}");

    this->setStyleSheet("QWidget#noteEditView{"
                        "border: 1px solid black;"
                        "}");
}

void NoteEditView::setupConnections(){
    connect(m_note_title, &QLineEdit::returnPressed, this, [this](){
        m_note_text_edit->setFocus();
    });
}

void NoteEditView::attatchWidgets(){
    m_title_layout->addWidget(m_note_title);
    m_top_layout->addLayout(m_title_layout, 0);

    m_text_area->setWidget(m_note_text_edit);
    m_text_area->setWidgetResizable(true);
    m_top_layout->addWidget(m_text_area, 1);
}

NoteEditView::NoteEditView(QWidget* parent, QSqlDatabase* dbparent, int noteId)
    : QWidget(parent), m_parent_db(dbparent), m_noteId(noteId){
    this->setObjectName("noteEditView");
    initializeLayouts();
    initializeWidgets();
    styleWidgets();
    attatchWidgets();
    setupConnections();
    this->setLayout(m_top_layout);
}