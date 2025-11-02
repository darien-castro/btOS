#include <iostream>
#include "resources/QtCommon.h"
#include "src/core/btShell.h"
#include "src/core/btState.h"
#include "src/core/screenManager.h"

int main(int argc, char* argv[])
{

   QApplication app(argc,argv);

   int id = QFontDatabase::addApplicationFont("/home/pablovepo/CLionProjects/btOS/resources/fonts/Hack/HackNerdFont-Regular.ttf");

   QString family = QFontDatabase::applicationFontFamilies(id).at(0);

   QFont font (family);


   QApplication::setFont(font);

   btShell* thisShell = new btShell(800,500);


   QWidget* wait = thisShell->returnCurrentScreen();

   wait->show();

   return app.exec();
}
