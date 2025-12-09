//
// Created by pablovepo on 12/8/25.
//

#ifndef NOTESDBMANAGER_H
#define NOTESDBMANAGER_H
#include <QSqlDatabase>
#include <resources/QtCommon.h>
#include <resources/models/notesApp/NoteStruct.h>
#include <resources/models/notesApp/tagStruct.h>

using noteQMap = QMap<int, NoteStruct>;
using tagQMap = QMap<int, tagStruct>;

class NotesDbManager {
    QSqlDatabase m_db;
public:
    NotesDbManager(QString db_location);
    bool isOpen() const;
    int returnDbSize() const;

    // general functions
    bool initialQuery();
    noteQMap getAllNotes() const;
    bool isOpen();


    // Note Functions
    bool createNote(const QString& title, const QString& data);
    bool deleteNote(int id);
    bool updateNote(int id, const QString& title, const QString& data);
    int nextNoteID();

    NoteStruct getNote(int id);

    // Tag Functions
    int createTag(const QString& title);
    tagStruct getTag(int id);
    tagQMap getAllTags();

    // note-tag relationships
    bool addTagToNote(int tag_id, int note_id);
    bool removeTagFromNote(int tag_id, int note_id);
    bool setTagsForNote(int note_id, const QStringList& tags_list);
    bool clearTagsFromNote(int note_id, const QStringList& tags_list);


    signals:
    void noteCreated();
    void noteDeleted();
    void noteUpdated();
    void tagCreated();



};



#endif //NOTESDBMANAGER_H
