// notesScreen.cpp
#include "notesScreen.h"
#include <QGraphicsDropShadowEffect>

#include "resources/models/notesApp/newNote.h"

notesScreen::notesScreen() {
    this->appName = "notes";
    setObjectName("notesScreen");
}
void notesScreen::setup_layouts(){
    // applications widget setup
    this->application = new QWidget;

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

void notesScreen::setup_widgets(){
    //Widget Setup

    //Title
    header_widget = new QLabel("Hello Darien");
    //new note button
    button = new QPushButton();
    //example cards, needed for inital grid placement
    card1 = new NoteCardModern("Hello World", "my name is darien");
    card2 = new NoteCardModern("Hello World", "my name is darien");
    card3 = new NoteCardModern("Hello World", "my name is darien");

    qDebug() << "Finished Setting Up Widgets";
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



void notesScreen::add_widgits(){
    //attach header
    header_layout->addWidget(header_widget);
    header_layout->addWidget(button,0, Qt::AlignCenter | Qt::AlignRight);

    // example of scroll capability
    // attatching tags
    for (int i = 0; i < 100; i++)
    {
        noteTag* curr = new noteTag;
        carousel_hbox->addWidget(curr);
    }
    // widget needed for attaching to hbox
    carousel_widget->setLayout(carousel_hbox);
    carousel_widget->setStyleSheet("QWidget{"
                                   "background: transparent;}");
    carousel_layout->setWidget(carousel_widget);
    //---------------------------------------------

    // initial grid layout
    note_card_view->addWidget(card1,0,0);
    note_card_view->addWidget(card2,0,1);
    note_card_view->addWidget(card3,1,0);
    //example logic
    for (int i = 0; i < 40; i++)
    {
        NoteCardModern* curr = new NoteCardModern("Hello World", "my name is darien");
        note_card_view->addWidget(curr);
    }

    // addding widgets to "top_screen"
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


void notesScreen::populate_prev_notes(){
    QSqlQuery query(db);
    if (!query.exec("SELECT id, Title, content FROM notes"))
    {
        qDebug() << "couldn't gather info from table";
    }
    while (query.next())
    {
        int noteID = query.value(0).toInt();
        QString title = query.value(1).toString();
        QString content = query.value(2).toString();
        qDebug() << "card here...";
        /*connect(curr, &QPushButton::clicked, this, [this,content, title, noteID](){
            connect Logic lol
        });*/
    }
}
void notesScreen::initiate_connections(){

}




void notesScreen::btAPP_SETUP(){

    setup_layouts();
    layout_styling();
    setup_widgets();
    widget_styling();
    add_widgits();
    application->setLayout(top_notes_layout);
    application->setObjectName("notes");
    application->setStyleSheet("QWidget#notes{"
                               "background-color: #000000;"
                               "}");
}


QWidget* notesScreen::btAPP_RETURN(){
    return this->application;
}

void notesScreen::btAPP_CLOSED(){
    //save logic
}

QString notesScreen::returnAppName(){
    return appName;
}
void notesScreen::initiate_db() {
    QString connectionName = "notes_connection";

    // Ensure directory exists before touching the file
    QDir().mkpath("../resources/appData/Notes");

    // Reuse the existing connection if it already exists
    if (QSqlDatabase::contains(connectionName)) {
        db = QSqlDatabase::database(connectionName);
    } else {
        db = QSqlDatabase::addDatabase("QSQLITE", connectionName);
        db.setDatabaseName("../resources/appData/Notes/notes.db");
    }
    if (!db.open()) {
        qDebug() << "Couldn't open Notes Database:" << db.lastError().text();
        return;
    }
    // Use QSqlQuery to execute SQL on this connection
    QSqlQuery query(db);
    bool ok = query.exec(
        "CREATE TABLE IF NOT EXISTS notes ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "title TEXT NOT NULL, "
        "content TEXT)"
    );
    if (!ok) {
        qDebug() << "Error creating notes table:" << query.lastError().text();
    } else {
        qDebug() << "Notes database opened successfully.";
    }
}

void notesScreen::setVariablesNull(){

}

notesScreen::~notesScreen(){
    notesScreen::btAPP_CLOSED();
}
