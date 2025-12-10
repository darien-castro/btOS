// notesScreen.cpp
#include "notesScreen.h"
#include <QGraphicsDropShadowEffect>

#include "resources/models/notesApp/noteTag.h"
#include "windows/note_edit_view.h"
/*
 ! -----------------------------------Application Setup---------------------------------------------------------------------
 */

void notesScreen::btAPP_SETUP(){

    databaseManager->initialQuery();
    _current_db_size = databaseManager->returnDbSize();

    setup_layouts();
    layout_styling();
    setup_widgets();
    widget_styling();
    add_widgits();
    initiate_connections();

    QWidget* main_screen = new QWidget();
    main_screen->setLayout(top_notes_layout);
    _window_stack->addWidget(main_screen);
    QVBoxLayout* vbox = new QVBoxLayout;
    vbox->addWidget(_window_stack);

    application->setLayout(vbox);
    application->setObjectName("notes");
    application->setStyleSheet("QWidget#notes{"
                               "background-color: rgba(7, 13, 15,1);"
                               "}");
    qDebug() <<"application width: " << application->parentWidget()->width();
}
void notesScreen::widget_styling(){
    header_widget->setStyleSheet("QLabel{"
                                 "color: rgba(255,255,255,225);"
                                 "font-size: 62px;"
                                 "font-weight: bold;"
                                 "}");
    header_widget->setWordWrap(true);
    button->setFixedSize(200,200);
    button->setIcon(QIcon("../resources/appData/Notes/imgs/plus_img.png")); // using resource path recommended
    button->setIconSize(QSize(65,65));
    button->setStyleSheet("QPushButton{"
                          "background-color: rgba(250,250,250,125);"
                          "border-radius: 25px;"
                          "}"
                          "QPushButton:hover{"
                          "background-color: rgba(250,250,250,185);"
                          "border-radius: 25px;"
                          "}");
}
/*
 ! ----------------------------------- Layout Functions---------------------------------------------------------------------
 */
void notesScreen::setup_layouts(){
    // applications widget setup
    application = new QWidget(this->parentWidget());

    _window_stack = new QStackedWidget();

    //layouts and areas setup
    top_notes_layout = new QVBoxLayout();
    top_notes_widget = new QWidget;
    header_layout = new QHBoxLayout();
    carousel_layout= new QScrollArea();
    note_card_scroll = new QScrollArea;
    note_card_view = new QGridLayout();
    carousel_hbox = new QHBoxLayout;
    carousel_widget = new QWidget;
    //---------------------------------
    qDebug() << "setup_layouts: Done!";
}

