//
// Created by pablovepo on 10/25/25.
//

#include "btTopBar.h"
#include "src/ui/theme.h"

btTopBar::btTopBar(QWidget* parent) : QWidget(parent) {
    QFrame* top_bar_frame = new QFrame(this);
    top_bar_frame->setObjectName("topBarFrame");

    QHBoxLayout* top_bar_hbox = new QHBoxLayout(top_bar_frame);
    top_bar_hbox->setContentsMargins(18, 0, 18, 0);

    // Battery Indicator (Left)
    QLabel* label_battery = new QLabel("77% ⚡", top_bar_frame);
    Theme::markAsMuted(label_battery);

    // Clock (Right)
    labelTime = new QLabel(time, top_bar_frame);
    Theme::markAsTitle(labelTime);

    // Navigation / Exit Button (Center-Left)
    QPushButton* close_window = new QPushButton("← Back", top_bar_frame);
    Theme::markAsGhost(close_window);
    exitButton = close_window;
    exitButton->hide(); // Hidden by default on home screen

    top_bar_hbox->addWidget(label_battery);
    top_bar_hbox->addSpacing(16);
    top_bar_hbox->addWidget(close_window);
    top_bar_hbox->addStretch();
    top_bar_hbox->addWidget(labelTime);

    QObject::connect(close_window, &QPushButton::clicked, [this]() {
        emit quitApplicationRequested();
    });

    QHBoxLayout* mainLayout = new QHBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->addWidget(top_bar_frame);
    setLayout(mainLayout);

    setFixedHeight(48);
}

QWidget* btTopBar::returnTopBar() {
    return this;
}

void btTopBar::exitToggle(bool visible) {
    if (!exitButton) return;
    if (visible) {
        exitButton->show();
    } else {
        exitButton->hide();
    }
}

void btTopBar::setTime(const QString& newTime) {
    time = newTime;
    if (labelTime) {
        labelTime->setText(newTime);
    }
}
