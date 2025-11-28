#include <iostream>
#include "resources/QtCommon.h"
#include "src/core/btShell.h"
#include "src/core/btState.h"
#include "src/core/screenManager.h"

// toDo, main toDo next, is to get save logic into db, and tags save, as well as sorting logic.

int main(int argc, char* argv[])
{
   //toDo, really need to theme this, and make a real design, so that it comes together nicely!
   QApplication app(argc,argv);
   int id = QFontDatabase::addApplicationFont("../resources/fonts/Trykker/Trykker-Regular.ttf");
   QString family = QFontDatabase::applicationFontFamilies(id).at(0);
   QFont font (family);
   QApplication::setFont(font);
   QFile styleFile("../resources/themes/personal/testing.qss");
   if (styleFile.open(QIODevice::ReadOnly | QIODevice::Text))
   {
      QString styleSheet = QLatin1String(styleFile.readAll());
      app.setStyleSheet(styleSheet);
      qDebug() << "styleSheet done";
      styleFile.close();
   }
   else
   {
      qDebug() << "not found";
   }
   btShell* thisShell = new btShell(800,500);
   QWidget* wait = thisShell->returnCurrentScreen();
   wait->show();
   return app.exec();
}
