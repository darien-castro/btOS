// NotesDbManager.cpp
#include "NotesDbManager.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QFileInfo>
#include <QDir>

// constructor
NotesDbManager::NotesDbManager(QString db_location)
{
    QString connectionName = "connection_name";

    QFileInfo fileInfo(db_location);
    QDir().mkpath(fileInfo.absolutePath());

    // Use unique connection name in case you create multiple managers
    connectionName = "notes_connection_";

    if (QSqlDatabase::contains(connectionName))
    {
        m_db = QSqlDatabase::database(connectionName);
        qDebug() << "Reusing existing connection";
    }
    else
    {
        m_db = QSqlDatabase::addDatabase("QSQLITE", connectionName);
        m_db.setDatabaseName(db_location);
        qDebug() << "Created new database connection";
    }

    if (!m_db.open())
    {
        qDebug() << "Failed to open database:" << m_db.lastError().text();
        throw std::runtime_error("Failed to open database");
    }

    qDebug() << "Database opened successfully at:" << db_location;
}

bool NotesDbManager::isOpen() const
{
    return m_db.isOpen();
}

int NotesDbManager::returnDbSize() const
{
    QSqlQuery query(m_db);
    if (!query.exec("SELECT COUNT(*) FROM notes")) {
        qDebug() << "COUNT(*) failed:" << query.lastError().text();
        return -1; // indicate error
    }
    if (!query.next()) {
        // unexpected, no row returned
        return 0;
    }
    return query.value(0).toInt();
}

bool NotesDbManager::initialQuery()
{
    QSqlQuery query(m_db);
    QString note_exec = "CREATE TABLE IF NOT EXISTS notes ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "title TEXT NOT NULL, "
        "content TEXT"
        ")";
    QString tag_exec = "CREATE TABLE IF NOT EXISTS tags ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "name TEXT UNIQUE NOT NULL"
        ")";
    QString note_tag_exec = "CREATE TABLE IF NOT EXISTS note_tags ("
        "note_id INTEGER NOT NULL, "
        "tag_id INTEGER NOT NULL, "
        "PRIMARY KEY (note_id, tag_id), "
        "FOREIGN KEY (note_id) REFERENCES notes(id), "
        "FOREIGN KEY (tag_id) REFERENCES tags(id)"
        ")";

    bool ok = true;

    if (!query.exec(note_exec))
    {
        qDebug() << "error initializing note table:" << query.lastError().text();
        ok = false;
    }
    if (!query.exec(tag_exec))
    {
        qDebug() << "error initializing tag table:" << query.lastError().text();
        ok = false;
    }
    if (!query.exec(note_tag_exec))
    {
        qDebug() << "error initializing note-tag table:" << query.lastError().text();
        ok = false;
    }

    return ok;
}

noteQMap NotesDbManager::getAllNotes() const
{
    noteQMap allNotes;
    if (!m_db.isOpen())
        return allNotes;

    QSqlQuery query(m_db);
    if (!query.exec("SELECT id, title, content FROM notes"))
    {
        qDebug() << "cannot retrieve values from 'notes':" << query.lastError().text();
        return allNotes;
    }
    while (query.next())
    {
        int id = query.value(0).toInt();
        QString title = query.value(1).toString();
        QString content = query.value(2).toString();
        allNotes.insert(id, {title, content});
    };
    return allNotes;
}


int NotesDbManager::nextNoteID()
{
    QSqlQuery q(m_db);

    // First try sqlite_sequence (works if table has had inserts before)
    q.exec("SELECT seq FROM sqlite_sequence WHERE name='notes'");
    if (q.next()) {
        return q.value(0).toInt() + 1;
    }

    // If no row in sqlite_sequence, table is new or no inserts yet.
    // Fall back to MAX(id) to detect if table is actually empty.
    q.exec("SELECT MAX(id) FROM notes");
    if (q.next()) {
        int maxId = q.value(0).toInt();
        if (!q.value(0).isNull()) {
            return maxId + 1;
        }
    }
    return 1;
}

