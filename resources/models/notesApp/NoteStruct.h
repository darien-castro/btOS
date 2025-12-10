//
// Created by pablovepo on 11/20/25.
//

#ifndef NOTESTRUCT_H
#define NOTESTRUCT_H
#include <resources/QtCommon.h>


struct NoteStruct {
    QString Title;
    QString Content;
    NoteStruct(QString title, QString content) : Title(title), Content(content){};
};



#endif //NOTESTRUCT_H
