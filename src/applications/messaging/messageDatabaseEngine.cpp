#include "messageDatabaseEngine.h"

void MessageDatabaseEngine::initiateDatabase(){
  
  // decide whether I should make dir path function somewhere...

  QString app_dir = QCoreApplication::applicationDirPath();
  
  QString db_dir = app_dir + "../assets/databases/messages.db";

  qDebug() << "Database Testing. Directory Pointing to: " << db_dir;

  m_db = QSqlDatabase::addDatabase("QSQLITE");
  m_db.setDatabaseName(db_dir);
  if (m_db.open()){
    QSqlQuery query;
    query.exec("CREATE TABLE IF NOT EXISTS messages("
               "id INTEGER PRIMARY KEY AUTOINCREMENT,"
               "sender TEXT,"
               "body TEXT,"
               "timestamp DATETIME DEFAULT CURRENT_TIMESTAMP,"
               "isOutgoing INTEGER)"
        );
    if (!query.isActive()) {
        qDebug() << "Table creation failed:" << query.lastError().text();
        return;
    }
    // testing with mock data for now
    query.exec("insert into messages values(1, 'Danny', 'Hey, are we still on for lunch today?', '2026-09-16 10:15:00', 0)");
    query.exec("insert into messages values(2, 'Me', 'Absolutely. The usual spot?', '2026-09-16 10:17:30', 1)");
    query.exec("insert into messages values(3, 'Danny', 'Yeah, sounds good. See you at 12:30.', '2026-09-16 10:18:15', 0)");
    
    query.exec("insert into messages values(4, 'Christine', 'Could you send me the latest project files?', '2026-09-16 11:05:22', 0)");
    query.exec("insert into messages values(5, 'Me', 'Just emailed them to you.', '2026-09-16 11:10:05', 1)");
    query.exec("insert into messages values(6, 'Christine', 'Got them, thanks!', '2026-09-16 11:12:40', 0)");
    
    query.exec("insert into messages values(7, 'Lars', 'The server is going down for maintenance in 10 minutes.', '2026-09-16 14:50:00', 0)");
    query.exec("insert into messages values(8, 'Me', 'Copy that. I will save my work.', '2026-09-16 14:51:12', 1)");
    query.exec("insert into messages values(9, 'Roberto', 'Did Lars just say the server is going down?', '2026-09-16 14:52:05', 0)");
    query.exec("insert into messages values(10, 'Me', 'Yep, better save your stuff!', '2026-09-16 14:52:30', 1)");
    
    query.exec("insert into messages values(11, 'Maria', 'Happy birthday!! Hope you have a great day!', '2026-09-16 16:00:00', 0)");
    query.exec("insert into messages values(12, 'Me', 'Thank you so much Maria!', '2026-09-16 16:15:45', 1)");
    query.exec("insert into messages values(13, 'Danny', 'Oh snap, is it your birthday? Happy birthday man!', '2026-09-16 16:20:10', 0)");
    query.exec("insert into messages values(14, 'Me', 'Haha thanks Danny!', '2026-09-16 16:25:00', 1)");

  }
  else{
    qDebug() << "Database Failed: " << m_db.lastError().text();
  }
}

MessageDatabaseEngine::MessageDatabaseEngine(){
  initiateDatabase(); 
}


