//
// Created by pablovepo on 11/14/25.
//

#ifndef NOTETAG_H
#define NOTETAG_H
#include <resources/QtCommon.h>


class noteTag : public QWidget {
    Q_OBJECT;
    QString _tag_name;
    QString _count;
    QRect orignal_pos;
    bool _clicked = false;
public:
    noteTag(QWidget* parent = nullptr, QString tagName = "basic", QString count = "#0");
protected:
    void enterEvent(QEvent* event) override;
    void leaveEvent(QEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    signals:
    void clicked();
};



#endif //NOTETAG_H
