#include "widgets/GameSettingsWid.h"
// #include <QDataTime>

GameSettingsWid::GameSettingsWid(QWidget *parent, bool lite) : lite(lite)
{
    setModal(true);
    setupWordsSpinBox();
    setupTimerSpinBox();
    setupChangeBox();
    setView();
    connect(checkPlayWithoutTimer, SIGNAL(stateChanged(int)), this, SLOT(checkedPlayWithoutTimer(int)));
    // connect(checkGetLastWords, SIGNAL(stateChanged(int)), this, SLOT(checkedPlayLastWords(int)));
    connect(this, SIGNAL(destroyed(QObject*)), this, SLOT(startGameWithSettings()));
    connect(startGame, SIGNAL(clicked()), this, SLOT(startGameWithSettings()));
    setFixedSize(300, 300);
}

inline void GameSettingsWid::setupWordsSpinBox()
{
    wordsAmount->setRange(1, 50);
    wordsAmount->setSingleStep(1);
    wordsAmount->setValue(1);
}

inline void GameSettingsWid::setupTimerSpinBox()
{
    if (!lite)
    {
        secondsAmount->setRange(10, 60);
        secondsAmount->setSingleStep(1);
        secondsAmount->setValue(10);
    }
}

inline void GameSettingsWid::setupChangeBox() 
{
    this->changeLayout->addWidget(fromLabel);
    this->changeLayout->addWidget(changeFromToButton);
    this->changeLayout->addWidget(toLabel);
    connect(changeFromToButton, SIGNAL(clicked()), this, SLOT(changeEvent()));
}

void GameSettingsWid::changeEvent()
{
    QString textFrom = this->fromLabel->text();
    this->fromLabel->setText(this->toLabel->text());
    this->toLabel->setText(textFrom);
    wordToTranslateSetting = !wordToTranslateSetting;
}

inline void GameSettingsWid::setView()
{
    this->settingsWidLayoutV->addWidget(wordsLabel);
    this->settingsWidLayoutV->addWidget(wordsAmount);
    if (!lite)
    {
        this->settingsWidLayoutV->addWidget(checkPlayWithoutTimer);
        this->settingsWidLayoutV->addWidget(timerLabel);
        this->settingsWidLayoutV->addWidget(secondsAmount);
        this->settingsWidLayoutV->addWidget(checkCorrectErrors);
        this->settingsWidLayoutV->addWidget(selectRandomCheck);
    }
    this->settingsWidLayoutV->addLayout(changeLayout);
    this->settingsWidLayoutV->addWidget(checkGetLastWords);
    this->settingsWidLayoutV->addWidget(selectWordsWithMostErrorsCheck);
    this->settingsWidLayoutV->addWidget(selectUnusedForLongTimeCheck);
    this->settingsWidLayoutV->addWidget(startGame);
    this->setLayout(settingsWidLayoutV);
}

GameSettingsWid::~GameSettingsWid()
{
    // delete nmFile;
    // delete stopGame;
    // delete gameWidLayoutV;
}

void GameSettingsWid::checkedPlayWithoutTimer(int state)
{
    this->secondsAmount->setEnabled(!state);
    return;
}

// void GameSettingsWid::checkedPlayLastWords(int state)
// {
//     return;
// }

void GameSettingsWid::startGameWithSettings()
{
    qDebug() << "start game";
    gameWasStarted = true;
    GameSettings gameSettings{(unsigned char)wordsAmount->value(),
                              this->checkPlayWithoutTimer->isChecked() ? (unsigned char)0x00 : (unsigned char)secondsAmount->value(),
                              !this->checkPlayWithoutTimer->isChecked(),
                              this->wordToTranslateSetting,
                              this->checkGetLastWords->isChecked(),
                              this->checkCorrectErrors->isChecked(),
                              this->selectWordsWithMostErrorsCheck->isChecked(),
                              this->selectUnusedForLongTimeCheck->isChecked(),
                              this->selectRandomCheck->isChecked()};
    emit startGameWithSettingsSig(gameSettings);
}

void GameSettingsWid::closeEvent(QCloseEvent *event)
{
    if (!gameWasStarted)
    {
        GameSettings gameSettings{(unsigned char)wordsAmount->value(),
                                  this->checkPlayWithoutTimer->isChecked() ? (unsigned char)0x00 : (unsigned char)secondsAmount->value(),
                                  !this->checkPlayWithoutTimer->isChecked(),
                                  this->wordToTranslateSetting,
                                  this->checkGetLastWords->isChecked(),
                                  this->checkCorrectErrors->isChecked(),
                                  this->selectWordsWithMostErrorsCheck->isChecked(),
                                  this->selectUnusedForLongTimeCheck->isChecked(),
                                  this->selectRandomCheck->isChecked()};
        emit startGameWithSettingsSig(gameSettings);
        qDebug() << "close window";
    }
}