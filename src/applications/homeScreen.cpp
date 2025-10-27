//
// Created by pablovepo on 10/26/25.
//

#include "homeScreen.h"

#include "notesScreen.h"
#include "src/core/btShell.h"
#include "src/core/screenManager.h"
void homeScreen::buttonStyle(QWidget* button){
    button->setStyleSheet("QPushButton{"
                         "color: #FFFFFF;"
                         "background-color: rgba(255, 255, 255, 50);"
                         "width: 100px;"
                         "height: 30px;"
                         "border-radius: 6px;"
                         ""
                         "}"
                         "QPushButton:hover{"
                         "background: solid rgba(187, 55, 123, 75);"
                         "border: .5px solid #D3DAD9;"
                         ""
                         ""
                         "}");
}


homeScreen::homeScreen(btShell* shell){
    mainShell = shell;

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
}

QWidget* homeScreen::returnHomeScreen(){
    return this;
}

