//
// Created by pablovepo on 09/15/26.
//
#ifndef MESSAGE_H
#define MESSAGE_H
#include "src/core/btApplication.h"
#include "src/ui/theme.h"

//
//
//
// ---------------- a little on current architecture ---------------------------
//
// message application, will really only be the UI engine, it will signal for 
// database information, which will be passed to it by btShell, but will need to have some 
// message database engine
// 
//

class Message : public btApplication {
  Q_OBJECT


  public:

    Message(QWidget* parent);
    void screenAppSetup();


    // btApplication Functions
    void btAPP_SETUP() override;
    QWidget* btAPP_RETURN() override;
    void btAPP_CLOSED() override;
    QString returnAppName() override;


    // applications specific functions
    QErrorMessage sendMessage();


  signals:

  void applicationDatabaseRequested();
}


#endif // !MESSAGE_H


