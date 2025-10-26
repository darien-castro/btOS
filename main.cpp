#include <iostream>
#include "resources/QtCommon.h"
#include "src/core/btShell.h"
#include "src/core/btState.h"
#include "src/core/screenManager.h"

int main(int argc, char* argv[])
{

   QApplication app(argc,argv);

   btShell* thisShell = new btShell(800,500);

   QWidget* wait = thisShell->returnCurrentScreen();

   wait->show();

   return app.exec();
}
