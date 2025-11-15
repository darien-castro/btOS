//
// Created by pablovepo on 11/14/25.
//

#ifndef NOTECARD_H
#define NOTECARD_H
#include <resources/QtCommon.h>



class NoteCardModern : public QWidget {
    Q_OBJECT
    QLabel* titleLabel;
    QLabel* descLabel;
    QLabel* imageLabel;
    QRect current;


public:
    NoteCardModern(const QString& title, const QString& desc,
                   const QString& imagePath = "", QWidget* parent = nullptr);


protected:
    void enterEvent(QEvent* event) override;

    void leaveEvent(QEvent* event) override;

    void mousePressEvent(QMouseEvent* event) override;

signals:
    void clicked();
};




#endif //NOTECARD_H
