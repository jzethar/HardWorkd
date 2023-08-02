
#include "StartWin.h"

StartWin::StartWin(QWidget *parent) : QMainWindow(parent)
{
    setWindowTitle(QString("Hard Wor(k)d"));
    databaseService->createDatabase("main.wdb");
    startWid->setDatabase(databaseService);
    gameWid->setDatabase(databaseService);
    setCentralWidget(startWid);
    connect(startWid, SIGNAL(startGameSig()), this, SLOT(startGameWid()));
    // connect(gameWid, SIGNAL(stopGameSig(const ScoreInfo&)), this, SLOT(stopGameWid(const ScoreInfo&)));
    setFixedSize(600, 600);
}

void StartWin::startGameWid()
{
    gameWid = new GameWid(this);
    gameWid->setDatabase(databaseService);
    connect(gameWid, SIGNAL(stopGameSig(const ScoreInfo&)), this, SLOT(stopGameWid(const ScoreInfo&)));
    setCentralWidget(gameWid);
}

void StartWin::stopGameWid(const ScoreInfo& score)
{
    qDebug() << score.serializeScoreInfo();
    databaseService->saveScore(score);
    startWid = new StartWid(this);
    startWid->setDatabase(databaseService);
    connect(startWid, SIGNAL(startGameSig()), this, SLOT(startGameWid()));
    setCentralWidget(startWid);
}
