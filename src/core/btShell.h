#ifndef BTSHELL_H
#define BTSHELL_H

#include <assets/QtCommon.h>
#include <src/core/btState.h>
#include <src/core/btApplicationManager.h>

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
    btApplicationManager* appManager;
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
    QWidget* returnShellScreen();
    screenManager* returnScreenManager() const;
    QWidget* returnCurrentScreen();
    btState* returnState();
    bool onHome();
    void setupKeys();
    QJsonArray appArray;
    QJsonArray* returnAppArray();
    void initializeApplications();
    btApplicationManager* returnAppManager();
private slots:
    void updateUi();

};

#endif
