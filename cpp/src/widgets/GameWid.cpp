#include "widgets/GameWid.h"
// #include <QDataTime>

GameWid::GameWid(QWidget *parent)
{
    gameSettingsWid = new GameSettingsWid(this);
    this->gameWidLayoutV->addWidget(timerLabel);
    this->gameWidLayoutV->addWidget(nmFile);
    this->gameWidLayoutV->addWidget(stopGame);
    this->setLayout(gameWidLayoutV);
    connect(stopGame, SIGNAL(clicked()), this, SLOT(stopGameSlot()));
    connect(gameSettingsWid, SIGNAL(startGameWithSettingsSig(GameSettings)), this, SLOT(startGameWid(GameSettings)));
    connect(timerForWord, SIGNAL(timeout()), this, SLOT(updateTime()));
    gameSettingsWid->show();
}

GameWid::~GameWid()
{
    delete nmFile;
    delete stopGame;
    delete gameWidLayoutV;
}

void GameWid::startGameWid(GameSettings settings)
{
    gameSettingsWid->close();
    this->settings = settings;
    if(this->databaseService != nullptr) {
        if(this->databaseService->getWords(this->words, this->settings.words)) {
            if(this->words.size() > 0) {
                this->timeForWord = settings.timer;
                this->timerLabel->setText(wordTIME + QString::number(this->timeForWord));
                this->timerForWord->start(1000);
            } 
        }
    }
}

void GameWid::stopGameSlot()
{
    ScoreInfo scoreInfo = ScoreInfo(QDateTime::currentDateTime().toMSecsSinceEpoch(), score);
    emit stopGameSig(scoreInfo);
}


void GameWid::setDatabase(std::shared_ptr<DatabaseService> databaseService)
{
    this->databaseService = databaseService;
    if (this->databaseService->isOpen())
    {
        return;
    }
}

void GameWid::updateTime()
{
    this->timeForWord -= 1;
    this->timerLabel->setText(wordTIME + QString::number(this->timeForWord));
    this->timerForWord->start(1000);
}