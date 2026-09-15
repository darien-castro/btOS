//
// Created by pablovepo on 10/26/25.
//

#include "homeScreen.h"
#include "src/core/btShell.h"
#include "src/core/screenManager.h"
#include "src/ui/theme.h"

void homeScreen::screenAppsSetup(QVBoxLayout* scrollArea) {
    for (const QJsonValue &value : currentApplications) {
        QJsonObject obj = value.toObject();
        QString name = obj["base_object_name"].toString();
        bool onHome = obj["on_home_screen"].toBool();

        if (onHome) {
            // Human-friendly display label with subtle icon accent
            QString displayName = name;
            if (name == "settingsScreen" || name == "settings") {
                displayName = "⚙   Settings";
            }

            QPushButton* curr = new QPushButton(displayName);
            curr->setFocusPolicy(Qt::StrongFocus);
            curr->setCursor(Qt::PointingHandCursor);
            curr->setFixedWidth(340);
            curr->setFixedHeight(58);

            // Apply Obsidian squircle card styling
            Theme::markAsCard(curr);

            onScreenButtons.push_back(curr);
            scrollArea->addWidget(curr, 0, Qt::AlignHCenter);

            QObject::connect(curr, &QPushButton::clicked, [this, name]() {
                emit applicationLaunchRequest(name);  
            });
        }
    }
}

homeScreen::homeScreen(QJsonArray ApplicationArray) : currentApplications(ApplicationArray) {
    setAccessibleName("homescreen");

    QWidget* content = new QWidget(this);
    QVBoxLayout* homeScreenLayout = new QVBoxLayout(content);
    homeScreenLayout->setSpacing(12);
    homeScreenLayout->setContentsMargins(32, 28, 32, 28);
    homeScreenLayout->setAlignment(Qt::AlignTop | Qt::AlignHCenter);

    // Subtle category header (Obsidian minimal metadata style)
    QLabel* categoryLabel = new QLabel("APPS", content);
    Theme::markAsMuted(categoryLabel);
    categoryLabel->setStyleSheet("font-size: 11px; font-weight: 700; letter-spacing: 2px; color: #7E8294; margin-bottom: 6px;");
    categoryLabel->setFixedWidth(340);
    homeScreenLayout->addWidget(categoryLabel, 0, Qt::AlignHCenter);

    // Populate apps
    screenAppsSetup(homeScreenLayout);

    QScrollArea* scrollareaMain = new QScrollArea(this);
    scrollareaMain->setWidgetResizable(true);
    scrollareaMain->setFrameShape(QFrame::NoFrame);
    scrollareaMain->setWidget(content);

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->addWidget(scrollareaMain);
    setLayout(mainLayout);
}

QWidget* homeScreen::returnHomeScreen() {
    return this;
}
