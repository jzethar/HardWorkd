
#include "StartWin.h"

StartWin::StartWin(QWidget *parent) : QMainWindow(parent)
{
    setWindowTitle(QString("Hard Wor(k)d"));
    // databaseService->createDatabase("main.wdb");
    startWid->setDatabase(databaseService);
    gameWid->setDatabase(databaseService);
    setCentralWidget(startWid);
    connect(startWid, SIGNAL(startGameSig()), this, SLOT(startGameWid()));
    connect(startWid, SIGNAL(uploadFileSig()), this, SLOT(uploadFileWid()));
    // connect(gameWid, SIGNAL(stopGameSig(const ScoreInfo&)), this, SLOT(stopGameWid(const ScoreInfo&)));
    setFixedSize(600, 600);
}

void StartWin::startGameWid()
{
    gameWid = new GameWid(this);
    gameWid->setDatabase(databaseService);
    connect(gameWid, SIGNAL(stopGameSig(const ScoreInfo&)), this, SLOT(initialScreen(const ScoreInfo&)));
    setCentralWidget(gameWid);
}

void StartWin::initialScreen(const ScoreInfo& score)
{
    // qDebug() << score.serializeScoreInfo();
    databaseService->saveScore(score);
    startWid = new StartWid(this);
    startWid->setDatabase(databaseService);
    connect(startWid, SIGNAL(startGameSig()), this, SLOT(startGameWid()));
    connect(startWid, SIGNAL(uploadFileSig()), this, SLOT(uploadFileWid()));
    setCentralWidget(startWid);
}

void StartWin::initialScreen()
{
    startWid = new StartWid(this);
    startWid->setDatabase(databaseService);
    connect(startWid, SIGNAL(startGameSig()), this, SLOT(startGameWid()));
    connect(startWid, SIGNAL(uploadFileSig()), this, SLOT(uploadFileWid()));
    setCentralWidget(startWid);
}

void StartWin::uploadFileWid()
{
    uploadWid = new UploadWid(this);
    uploadWid->setDatabase(databaseService);
    connect(uploadWid, SIGNAL(uploadDoneSig()), this, SLOT(initialScreen()));
    setCentralWidget(uploadWid);
}