int NotesDbManager::createNote(const QString& title, const QString& data)
{
    QSqlQuery query(m_db);
    query.prepare("INSERT INTO notes (title, content) VALUES (:title, :content)");
    query.bindValue(":title", title);
    query.bindValue(":content", data);
    if (!query.exec())
    {
        qDebug() << query.lastError().text();
        qDebug() << "didnt' save";
        return -1;
    }

    int id = query.lastInsertId().toInt();
    qDebug() << "saved: " << id;
    return id;
}

bool NotesDbManager::updateNote(int id, const QString& title, const QString& data)
{
    QSqlQuery query(m_db);
    query.prepare("UPDATE notes SET title = :title, content = :content WHERE id = :id");
    query.bindValue(":title", title);
    query.bindValue(":content",data);
    query.bindValue(":id",id);
    if (!query.exec())
    {
        qDebug() << "Failed!: at line NotesDbManager.cpp (line 170)";
        return false;
    }
    return true;
}

std::vector<QString> NotesDbManager::parseForTags(const QString& content)
{
    QString tag = "";
    std::vector<QString> tags;
    bool curr_tag = false;
    for (int i = 0; i < content.length(); i++)
    {
        if (curr_tag == true)
        {
            if (content[i] != ' ' && content[i] != '\n')
            {
                tag += content[i];
            }
            else
            {
                tags.push_back(tag);
                tag = "";
                curr_tag = false;
            }
        }
        if (content[i] == '#')
        {
            curr_tag = true;
        }
    }
    if (tag != "")
    {
        tags.push_back(tag);
    }
    return tags;
};

bool NotesDbManager::pushAllTags(const std::vector<QString>& tags)
{
    QSqlQuery query(m_db);
    query.prepare("INSERT INTO tags (name) VALUES (:name)");
    for (int i = 0; i < tags.size(); i++)
    {
        QString name = tags[i];
        query.bindValue(":name", name);
        query.exec();
    }
    return true;
};

bool NotesDbManager::addTagToNote(int tag_id, int note_id)
{
    QSqlQuery query(m_db);
    query.prepare("INSERT INTO note_tags (note_id, tag_id) VALUES (:note_id, :tag_id)");
    query.bindValue(":tag_id", tag_id);
    query.bindValue(":note_id", note_id);
    if (!query.exec())
    {
        qDebug() << "error in file NotesDbManager (line 228)";
        return false;
    }
    return true;
}


std::vector<int> NotesDbManager::vectQtoInt(std::vector<QString> example)
{
    std::vector<int> vect;
    QSqlQuery query(m_db);
    query.prepare("SELECT id FROM tags WHERE name = :name LIMIT 1");
    for (int i = 0; i < example.size(); i++)
    {
        QString name = example[i];
        query.bindValue(":name", name);
        if (!query.exec())
            continue;
        if (query.next()) {
            vect.push_back(query.value(0).toInt());
        }
    }
    return vect;
}

bool NotesDbManager::setTagsForNote(int note_id, const std::vector<int>& tags)
{
    QSqlQuery query(m_db);
    query.prepare("INSERT INTO note_tags (note_id, tag_id) VALUES (:note_id,:tag_id)");
    query.bindValue(":note_id", note_id);
    for (int i = 0; i < tags.size(); i++)
    {
        query.bindValue(":tag_id", tags[i]);
        if (!query.exec())
        {
            qDebug() << "Error in NotesDbManager (line 261)";
        };
    }
    return true;

}

bool NotesDbManager::updateTagsFromNT()
{
    // thought is, check if tags are included in
}


std::vector<QString> NotesDbManager::getAllTagNames()
{
    std::vector<QString> vect;
    QSqlQuery query(m_db);
    query.prepare("SELECT name FROM tags");
    if (!query.exec())
    {
        qDebug() << "ERROR in NotesDbManager (line 285)";
    }
    while (query.next())
    {
        QString name = query.value(0).toString();
        vect.push_back(name);
    }
    return vect;
}