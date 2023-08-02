#include "widgets/GameSettingsWid.h"
// #include <QDataTime>

GameSettingsWid::GameSettingsWid(QWidget *parent)
{
    setModal(true);
    setupWordsSpinBox();
    setupTimerSpinBox();
    setView();
    connect(checkPlayWithTimer, SIGNAL(stateChanged(int)), this, SLOT(checkedPlayedWithTimer(int)));
    connect(this, SIGNAL(destroyed(QObject*)), this, SLOT(startGameWithSettings()));
    connect(startGame, SIGNAL(clicked()), this, SLOT(startGameWithSettings()));
    setFixedSize(200, 200);
}

void GameSettingsWid::setupWordsSpinBox()
{
    wordsAmount->setRange(1, 50);
    wordsAmount->setSingleStep(1);
    wordsAmount->setValue(1);
}

void GameSettingsWid::setupTimerSpinBox()
{
    secondsAmount->setRange(10, 60);
    secondsAmount->setSingleStep(1);
    secondsAmount->setValue(10);
}

void GameSettingsWid::setView()
{
    this->settingsWidLayoutV->addWidget(wordsLabel);
    this->settingsWidLayoutV->addWidget(wordsAmount);
    this->settingsWidLayoutV->addWidget(checkPlayWithTimer);
    this->settingsWidLayoutV->addWidget(timerLabel);
    this->settingsWidLayoutV->addWidget(secondsAmount);
    this->settingsWidLayoutV->addWidget(startGame);
    this->setLayout(settingsWidLayoutV);
}

GameSettingsWid::~GameSettingsWid()
{
    // delete nmFile;
    // delete stopGame;
    // delete gameWidLayoutV;
}

#define STARTGAME                                                                \
    if (this->checkPlayWithTimer->isChecked())                                   \
    {                                                                            \
        GameSettings gameSettings(wordsAmount->value(), secondsAmount->value()); \
        emit startGameWithSettingsSig(gameSettings);                             \
    }                                                                            \
    else                                                                         \
    {                                                                            \
        GameSettings gameSettings(wordsAmount->value());                         \
        emit startGameWithSettingsSig(gameSettings);                             \
    }

void GameSettingsWid::checkedPlayedWithTimer(int state)
{
    this->secondsAmount->setEnabled(!state);
    return;
}

void GameSettingsWid::startGameWithSettings()
{
    qDebug() << "start game";
    gameWasStarted = true;
    STARTGAME
}

void GameSettingsWid::closeEvent(QCloseEvent *event)
{
    if (!gameWasStarted)
    {
        STARTGAME
        qDebug() << "close window";
    }
}