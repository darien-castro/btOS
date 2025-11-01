//
// Created by pablovepo on 10/29/25.
//

#include "appViewer.h"
#include <thread>
#include <chrono>
#include "src/core/screenManager.h"

void appViewer::blurBackgroundImage() {
    QString blurExecutable = "/home/pablovepo/CLionProjects/btOS/resources/utils/blurImage";

    QProcess process;
    QStringList args;
    process.start(blurExecutable, args);
    qDebug() << "ran";
    process.waitForFinished(-1);
    qDebug() <<"finished Here";

}

appViewer::appViewer(btShell* mS){
    setObjectName("appViewer");
    QString saveLoc = "/home/pablovepo/CLionProjects/btOS/resources/temp/curr_screen";
    QString saveFile = saveLoc + "/screen_appViewer_temp2.png";
    this->mainShell = mS;
    blurBackgroundImage();

    QVBoxLayout* main = new QVBoxLayout(this);
    main->setContentsMargins(0, 0, 0, 0);
    main->setSpacing(0);
    main->setAlignment(Qt::AlignCenter);  // centers *all* child widgets

    QLabel* mainLabel = new QLabel("hello World");
    mainLabel->setStyleSheet("color: white; font-size: 24px;");

    main->addWidget(mainLabel, 0, Qt::AlignCenter);

    setStyleSheet(
    "QWidget {"
    "background-image: url(/home/pablovepo/CLionProjects/btOS/resources/temp/curr_screen/screen_appViewer_temp2.png);"
    "background-position: center;"
    "background-repeat: no-repeat;"
    "background-attachment: fixed;"
    "background-origin: content;"
    "background-size: cover;"   // ✅ makes it fill the whole area
    "}"
);


}
