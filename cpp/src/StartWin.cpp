
#include "StartWin.h"

# define init_connect     connect(startWid, SIGNAL(startGameSig()), this, SLOT(startGameWid())); \
    connect(startWid, SIGNAL(uploadFileSig()), this, SLOT(uploadFileWid())); \
    connect(startWid, SIGNAL(learnWordsSig()), this, SLOT(learnWordsWid())); \

StartWin::StartWin(QWidget *parent) : QMainWindow(parent)
{
    setWindowTitle(QString("Hard Wor(k)d"));
    readLastDataBaseFile();
    startWid->setDatabase(databaseService);
    setCentralWidget(startWid);
    init_connect
    setFixedSize(600, 600);
}

void StartWin::startGameWid()
{
    gameWid = new GameWid(this);
    gameWid->setDatabase(databaseService);
    connect(gameWid, SIGNAL(stopGameSig(const ScoreInfo&)), this, SLOT(initialScreen(const ScoreInfo&)));
    connect(gameWid, SIGNAL(stopGameERCSig(const ScoreInfo&, const QList<WordInfo> &)), this, SLOT(ERCLearnWordsWid(const ScoreInfo&, const QList<WordInfo> &)));
    setCentralWidget(gameWid);
}

void StartWin::learnWordsWid()
{
    learnWid = new LearnWordsWid();
    learnWid->setDatabase(databaseService);
    connect(learnWid, SIGNAL(stopLearnSig()), this, SLOT(initialScreen()));
    setCentralWidget(learnWid);
}

void StartWin::ERCLearnWordsWid(const ScoreInfo& score, const QList<WordInfo> &words)
{
    learnWid = new LearnWordsWid(nullptr, nullptr, words);
    connect(learnWid, SIGNAL(stopLearnSig()), this, SLOT(initialScreen()));
    setCentralWidget(learnWid);
}

void StartWin::readLastDataBaseFile()
{
    QFile file(filePath);
    QStringList strings;
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&file);
        QString lastDatabasePath = in.readLine();
        databaseService->createDatabase(lastDatabasePath);
    } else {
        if(!file.open(QIODevice::NewOnly))
        {
            qDebug() << "Error can't create file";
        }
    }
}

// May be I need to make a def param ?

void StartWin::initialScreen(const ScoreInfo& score)
{
    databaseService->saveScore(score);
    startWid = new StartWid(this);
    startWid->setDatabase(databaseService);
    init_connect
    setCentralWidget(startWid);
}

void StartWin::initialScreen()
{
    startWid = new StartWid(this);
    startWid->setDatabase(databaseService);
    init_connect
    setCentralWidget(startWid);
}

void StartWin::initialScreen(const ScoreInfo& score,  const QList<WordInfo> &words)
{
    databaseService->saveScore(score);
    startWid = new StartWid(this);
    startWid->setDatabase(databaseService);
    init_connect
    setCentralWidget(startWid);
}

void StartWin::uploadFileWid()
{
    uploadWid = new UploadWid(this);
    uploadWid->setDatabase(databaseService);
    connect(uploadWid, SIGNAL(uploadDoneSig()), this, SLOT(initialScreen()));
    setCentralWidget(uploadWid);
}
