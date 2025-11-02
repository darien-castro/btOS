//
// Created by pablovepo on 10/29/25.
//

#include "appViewer.h"
#include "src/core/screenManager.h"

void appViewer::buttonSetup(QPushButton* button){
    button->setStyleSheet("QPushButton{"
                          "height: 50px;"
                          "width: 5px;"
                          "background: #D8A65C;"
                          "border-radius: 10px;"
                          "font-size: 16px;"
                          "color: #000000;"
                          "}");
}

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

    /*QVBoxLayout* main = new QVBoxLayout(this);
    main->setContentsMargins(0, 0, 0, 0);
    main->setSpacing(0);
    main->setAlignment(Qt::AlignCenter);  // centers *all* child widgets*/


    //make for loop for creating grid and printing "all" available apps to screen

    QGridLayout* appScreenGrid = new QGridLayout(this);

    for (int i = 0; i < this->mainShell->returnState()->returnAppVect().size(); i++)
    {
        QPushButton* curr = new QPushButton(this->mainShell->returnState()->returnAppVect()[i]->appName);
        buttonSetup(curr);
        appScreenGrid->addWidget(curr);
    }



    setLayout(appScreenGrid);

    qDebug() << "Margins:" << layout()->contentsMargins();


    setStyleSheet(
    "QWidget {"
    "background-image: url(/home/pablovepo/CLionProjects/btOS/resources/temp/curr_screen/screen_appViewer_temp2.png);"
    "position: center;"
    "padding: 0px 0px 0px 0px;"
    "background-position: left center;"
    "background-origin: content;"
    "}");

}
