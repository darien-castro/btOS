//
// Created by pablovepo on 10/25/25.
//

#include "btTopBar.h"
#include "src/core/btShell.h"
#include "src/core/screenManager.h"

void btTopBar::styleWidget(QWidget* someWidget){
    someWidget->setStyleSheet("QWidget{"
                              "color: #ffffff;"
                              "font-size: 16px;"
                          "border: none;"
                          "background-color: rgba(0,0,0,0);"
                          "}");
}



btTopBar::btTopBar(btShell* btParent){
    shell = btParent;
    QFrame* top_bar_frame = new QFrame;
    top_bar_frame->setFrameShape(QFrame::Box);
    top_bar_frame->setFrameShadow(QFrame::Sunken);
    top_bar_frame->setLineWidth(2);
    QHBoxLayout* top_bar_hbox = new QHBoxLayout;

    //todo lank variables for testing
    QLabel* label_battery = new QLabel("67%");
    styleWidget(label_battery);
    QLabel* label_time = new QLabel(shell->returnStateTime());
    styleWidget(label_time);
    connect(shell->returnState(), &btState::timeUpdated, label_time, &QLabel::setText);


    //button logic for leaving current window
    QPushButton* close_window = new QPushButton("Quit");
    exitButton=close_window;
    exitButton->setStyleSheet("QPushButton{"
                               ""
                               "background-color: #FFFFFF;"
                               "background: #ffffff;"
                               "border:none;"
                               "color: #000000;"
                               "padding: 5px;"
                               "}");

    top_bar_hbox->addWidget(label_battery);
    top_bar_hbox->addStretch();
    //toDo, not dynamic at all, due to size of other widgets, has to be a good way to set actual center, maybe by
    //toDo, finding center of screen, and setting loc to there.
    top_bar_hbox->addSpacing(30);
    top_bar_hbox->addWidget(close_window);
    top_bar_hbox->addStretch();
    top_bar_hbox->addWidget(label_time);

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
        toDel->deleteLater();
    });

    top_bar_frame->setLayout(top_bar_hbox);
    top_bar_frame->setStyleSheet("QFrame{"
                                 "background: #000000; "
                                 "border: solid;"
                                 "border-width: 1upx;"
                                 "border-color: #989816;"
                                 "}");


    QHBoxLayout* pushLayout = new QHBoxLayout;

    pushLayout->addWidget(top_bar_frame);

    if (shell->onHome())
    {
        exitToggle(false);
    }


    this->setLayout(pushLayout);

    this->setStyleSheet("QWidget{"
                        "border-radius: 5px;"
                        "color: rgba(0,0,0,0);"
                        "border: solid 10px #989816;"
                        "background-color: rgba(0,0,0,0)};");
    setFixedHeight(45);
}

QWidget* btTopBar::returnTopBar(){
    return this;
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
