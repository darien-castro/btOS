// notesScreen.cpp
#include "notesScreen.h"
#include <QGraphicsDropShadowEffect>

#include "resources/models/notesApp/newNote.h"
#include "resources/models/notesApp/noteTag.h"
#include "windows/note_edit_view.h"
/*
 ! -----------------------------------Application Setup---------------------------------------------------------------------
 */



void notesScreen::btAPP_SETUP(){
    // application setup;
    initiate_db();
    data_to_qmap();
    qDebug() << QMap_dataBase->size();
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
    header_widget = new QLabel("Hello Darien");
    //new note button
    button = new QPushButton();
    //example cards, needed for inital grid placement
    qDebug() << "Finished Setting Up Widgets";
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

    // Qmap to Card logic
    int row = 0;
    int col = 0;

    for (auto it = QMap_dataBase->begin(); it != QMap_dataBase->end(); ++it) {
        int id = it.key();
        QString title = it.value().Title;
        QString content = it.value().Content;

        NoteCardModern* curr = new NoteCardModern(title, content);
        note_card_view->addWidget(curr, row, col);

        col++;
        if (col == 2) {  // 2 columns
            col = 0;
            row++;
        }

        connect(curr, &NoteCardModern::clicked, this, [this, id, title, content](){
            NoteEditView* lol = new NoteEditView(this, id, title, content,QMap_dataBase);
            _window_stack->addWidget(lol);
            _window_stack->setCurrentWidget(lol);
            connect(lol, &NoteEditView::closed, this, [this, lol]()
            {
                _window_stack->removeWidget(lol);
            });
        });
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

/*
 ! -----------------------------------Connection Functions---------------------------------------------------------------------
 */
void notesScreen::initiate_connections(){
    qDebug() << "Pressed: New Note Button";
    _current_db_size++;
    connect(button, &QPushButton::clicked, this,[this](){
        NoteEditView* lol = new NoteEditView(this,_current_db_size,"","",QMap_dataBase);
        _window_stack->addWidget(lol);
        _window_stack->setCurrentWidget(lol);
        connect(lol, &NoteEditView::closed, this, [this, lol]()
            {
                _window_stack->removeWidget(lol);
            });
    });

    connect(_window_stack, &QStackedWidget::currentChanged, this, [this](){
        qDebug() << "logic to save to db here!";
    });

}

/*
 ! -----------------------------------Database Functions---------------------------------------------------------------------
 */
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
    QMap_dataBase = std::make_shared<QMap<int, NoteStruct>>();
}
void notesScreen::data_to_qmap(){
    if (db.isOpen())
    {
        QSqlQuery query(db);
        if (!query.exec("SELECT id, title, content FROM notes"))
        {
            qDebug() << "cannot retrieve values: 'id', 'title, 'content' from 'notes'";
            return;
        }
        while (query.next())
        {
            int id = query.value(0).toInt();
            QString title = query.value(1).toString();
            QString content = query.value(2).toString();
            QMap_dataBase->insert(id, {title,content});
        }
        qDebug() << "Copy from DB to QMap Complete";
        qDebug() << "QMap Size: " << QMap_dataBase->size();
    }
    else
    {
        qDebug() << "error copying";
        return;
    }
    _current_db_size = QMap_dataBase->size();
}


// toDo, neex to fix logic, assumes values don't get deleted, and starts at 0? obviously not correct, maybe we should always gatehr from db every time? idk

// ? not pushing to db, because logic is flawed on how we store it.
void notesScreen::qmap_to_data(){

}

/*
 ! -----------------------------------Constructor/Destructor/Virtual---------------------------------------------------------------------
 */
notesScreen::notesScreen(QWidget* parent) : btApplication(parent) {
    this->appName = "notes";
    setObjectName("notesScreen");
    setFixedWidth(parent->width());
    qDebug() << "notesScreen Width: " << width();
}
notesScreen::~notesScreen(){
    notesScreen::btAPP_CLOSED();
}

QWidget* notesScreen::btAPP_RETURN(){
    return this->application;
}

void notesScreen::btAPP_CLOSED(){
    if (db.isOpen())
    {
        db.close();
    }
}

QString notesScreen::returnAppName(){
    return appName;
}