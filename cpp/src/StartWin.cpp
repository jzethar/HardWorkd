
#include "StartWin.h"

StartWin::StartWin(QWidget *parent) : QMainWindow(parent)
{
    setWindowTitle(QString("Hard Wor(k)d"));
    databaseService.createDatabase("main.wdb");
    startWid->setDatabase(databaseService);
    setCentralWidget(startWid);
    connect(startWid, SIGNAL(startGameSig()), this, SLOT(startGameWid()));
    connect(gameWid, SIGNAL(stopGameSig(const ScoreInfo&)), this, SLOT(stopGameWid(const ScoreInfo&)));
    setFixedSize(600, 600);
}

void StartWin::startGameWid()
{
    gameWid = new GameWid(this);
    connect(gameWid, SIGNAL(stopGameSig(const ScoreInfo&)), this, SLOT(stopGameWid(const ScoreInfo&)));
    setCentralWidget(gameWid);
}

void StartWin::stopGameWid(const ScoreInfo& score)
{
    qDebug() << score.serializeScoreInfo();
    startWid = new StartWid(this);
    connect(startWid, SIGNAL(startGameSig()), this, SLOT(startGameWid()));
    setCentralWidget(startWid);
}
