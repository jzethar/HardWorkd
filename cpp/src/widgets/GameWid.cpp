#include "widgets/GameWid.h"
// #include <QDataTime>

GameWid::GameWid(QWidget *parent)
{
    this->gameWidLayoutV->addWidget(nmFile);
    this->gameWidLayoutV->addWidget(stopGame);
    this->setLayout(gameWidLayoutV);
    connect(stopGame, SIGNAL(clicked()), this, SLOT(stopGameSlot()));
}

GameWid::~GameWid()
{
    delete nmFile;
    delete stopGame;
    delete gameWidLayoutV;
}

void GameWid::stopGameSlot() {
    // qDebug() << QDateTime::currentDateTime().toMSecsSinceEpoch();
    ScoreInfo scoreInfo = ScoreInfo(QDateTime::currentDateTime().toMSecsSinceEpoch(), score);
    emit stopGameSig(scoreInfo);
}