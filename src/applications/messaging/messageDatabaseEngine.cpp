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


    // create contacts table
    if (!query.exec("CREATE TABLE IF NOT EXISTS contact("
              "first_name TEXT NOT NULL,"
              "mobile_contact TEXT NOT NULL,"
              "last_name TEXT,"
              "contact_id INTEGER PRIMARY KEY AUTOINCREMENT)"
        )){
        qDebug() << "Database Creation Failed: " << m_db.lastError().text();
    }


    // create messages table
    if(!query.exec("CREATE TABLE IF NOT EXISTS messages("
               "id INTEGER PRIMARY KEY AUTOINCREMENT,"
               "sender TEXT,"
               "body TEXT,"
               "timestamp DATETIME DEFAULT CURRENT_TIMESTAMP,"
               "isOutgoing INTEGER,"
               "mobile_contact INTEGER,"
               "CONSTRAINT fk_mobilecontact "
               "FOREIGN KEY (mobile_contact) "
               "REFERENCES contact(contact_id))"
        )){
        qDebug() << "Database Creation Failed: " << m_db.lastError().text();
    }
    if (!query.isActive()) {
        qDebug() << "Table creation failed:" << query.lastError().text();
        return;
    }
 }
  else{
    qDebug() << "Database Failed: " << m_db.lastError().text();
  }
  m_db.close();
}

MessageDatabaseEngine::MessageDatabaseEngine(){
  initiateDatabase(); 
}


