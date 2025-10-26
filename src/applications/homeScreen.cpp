//
// Created by pablovepo on 10/26/25.
//

#include "homeScreen.h"

#include "notesScreen.h"
#include "src/core/btShell.h"
#include "src/core/screenManager.h"


homeScreen::homeScreen(btShell* shell){
    mainShell = shell;
    btHomeScreen = new QWidget;

    //toDo need button for applications, and way to print them on homescreen
    //toDo from some application list, for now, just buttons to set connections


    QPushButton* phone = new QPushButton("Phone");
    QPushButton* notes = new QPushButton("Notes");
    QPushButton* text = new QPushButton("Message");
    QPushButton* manga = new QPushButton("Manga");

    QObject::connect(notes, &QPushButton::clicked, [this]{
        notesScreen* notes = new notesScreen;
        this->mainShell->returnScreenManager()->addWidget(notes->returnNotesWindow());
        this->mainShell->returnScreenManager()->returnStack()->setCurrentWidget(notes->returnNotesWindow());
    });


    QVBoxLayout* homeScreenLayout = new QVBoxLayout;
    homeScreenLayout->setSpacing(1);
    homeScreenLayout->setContentsMargins(4,2,4,2);

    homeScreenLayout->addWidget(phone, 0, Qt::AlignCenter);
    homeScreenLayout->addWidget(notes, 0, Qt::AlignCenter);
    homeScreenLayout->addWidget(text, 0, Qt::AlignCenter);
    homeScreenLayout->addWidget(manga, 0, Qt::AlignCenter);

    btHomeScreen->setLayout(homeScreenLayout);
}

QWidget* homeScreen::returnHomeScreen(){
    return btHomeScreen;
}

