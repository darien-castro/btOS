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
    QLabel* label_battery = new QLabel("67%");
    QLabel* label_time = new QLabel(shell->returnStateTime());
    connect(shell->returnState(), &btState::timeUpdated, label_time, &QLabel::setText);

    QLabel* label_connection = new QLabel("╭∩╮(•̀_·́)╭∩╮");

    //button logic for leaving current window
    QPushButton* close_window = new QPushButton("Quit");
    exitButton=close_window;
    close_window->setStyleSheet("QPushButton{"
                               "border: none rgba(0,0,0,0);"
                               "background-color: #FFFFFF;"
                               "}");
    close_window->setStyleSheet("QPushButton:hover{"
                                "background-color: solid rgba(20, 30, 0, 32);"
                                "border: none;"
                                "}");

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
        QWidget* toDel = shell->returnScreenManager()->returnCurrent();
        shell->returnScreenManager()->removeWidget(shell->returnScreenManager()->returnCurrent());
        qDebug() << "toDelete: "<<  toDel;
        delete toDel;
    });

    top_bar_frame->setLayout(top_bar_hbox);
    top_bar_frame->setStyleSheet("QFrame{"
                                 "border: none;"
                                 "}");


    QHBoxLayout* pushLayout = new QHBoxLayout;

    pushLayout->addWidget(top_bar_frame);

    if (shell->onHome())
    {
        exitToggle(false);
    }


    this->setLayout(pushLayout);

    this->setStyleSheet(""
                        "border-radius: 5px;"
                        "color: #000000;"
                        "border: 2px solid rgba(56, 7, 42, 36);"
                        "background-color: #FFFFFF");


}

QWidget* btTopBar::returnTopBar(){
    return topBar;
}


void btTopBar::exitToggle(bool x){
    if (x == false)
    {
        this->exitButton->hide();
    }
    if (x == true)
    {
        this->exitButton->show();
    }

}
