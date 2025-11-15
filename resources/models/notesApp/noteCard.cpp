//
// Created by pablovepo on 11/14/25.
//

#include "noteCard.h"

NoteCardModern::NoteCardModern(const QString& title, const QString& desc, const QString& imagePath , QWidget* parent): QWidget(parent){
    setAttribute(Qt::WA_StyledBackground, true);
    setFixedSize(180, 200);

    // Shadow
    QGraphicsDropShadowEffect* shadow = new QGraphicsDropShadowEffect;
    shadow->setBlurRadius(15);
    shadow->setColor(QColor(0, 0, 0, 30));
    shadow->setOffset(0, 2);
    setGraphicsEffect(shadow);

    // Layout
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setContentsMargins(16, 16, 16, 16);
    layout->setSpacing(8);

    // Image (optional)
    if (!imagePath.isEmpty()) {
        imageLabel = new QLabel;
        QPixmap pix(imagePath);
        imageLabel->setPixmap(pix.scaled(148, 100, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation));
        imageLabel->setFixedSize(148, 100);
        imageLabel->setStyleSheet("border-radius: 8px;");
        layout->addWidget(imageLabel);
    }
    // Title
    titleLabel = new QLabel(title);
    titleLabel->setStyleSheet(
        "font-size: 16px;"
        "font-weight: bold;"
        "color: #000000;"
    );
    titleLabel->setWordWrap(true);

    // Description
    descLabel = new QLabel(desc);
    descLabel->setStyleSheet(
        "font-size: 12px;"
        "color: #666666;"
    );
    descLabel->setWordWrap(true);

    layout->addWidget(titleLabel);
    layout->addWidget(descLabel);
    layout->addStretch();

    // Styling
    setStyleSheet(
        "QWidget {"
        "   background-color: #FFFFFF;"
        "   border-radius: 16px;"
        "}"
    );
};
void NoteCardModern::enterEvent(QEvent* event){
    // Lift effect on hover
    QPropertyAnimation* anim = new QPropertyAnimation(this, "geometry");
    anim->setDuration(100);
    current = geometry();
    anim->setStartValue(current);
    anim->setEndValue(current.adjusted(2, 2, -2, -2));
    anim->start(QPropertyAnimation::DeleteWhenStopped);

    QWidget::enterEvent(event);
}
void NoteCardModern::leaveEvent(QEvent* event){
    QPropertyAnimation* anim = new QPropertyAnimation(this, "geometry");
    anim->setDuration(100);
    QRect current_ = geometry();
    anim->setStartValue(current_);
    anim->setEndValue(current);
    anim->start(QPropertyAnimation::DeleteWhenStopped);
    QWidget::enterEvent(event);
    QWidget::leaveEvent(event);
}
void NoteCardModern::mousePressEvent(QMouseEvent* event){

    emit clicked();
}

