//
// Created by darien-castro on 09/15/26.
//

#ifndef MESSAGEDATABASEENGINE_H
#define MESSAGEDATABASEENGINE_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

struct ChatMessage{

  int id = -1;
  QString sender;
  QString body;
  QString timeStamp;
  bool isOutgoing;

};


class MessageDatabaseEngine : public QObject{
  Q_OBJECT
  QSqlDatabase m_db;
public:
  explicit  MessageDatabaseEngine(QWidget* parent = nullptr);
  void initiateDatabase();
  void saveMessage(const ChatMessage& message);
  void exportMessages();
signals:
  

};

#endif // !MESSAGEDATABASEENGINE_H
