#ifndef BTSHELL_H
#define BTSHELL_H

#include <resources/QtCommon.h>
#include <src/core/btState.h>

// forward declarations to avoid include loops
class btTopBar;
class screenManager;
class homeScreen;

enum class CURRAPP {HOMESCREEN, APPLICATION};

class btShell : public QObject {
    Q_OBJECT
    btState* mainState;
    btTopBar* topBar;
    screenManager* mainScreenManager;
    QWidget* shellScreen;
    //depends on settings
    int height;
    int width;
    CURRAPP current = CURRAPP::HOMESCREEN;

public:
    btShell(int h = 450, int w = 250);
    QString returnStateTime();
    QString returnStateBat();
    QString returnStateConnec();
    void setupShellScreen();
    screenManager* returnScreenManager() const;
    QWidget* returnCurrentScreen();
    bool onHome();
    void setupKeys();
private slots:
    void updateUi();
};

#endif
