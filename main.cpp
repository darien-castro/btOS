#include "src/core/btShell.h"
#include "src/core/screenManager.h"
#include "src/ui/theme.h"

int main(int argc, char* argv[])
{
  QApplication app(argc,argv);
  Theme::applyTheme(&app);
  btShell* thisShell = new btShell(800, 500);
  QWidget* wait = thisShell->returnCurrentScreen();
  wait->show();
  return app.exec();
}
