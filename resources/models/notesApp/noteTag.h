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
    int m_tag_id;

    QLabel* title;

public:
    noteTag(QWidget* parent = nullptr, QString tagName = "basic", int tag_id = -1);
    int returnTagId(){ return m_tag_id;};
    bool Active(){return _clicked;};
protected:
    void enterEvent(QEvent* event) override;
    void leaveEvent(QEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    signals:
    void clicked();
};



#endif //NOTETAG_H