void notesScreen::layout_styling(){
    // tag layout height
    carousel_layout->setFixedHeight(80);
    // no scroll bar
    carousel_layout->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    carousel_layout->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    // hiding, and setting children colors
    carousel_layout->setStyleSheet("QScrollArea{"
                                  "background: transparent;"
                                  "color: white;"
                                  "}");
    //spacing between tags
    carousel_hbox->setSpacing(10);

    // title and new note margins
    header_layout->setContentsMargins(10,0,10,0);
    //spacing between note_cards
    note_card_view->setHorizontalSpacing(30);
    note_card_view->setVerticalSpacing(50);

    // carousel no scroll
    note_card_scroll->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

/*
 !
 ! -----------------------------------Widget Functions---------------------------------------------------------------------
 */
void notesScreen::setup_widgets(){
    //Widget Setup

    //Title
    header_widget = new QLabel("Notes");
    //new note button
    button = new QPushButton();
    //example cards, needed for inital grid placement
    qDebug() << "Finished Setting Up Widgets";
}

void notesScreen::populateNotes(NotesDbManager* database)
{
    if (!note_card_view->isEmpty()) {
        QLayoutItem* child;
        while ((child = note_card_view->takeAt(0)) != nullptr) {
            delete child->widget();
            delete child;
        }
    }

    int row = 0;
    int col = 0;

    noteQMap notesToRender;

    if (m_activeFilters.isEmpty()) {
        // CASE 1: No filters? Show EVERYTHING.
        notesToRender = database->getAllNotes();
    }
    else {
        // CASE 2: Filters active? Find specific IDs.
        QSet<int> noteIds;
        for (auto it = m_activeFilters.begin(); it != m_activeFilters.end(); it++) {
            qDebug() << "it: " << *it;
            std::vector<int> curr = database->getIdFromTags(*it);
            for (int id : curr) {
                qDebug() <<"id: " << id;
                noteIds.insert(id);
            }
        }
        qDebug() << "noteId Size: " << noteIds.size();

        // Now fetch the note details for these specific IDs
        for (int id : noteIds) {
            noteQMap curr;
            notesToRender.insert(id, database->getNote(id));
        }
    }
    qDebug() << "notesToRender Size: " << notesToRender.size();
    for (auto it = notesToRender.begin(); it != notesToRender.end(); ++it) {
        int currID = it.key();
        QString title = it.value().Title;
        QString content = it.value().Content;

        NoteCardModern* curr = new NoteCardModern(title, content);
        note_card_view->addWidget(curr, row, col);

        // FIX 1: Explicitly show the widget (just to be safe)
        curr->show();

        col++;
        if (col == 2) {
            col = 0;
            row++;
        }

        // Connections...
        connect(curr, &NoteCardModern::clicked, this, [this, currID, title, content](){
            NoteEditView* lol = new NoteEditView(this, currID, title, content, databaseManager);
            _window_stack->addWidget(lol);
            _window_stack->setCurrentWidget(lol);
            connect(lol, &NoteEditView::closed, this, [this, lol]() {
                populateNotes(databaseManager);
                _window_stack->removeWidget(lol);
            });
        });
    }

    // FIX 2: Refresh the container OUTSIDE the loop
    // This forces the "test" widget (inside the scroll area) to snap to the new grid size
    QWidget* container = note_card_scroll->widget();
    if (container) {
        container->adjustSize();
    }
};

void notesScreen::add_widgits(){
    //attach header
    header_layout->addWidget(header_widget);
    header_layout->addWidget(button,0, Qt::AlignCenter | Qt::AlignRight);

    // example of scroll capability
    // attatching tags
    QList<QPair<int, QString>> tagsVect = databaseManager->getAllTags();

    for (int i = 0; i < tagsVect.size(); i++)
    {
        noteTag* curr = new noteTag(this,tagsVect[i].second,tagsVect[i].first);
        connect(curr, &noteTag::clicked, this, [this, curr]()
        {
            // Debugging print to ensure timing is right
            qDebug() << "Tag Clicked:" << curr->returnTagId() << " New State:" << curr->Active();

            if (curr->Active())
            {
                m_activeFilters.insert(curr->returnTagId());
                qDebug() << "m_activeFilters size: "<< m_activeFilters.size();
            }
            else
            {
                m_activeFilters.remove(curr->returnTagId());
            }

            // You don't need the 'return' statement if you use if/else
            populateNotes(databaseManager);
        });
        carousel_hbox->addWidget(curr);
    }
    // widget needed for attaching to hbox
    carousel_widget->setLayout(carousel_hbox);
    carousel_widget->setStyleSheet("QWidget{"
                                   "background: transparent;}");
    carousel_layout->setWidget(carousel_widget);
    //---------------------------------------------

    note_card_scroll->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    populateNotes(databaseManager);

    top_notes_layout->addLayout(header_layout);
    top_notes_layout->addWidget(carousel_layout);
    QWidget* test = new QWidget;
    test->setStyleSheet("QWidget{"
                        "background: transparent;"
                        "}"
                        );
    test->setLayout(note_card_view);
    note_card_scroll->setWidget(test);
    top_notes_layout->addWidget(note_card_scroll, 0, Qt::AlignCenter);
    qDebug() << "Finished Adding Widgets";

}

/*
 ! -----------------------------------Connection Functions---------------------------------------------------------------------
 */
void notesScreen::initiate_connections(){
    qDebug() << "Pressed: New Note Button";
    _current_db_size++;
    connect(button, &QPushButton::clicked, this,[this](){
        NoteEditView* lol = new NoteEditView(this,-1,"","", databaseManager);
        _window_stack->addWidget(lol);
        _window_stack->setCurrentWidget(lol);
        connect(lol, &NoteEditView::closed, this, [this, lol]()
            {
                this->populateNotes(this->databaseManager);
                _window_stack->removeWidget(lol);
                lol->deleteLater();
            });
    });
    connect(_window_stack, &QStackedWidget::currentChanged, this, [this](){
        qDebug() << "logic to save to db here!";
    });
}
/*
 ! -----------------------------------Constructor/Destructor/Virtual---------------------------------------------------------------------
 */
notesScreen::notesScreen(QWidget* parent) : btApplication(parent)
{
    this->appName = "notes";
    setObjectName("notesScreen");
    setFixedWidth(parent->width());
    databaseManager = new NotesDbManager("../resources/appData/Notes/notes.db");
    qDebug() << "notesScreen Width: " << width();
}

notesScreen::~notesScreen(){
    notesScreen::btAPP_CLOSED();
}

QWidget* notesScreen::btAPP_RETURN(){
    return this->application;
}

void notesScreen::btAPP_CLOSED(){

}

QString notesScreen::returnAppName(){
    return appName;
}