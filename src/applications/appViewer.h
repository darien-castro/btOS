//
// Created by pablovepo on 10/29/25.
//

#ifndef APPVIEWER_H
#define APPVIEWER_H
#include <resources/QtCommon.h>

#include "src/core/btShell.h"


class appViewer : public QWidget {
    btShell* mainShell;
public:
    appViewer(btShell* mS);
};



#endif //APPVIEWER_H
