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
    m_note_title = new QLineEdit(m_title);
    m_note_title->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    m_note_title->setMinimumHeight(105);

    m_note_text_edit = new QTextEdit(m_note_content);
    m_back_button = new QPushButton();
    m_settings_button = new QPushButton();
    buttonLol = new QPushButton("Quit");

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

    connect(buttonLol, &QPushButton::clicked, this, [this](){
        QString title = m_note_title->text();
        QString content = m_note_text_edit->toPlainText();
        std::vector<QString> test = m_parent_db->parseForTags(content);
        if (m_noteId == -1 && title != "")
        {
            // Creating new note - createNote returns int (the new ID)
            int newId = m_parent_db->createNote(title, content);
            if (newId == -1)
            {
                qDebug() << "Error: Failed to create note";
            }
            else
            {
                m_noteId = newId;  // Store the new ID
                if (!m_parent_db->pushAllTags(test))
                {
                    qDebug() << "saving notes failed at 'note_edit_view' (line 71)";
                };
                if (!m_parent_db->setTagsForNote(m_noteId, m_parent_db->vectQtoInt(test)))
                {
                    qDebug() << "failed to save notes to note_tags";
                };
            }
        }
        else if (m_noteId >= 0)
        {
            if (!m_parent_db->updateNote(m_noteId, title, content))
            {
                qDebug() << "Error: Failed to update note";
            }
            else
            {
                qDebug() << "Note updated successfully";
            }
        }

        // then combine, save every note in vector, to said note id

        emit closed();
    });
}

void NoteEditView::attatchWidgets(){
    m_title_layout->addWidget(m_note_title);
    m_title_layout->addWidget(buttonLol);
    m_top_layout->addLayout(m_title_layout, 0);

    m_text_area->setWidget(m_note_text_edit);
    m_text_area->setWidgetResizable(true);
    m_top_layout->addWidget(m_text_area, 1);
}

NoteEditView::NoteEditView(QWidget* parent, int noteId, QString title, QString content, NotesDbManager* db)
    : QWidget(parent),m_noteId(noteId), m_title(title), m_note_content(content), m_parent_db(db){
    this->setObjectName("noteEditView");
    initializeLayouts();
    initializeWidgets();
    styleWidgets();
    attatchWidgets();
    setupConnections();
    this->setLayout(m_top_layout);
    qDebug() << "note index: " << noteId;
}