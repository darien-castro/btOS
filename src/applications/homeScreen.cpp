//
// Created by pablovepo on 10/26/25.
//

#include "homeScreen.h"

#include "notesScreen.h"
#include "src/core/btShell.h"
#include "src/core/screenManager.h"
void homeScreen::buttonStyle(QWidget* button){
    button->setStyleSheet("QPushButton{"
                         "color: #000000;"
                         "background-color: rgba(135, 133, 128,15);"
                         "width: 100px;"
                         "height: 30px;"
                         "border-radius: 6px;"
                         ""
                         "}"
                         "QPushButton:hover{"
                         "background: rgba(207,212,198,100);"
                         "border: none;"
                         ""
                         ""
                         "}"
                         "QPushButton:hover:pressed {"
                        "background-color: rgba(207,212,198,40);"
                        "color: #FF0000;"
                        "}");
}


homeScreen::homeScreen(btShell* shell){
    mainShell = shell;

    setAccessibleName("homescreen");

    //toDo need button for applications, and way to print them on homescreen
    //toDo from some application list, for now, just buttons to set connections


    QPushButton* phone = new QPushButton("Phone");
    buttonStyle(phone);
    QPushButton* notes = new QPushButton("Notes");
    buttonStyle(notes);
    QPushButton* text = new QPushButton("Message");
    buttonStyle(text);
    QPushButton* manga = new QPushButton("Manga");
    buttonStyle(manga);

    QObject::connect(notes, &QPushButton::clicked, [this]{
        notesScreen* notes = new notesScreen;
        this->mainShell->returnScreenManager()->addWidget(notes->returnNotesWindow());
        this->mainShell->returnScreenManager()->returnStack()->setCurrentWidget(notes->returnNotesWindow());
    });


    QVBoxLayout* homeScreenLayout = new QVBoxLayout;
    homeScreenLayout->setObjectName("homeScreen");
    homeScreenLayout->setSpacing(1);
    homeScreenLayout->setContentsMargins(4,2,4,2);

    homeScreenLayout->addWidget(phone, 0, Qt::AlignCenter);
    homeScreenLayout->addWidget(notes, 0, Qt::AlignCenter);
    homeScreenLayout->addWidget(text, 0, Qt::AlignCenter);
    homeScreenLayout->addWidget(manga, 0, Qt::AlignCenter);

    setLayout(homeScreenLayout);
    setObjectName("homeScreen");
    setStyleSheet("QWidget#homeScreen{"
                  "background-color: rgba(237,232,208,50)"
                  "}");
}

QWidget* homeScreen::returnHomeScreen(){
    return this;
}

