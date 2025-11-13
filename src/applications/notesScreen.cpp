// notesScreen.cpp
#include "notesScreen.h"
#include <QGraphicsDropShadowEffect>
notesScreen::notesScreen() {
    this->appName = "notes";
    setObjectName("notesScreen");
}
void notesScreen::setup_layouts(){
    _mainNotesLayout= new QHBoxLayout(this->application);
    _noteWindow = new QVBoxLayout();
    _leftScrollArea = new QScrollArea();
    _leftScrollArea->setWidgetResizable(false);
    _leftAreaWidget = new QWidget();
    _previousNotesContainer = new QVBoxLayout();
    _rightScreen = new QWidget();
    _buttonLayout = new QVBoxLayout();
}
void notesScreen::setup_buttons(){
    _compact = new QPushButton("<-");
    _newNote = new QPushButton("+");
    _notesText = new QTextEdit();
    _buttons = new QWidget();
}

void notesScreen::add_widgits(){
    _leftScrollArea->setWidget(_leftAreaWidget);
    _noteWindow->addWidget(_notesText);
    _rightScreen->setLayout(_noteWindow);
    _mainNotesLayout->addWidget(_leftScrollArea);
    _mainNotesLayout->addWidget(_rightScreen);
    _compact->setFixedSize(100,50);
    _newNote->setFixedSize(100,50);

    _buttonLayout->addWidget(_compact,0,Qt::AlignTop);
    _buttonLayout->addWidget(_newNote,0,Qt::AlignTop);
    _buttonLayout->setSpacing(0);
    _buttonLayout->setContentsMargins(0,0,0,0);
    _buttons->setLayout(_buttonLayout);
    _mainNotesLayout->addWidget(_buttons);
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
        QPushButton* curr = new QPushButton(title);
        curr->setFixedSize(200,40);
        _previousNotesContainer->addWidget(curr,0,Qt::AlignCenter);
        connect(curr, &QPushButton::clicked, this, [this,content, title, noteID](){
            _current_note = noteID;
            _notesText->setText(title + "\n" + content);
            qDebug() << content;
            this->application->update();
        });
    }
}
void notesScreen::initiate_connections(){
    connect(_compact, &QPushButton::pressed, this, [=]() {
    if (_mainNotesLayout->indexOf(_leftScrollArea) != -1) {
        _mainNotesLayout->removeWidget(_leftScrollArea);
        _leftScrollArea->hide();
        _compact->setText("->");
    } else {
        _mainNotesLayout->insertWidget(0, _leftScrollArea);
        _leftScrollArea->show();
        _compact->setText("<-");
    }
    });
    connect(this->application, &QObject::destroyed, this, [this]() {
    this->btAPP_CLOSED();
});
    connect(_newNote, &QPushButton::clicked, this, [this](){
        if (_current_note > _current_db_size)
        {
            qDebug() << "error: note already new...";
            return;
        }
        _notesText->setText("");
        _current_note = _current_db_size + 1;
    });
}




void notesScreen::btAPP_SETUP(){
    initiate_db();
    this->application = new QWidget;
    setup_layouts();
    setup_buttons();
    populate_prev_notes();
    add_widgits();
    initiate_connections();
    QSqlQuery max("SELECT MAX(id) FROM notes", db);
    if (max.next())
    {
        _current_db_size = max.value(0).toInt();
        _current_note = _current_db_size + 1;
    }

}


QWidget* notesScreen::btAPP_RETURN(){
    return this->application;
}

void notesScreen::btAPP_CLOSED(){
    QString saveText = _notesText->toPlainText();
    qDebug() << "savedText:" << saveText;

    if (_current_note <= _current_db_size)
    {
        qDebug() << "cannot save same note";
        return;
    }

    if (saveText == "")
    {
        qDebug() << "closed without changes";
        return;
    }
    QString title;
    QString content;
    int newlineIndex = saveText.indexOf('\n');
    if (newlineIndex == -1) {
        // no newline found
        title = saveText.trimmed();
        content = "";
    } else {
        title = saveText.left(newlineIndex).trimmed();
        content = saveText.mid(newlineIndex + 1).trimmed();
    }
    qDebug() << "title:" << title;
    qDebug() << "content:" << content;
    QSqlQuery query(db);
    query.prepare("INSERT INTO notes (title, content) VALUES(:value1, :value2)");
    query.bindValue(":value1", title);
    query.bindValue(":value2", content);

    if (!query.exec()) {
        // Handle error
        qDebug() << "Error inserting data: " << query.lastError().text();
    } else {
        qDebug() << "Data inserted successfully.";
    }

    setVariablesNull();
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
    _mainNotesLayout = nullptr;
    _leftAreaWidget = nullptr;
    _leftScrollArea = nullptr;
    _previousNotesContainer = nullptr;
    _noteWindow = nullptr;
    _rightScreen = nullptr;
    _buttons = nullptr;
    _notesText = nullptr;
    _compact = nullptr;
    _newNote = nullptr;
    _buttonLayout = nullptr;
}

notesScreen::~notesScreen(){
    notesScreen::btAPP_CLOSED();
}
