#include <iostream>
#include "assets/QtCommon.h"
#include "src/core/btShell.h"
#include "src/core/btState.h"
#include "src/core/screenManager.h"
#include "src/ui/theme.h"

// toDo, main toDo next, is to get save logic into db, and tags save, as well as sorting logic.

int main(int argc, char* argv[])
{
   //toDo, really need to theme this, and make a real design, so that it comes together nicely!
  QApplication app(argc,argv);
  Theme::applyTheme(&app);
  btShell* thisShell = new btShell(1080,1920);
  QWidget* wait = thisShell->returnCurrentScreen();
  wait->show();
  return app.exec();
}
