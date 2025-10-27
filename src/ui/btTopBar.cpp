//
// Created by pablovepo on 10/25/25.
//

#include "btTopBar.h"
#include "src/core/btShell.h"
#include "src/core/screenManager.h"


btTopBar::btTopBar(btShell* btParent){
    shell = btParent;
    QFrame* top_bar_frame = new QFrame;
    top_bar_frame->setFrameShape(QFrame::Box);
    top_bar_frame->setFrameShadow(QFrame::Sunken);
    top_bar_frame->setLineWidth(2);
    QHBoxLayout* top_bar_hbox = new QHBoxLayout;

    //todo lank variables for testing
    QLabel* label_battery = new QLabel("0");
    QLabel* label_time = new QLabel("0");
    QLabel* label_connection = new QLabel("0");

    //button logic for leaving current window
    QPushButton* close_window = new QPushButton("Quit");

    top_bar_hbox->addWidget(label_battery);
    top_bar_hbox->addWidget(label_time);
    top_bar_hbox->addWidget(label_connection);
    top_bar_hbox->addWidget(close_window);

    QObject::connect(close_window, &QPushButton::clicked, [this](){
        if (shell->onHome())
        {
            //hacky version, can improve
            qDebug() << "cannot remove homeScreen";
            return;
        }
        shell->returnScreenManager()->removeWidget(shell->returnScreenManager()->returnCurrent());
    });

    top_bar_frame->setLayout(top_bar_hbox);


    QHBoxLayout* pushLayout = new QHBoxLayout;

    pushLayout->addWidget(top_bar_frame);

    topBar = new QWidget();
    topBar->setLayout(pushLayout);


}

QWidget* btTopBar::returnTopBar(){
    return topBar;
}
