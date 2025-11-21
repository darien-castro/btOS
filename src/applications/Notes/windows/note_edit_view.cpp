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
        toParentQmap();
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

NoteEditView::NoteEditView(QWidget* parent, int noteId, QString title, QString content, std::shared_ptr<noteQMap> parent_qmap)
    : QWidget(parent),m_noteId(noteId), m_title(title), m_note_content(content), parentQmap(parent_qmap){
    this->setObjectName("noteEditView");
    initializeLayouts();
    initializeWidgets();
    styleWidgets();
    attatchWidgets();
    setupConnections();
    this->setLayout(m_top_layout);
    qDebug() << "note index: " << noteId;
}

void NoteEditView::toParentQmap(){
    QString Title = m_note_title->text();
    QString Content = m_note_text_edit->toPlainText();
    qDebug() << "noteID: " <<m_noteId;
    qDebug() << "at closing title: " << Title;
    if (!parentQmap->contains(m_noteId) && Title != "")
    {
        parentQmap->insert(m_noteId, {Title, Content});
        qDebug() << "saved to Qmap (not db)";
        emit closed();
        return;
    }
    qDebug() << "didnt' save to Qmap (not db), note exists &/or Title is blank";
    emit closed();

}
