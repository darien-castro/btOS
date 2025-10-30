//
// Created by pablovepo on 10/29/25.
//

#include "appViewer.h"

#include "src/core/screenManager.h"

appViewer::appViewer(btShell* mS){

    setObjectName("appViewer");
    QString saveLoc = "/home/pablovepo/CLionProjects/btOS/resources/temp/curr_screen";
    QString saveFile = saveLoc + "/screen_appViewer_temp.png";
    this->mainShell = mS;
    QWidget* prevScreen = mS->returnScreenManager()->returnStack()->currentWidget();
    QPixmap pix = prevScreen->grab();

    qDebug() << "Pixmap size:" << pix.size();
    qDebug() << "Save success:" << pix.save(saveFile, "PNG");

    QVBoxLayout* appViewer_topBox = new QVBoxLayout;

    QLabel* text = new QLabel("hello World");

    appViewer_topBox->addWidget(text, 0, Qt::AlignCenter);

    this->setLayout(appViewer_topBox);

    this->setStyleSheet("QWidget{"
                        "background-image: url(/home/pablovepo/CLionProjects/btOS/resources/temp/curr_screen/screen_appViewer_temp.png)"
                        ""
                        "}");

    QGraphicsBlurEffect* blurEffect = new QGraphicsBlurEffect(this);
    blurEffect->setBlurRadius(10);
    setGraphicsEffect(blurEffect);

}
