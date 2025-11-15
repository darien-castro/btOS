//
// Created by pablovepo on 11/15/25.
//

#ifndef NOTE_EDIT_VIEW_H
#define NOTE_EDIT_VIEW_H
#include <resources/QtCommon.h>

class QSqlDatabase;
class notesScreen;

class NoteEditView : public QWidget {
    Q_OBJECT
    QSqlDatabase* m_parent_db;
    QString m_title;
    QString m_note_content;
    int m_noteId = -1;
public:
    // todo... need to intake some db variable, so that, we can input some note
    NoteEditView(QSqlDatabase* parent, int noteId);

private:

    //----------- Helper Functions ------------------
    void initializeLayouts();
    void initializeWidgets();
    void styleWidgets();
    // depending on if db is inputed as value or not
    QString loadNoteFromDatabase(int index);
    void saveNoteToDatabase();
    void closeNote();

    //----------- UI layouts ------------------
    QVBoxLayout* m_top_layout; // screen layout that will be attactched to objectwidget
    QHBoxLayout* m_top_bar_layout; // back, and text settings buttons
    QHBoxLayout* m_title_layout; // title here
    QScrollArea* m_text_area; // area where text will be input

    // may need other variables for scrollArea to work

    //----------- UI Variables ------------------
    QTextEdit* m_note_title;
    QTextEdit* m_note_text_edit;
    QPushButton* m_back_button;
    QPushButton* m_settings_button;

    // some of these may change due to stylistic features needed...




    signals:
    void closed();
};



#endif //NOTE_EDIT_VIEW_H
