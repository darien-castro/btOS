//
// Created by pablovepo on 10/29/25.
//

#include "phoneScreen.h"

phoneScreen::phoneScreen(){
    this->setObjectName("phone");
    this->appName = "phone";
}



void phoneScreen::btAPP_SETUP(){
    std::vector<std::string> numList = {"1","2","3","4","5","6","7","8","9" ,"*","0","#"};
    int row = 0;
    int column = 0;
    int amt = 0;
    this->application = new QWidget;
    QVBoxLayout* mainLayout = new QVBoxLayout(this->application);

    QHBoxLayout* topPhoneScreen = new QHBoxLayout;

    QLabel* inputNum = new QLabel(phoneNumberInput);
    inputNum->setStyleSheet("QLabel{"
                            "color: #000000;"
                            "font-size: 28px;}");
    topPhoneScreen->addWidget(inputNum,0, Qt::AlignLeft);


    QPushButton* del = new QPushButton("`(╥_╥)");
    topPhoneScreen->addWidget(del,0,Qt::AlignRight);
    connect(del, &QPushButton::pressed, [this,inputNum]{
        if (phoneNumberInput.length() > 0)
        {
            this->phoneNumberInput.chop(1);
            if (phoneNumberInput.endsWith('-'))
            {
                phoneNumberInput.chop(1);
            }
            inputNum->setText(phoneNumberInput);
        }
    });


    QGridLayout* phoneButtons = new QGridLayout();

    for (int i = 0; i < numList.size(); i++)
    {
        QPushButton* curr = new QPushButton(numList[i].data());
        curr->setStyleSheet("QPushButton{"
                            "border-radius: 5px"
                            "background-color: #FF0000"
                            "}");
        connect(curr, &QPushButton::pressed, [this, numList, i, inputNum]{
            if (phoneNumberInput.length() == 12)
            {
                qDebug() << "not valid num length";
                return;
            }
            phoneNumberInput+= numList[i].data();
            if (phoneNumberInput.length() == 3 || phoneNumberInput.length() == 7)
            {
                phoneNumberInput += "-";
            }
            inputNum->setText(phoneNumberInput);
        });
        phoneButtons->addWidget(curr,row,column);
        if (column == 2)
        {
            row++;
            column = 0;
            continue;
        }
        column++;
    }


    QWidget* grid = new QWidget;
    QWidget* topScreen = new QWidget;
    grid->setLayout(phoneButtons);
    topScreen->setLayout(topPhoneScreen);
    mainLayout->addWidget(topScreen);
    mainLayout->addWidget(grid);



}

QWidget* phoneScreen::btAPP_RETURN(){
    return this->application;
}

void phoneScreen::btAPP_CLOSED(){
    QWidget* toDel = application;
    application = nullptr;
    delete toDel;
}

QString phoneScreen::returnAppName(){
    return appName;
}
