#include "theme.h"
#include <QStyle>

void Theme::applyTheme(QApplication* app) {
    if (!app) return;
    app->setStyleSheet(getMasterStyleSheet());
}

QString Theme::getMasterStyleSheet() {
    return QString(R"(
        /* ===================================================
           Obsidian / Minimal iOS Global Base
           =================================================== */
        QWidget {
            background-color: %1;
            color: %7;
            font-family: -apple-system, BlinkMacSystemFont, 'Inter', 'SF Pro Display', 'Segoe UI', 'JetBrains Mono', 'DejaVu Sans Mono', sans-serif;
            font-size: 13px;
            border: none;
            outline: none;
        }

        QWidget#shell {
            background-color: %1;
        }

        /* ===================================================
           Minimal Modern Scrollbars (Invisible until needed)
           =================================================== */
        QScrollArea {
            background-color: transparent;
            border: none;
        }

        QScrollBar:vertical {
            border: none;
            background: transparent;
            width: 5px;
            margin: 4px 2px 4px 0px;
        }
        QScrollBar::handle:vertical {
            background: %5;
            min-height: 28px;
            border-radius: 2px;
        }
        QScrollBar::handle:vertical:hover {
            background: %6;
        }
        QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical {
            height: 0px;
        }
        QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical {
            background: transparent;
        }

        QScrollBar:horizontal {
            height: 0px;
        }

        /* ===================================================
           Obsidian App Cards & Buttons
           =================================================== */
        QPushButton {
            background-color: %2;
            color: %7;
            border: 1px solid %5;
            border-radius: %13px;
            padding: 15px 15px;
            font-size: 14px;
            font-weight: 600;
            text-align: center;
        }
        QPushButton:hover {
            background-color: %3;
            border-color: %6;
            color: #FFFFFF;
        }
        QPushButton:pressed {
            background-color: %4;
            border-color: %9;
        }
        QPushButton:focus {
            border-color: %9;
        }

        /* Primary Filled Action Button (Obsidian Iris Violet) */
        QPushButton[role="primary"] {
            background-color: %9;
            color: #FFFFFF;
            border: none;
            font-weight: 600;
        }
        QPushButton[role="primary"]:hover {
            background-color: %10;
        }
        QPushButton[role="primary"]:pressed {
            background-color: #6D28D9;
        }

        /* Minimal Pill Ghost Button (e.g. Back / Quit) */
        QPushButton[role="ghost"] {
            background-color: rgba(255, 255, 255, 0.05);
            color: %7;
            border: 1px solid %5;
            border-radius: %12px;
            padding: 6px 14px;
            font-size: 12px;
            font-weight: 500;
        }
        QPushButton[role="ghost"]:hover {
            background-color: rgba(255, 255, 255, 0.12);
            border-color: %6;
            color: #FFFFFF;
        }
        QPushButton[role="ghost"]:pressed {
            background-color: rgba(255, 255, 255, 0.03);
        }

        /* Danger Button */
        QPushButton[role="danger"] {
            background-color: transparent;
            color: %11;
            border: 1px solid %11;
            border-radius: %12px;
            padding: 6px 14px;
        }
        QPushButton[role="danger"]:hover {
            background-color: %11;
            color: #FFFFFF;
        }

        /* ===================================================
           Bento Card Panels
           =================================================== */
        QFrame[class="card"], QWidget[class="card"] {
            background-color: %2;
            border: 1px solid %5;
            border-radius: %13px;
            padding: 16px;
        }
        QFrame[class="card"]:hover, QWidget[class="card"]:hover {
            background-color: %3;
            border-color: %6;
        }

        /* ===================================================
           Typography
           =================================================== */
        QLabel {
            background-color: transparent;
            color: %7;
        }
        QLabel[role="title"] {
            font-size: 15px;
            font-weight: 700;
            color: #FFFFFF;
            letter-spacing: 0.3px;
        }
        QLabel[role="muted"] {
            font-size: 12px;
            font-weight: 500;
            color: %8;
            letter-spacing: 0.2px;
        }

        /* ===================================================
           Inputs & LineEdits
           =================================================== */
        QLineEdit, QTextEdit {
            background-color: %2;
            color: %7;
            border: 1px solid %5;
            border-radius: %12px;
            padding: 10px 14px;
            selection-background-color: %9;
            selection-color: #FFFFFF;
        }
        QLineEdit:focus, QTextEdit:focus {
            border: 1px solid %9;
        }

        /* ===================================================
           TopBar Minimal Hairline
           =================================================== */
        QFrame#topBarFrame {
            background-color: %1;
            border: none;
            border-bottom: 1px solid %5;
        }
    )")
    .arg(ColorBackground)      // %1
    .arg(ColorSurface)         // %2
    .arg(ColorSurfaceHover)    // %3
    .arg(ColorSurfacePressed)  // %4
    .arg(ColorBorder)          // %5
    .arg(ColorBorderActive)    // %6
    .arg(ColorTextPrimary)     // %7
    .arg(ColorTextMuted)       // %8
    .arg(ColorAccent)          // %9
    .arg(ColorAccentHover)     // %10
    .arg(ColorDanger)          // %11
    .arg(QString::number(RadiusSmall))   // %12
    .arg(QString::number(RadiusMedium)); // %13
}

void Theme::markAsCard(QWidget* widget) {
    if (!widget) return;
    widget->setProperty("class", "card");
    refreshWidget(widget);
}

void Theme::markAsPrimary(QPushButton* button) {
    if (!button) return;
    button->setProperty("role", "primary");
    refreshWidget(button);
}

void Theme::markAsGhost(QPushButton* button) {
    if (!button) return;
    button->setProperty("role", "ghost");
    refreshWidget(button);
}

void Theme::markAsDanger(QPushButton* button) {
    if (!button) return;
    button->setProperty("role", "danger");
    refreshWidget(button);
}

void Theme::markAsTitle(QLabel* label) {
    if (!label) return;
    label->setProperty("role", "title");
    refreshWidget(label);
}

void Theme::markAsMuted(QLabel* label) {
    if (!label) return;
    label->setProperty("role", "muted");
    refreshWidget(label);
}

void Theme::refreshWidget(QWidget* widget) {
    if (!widget) return;
    widget->style()->unpolish(widget);
    widget->style()->polish(widget);
    widget->update();
}
