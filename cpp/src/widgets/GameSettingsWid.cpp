#include "widgets/GameSettingsWid.h"
// #include <QDataTime>

GameSettingsWid::GameSettingsWid(QWidget *parent)
{
    setModal(true);
    setupWordsSpinBox();
    setupTimerSpinBox();
    setView();
    connect(startGame, SIGNAL(clicked()), this, SLOT(stopGameSlot()));
    connect(this, SIGNAL(close()), this, SLOT(startGameWithSettings()));
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

void GameSettingsWid::startGameWithSettings()
{
    GameSettings gameSettings(wordsAmount->value(), secondsAmount->value());
    emit startGameWithSettingsSig(gameSettings);
}