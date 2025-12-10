//
// Created by pablovepo on 11/14/25.
//

#include "noteTag.h"

noteTag::noteTag(QWidget* parent, QString tagName, QString count, int tag_id) : QWidget(parent), _tag_name(tagName), _count(count), m_tag_id(tag_id){
    // naming object, and setting stylesheet, and other stuff
    setAttribute(Qt::WA_StyledBackground, true);
    setObjectName("noteTag");
    setFixedSize(100,45);
    setStyleSheet("QWidget#noteTag{"
                  "background: transparent;"
                  "border: 2px solid white;"
                  "border-radius: 22px;"
                  "}");
    QHBoxLayout* tag_layout = new QHBoxLayout(this);
    tag_layout->setContentsMargins(10,10,10,10);
    tag_layout->setSpacing(10);

    // tag label
    title = new QLabel(_tag_name, this);
    title->setWordWrap(true);
    title->setStyleSheet("QLabel{"
                         "background: transparent;"
                         "color: white;"
                         "font-weight: bold;"
                         "font-size: 16px;"
                         "}");
    tag_layout->addWidget(title);

    // num tags
    QLabel* num = new QLabel(_count, this);
    num->setObjectName("numLabel");
    num->setStyleSheet("QLabel#numLabel{"
                      "background: transparent;"
                      "border: solid 1px white;"
                      "border-radius: 7px;"
                      "}");
    tag_layout->addWidget(num,0,Qt::AlignRight);

    setLayout(tag_layout);
}

void noteTag::enterEvent(QEvent* event){
    if (_clicked == true)
    {
        return;
    }
    setStyleSheet("QWidget#noteTag{"
                  "background: transparent;"
                  "border: 1px solid rgba(255,255,255,100);"
                  "border-radius: 22px;"
                  "}");
}
void noteTag::leaveEvent(QEvent* event){
    if (_clicked == true)
    {
        return;
    }
    setStyleSheet("QWidget#noteTag{"
                  "background: transparent;"
                  "border: 2px solid rgba(255,255,255,255);"
                  "border-radius: 22px;"
                  "}");
}
void noteTag::mousePressEvent(QMouseEvent* event){
    if (_clicked == false)
    {
        _clicked = true;
        setStyleSheet("QWidget#noteTag{"
                      "background: transparent;"
                      "border: 3px solid rgba(255,255,197,255);"
                      "border-radius: 22px;"
                      "}");
        title->setStyleSheet("QLabel{"
                         "background: transparent;"
                         "color: #A7C7E7;"
                         "font-weight: bold;"
                         "font-size: 16px;"
                         "}");
        QPropertyAnimation* anim = new QPropertyAnimation(this, "geometry");
        anim->setDuration(30);
        orignal_pos = geometry();
        anim->setStartValue(orignal_pos);
        anim->setEndValue(orignal_pos.adjusted(2,2,-2,-2));
        anim->start(QPropertyAnimation::DeleteWhenStopped);
        QWidget::enterEvent(event);
        QWidget::leaveEvent(event);
        emit clicked();
    }
    else
    {
        QPropertyAnimation* anim = new QPropertyAnimation(this, "geometry");
        anim->setDuration(30);
        QRect current = geometry();
        anim->setStartValue(current);
        anim->setEndValue(orignal_pos);
        anim->start(QPropertyAnimation::DeleteWhenStopped);
        QWidget::enterEvent(event);
        QWidget::leaveEvent(event);
        emit clicked();
        _clicked = false;
        setStyleSheet("QWidget#noteTag{"
                  "background: transparent;"
                  "color: white;"
                  "border: 2px solid rgba(255,255,255,255);"
                  "border-radius: 22px;"
                  "}");
        title->setStyleSheet("QLabel{"
                         "background: transparent;"
                         "color: white;"
                         "font-weight: bold;"
                         "font-size: 16px;"
                         "}");
    }

}


