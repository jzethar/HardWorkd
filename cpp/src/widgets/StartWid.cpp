#include "widgets/StartWid.h"
#include <QMessageBox>
#include<QFileDialog>

// TODO read about inline functions or how to beautify it

StartWid::StartWid(QWidget *parent)
{
    this->startWidLayoutV->addWidget(labelTime);
    this->startWidLayoutV->addWidget(labelScore);
    this->databaseLayoutH->addWidget(databaseFile);
    this->databaseLayoutH->addWidget(chooseDbButton);
    this->startWidLayoutV->addLayout(databaseLayoutH);
    this->startWidLayoutV->addWidget(startGame);
    this->startWidLayoutV->addWidget(uploadCSVFile);
    this->setLayout(startWidLayoutV);
    connect(startGame, SIGNAL(clicked()), this, SLOT(startGameSlot()));
    connect(uploadCSVFile, SIGNAL(clicked()), this, SLOT(uploadFileSlot()));
    connect(chooseDbButton, SIGNAL(clicked()), this, SLOT(chooseDatabaseFile()));
}

StartWid::~StartWid()
{
    delete startGame;
    delete startWidLayoutV;
    delete labelScore;
    delete labelTime;
}

void StartWid::chooseDatabaseFile()
{
    QString fileName = QFileDialog::getSaveFileName(this, 
                                                    tr("Choose a place"), "", 
                                                    tr("WDB files (*.wdb)"));
    databaseFile->setText(fileName);
    if (!databaseService->createDatabase(fileName))
    {
        QMessageBox::critical(this, "Attention", "Can't create database");
        return;
    }
    setDatabase(databaseService);
}

void StartWid::startGameSlot() {
    emit startGameSig();
}

void StartWid::uploadFileSlot() {
    emit uploadFileSig();
}

void StartWid::setDatabase(std::shared_ptr<DatabaseService> databaseService)
{
    this->databaseService = databaseService;
    if (this->databaseService->isOpen())
    {
        ScoreInfo score;
        if (this->databaseService->getLastScore(score))
        {
            QFont fontScore = labelScore->font();
            QFont fontTime = labelTime->font();
            fontScore.setPointSize(36);
            fontTime.setPointSize(36);
            labelScore->setFont(fontScore);
            labelScore->setFrameStyle(QFrame::Panel | QFrame::Sunken);
            labelScore->setText(score.serializeScore());
            labelScore->setTextFormat(Qt::RichText);
            labelScore->setAlignment(Qt::AlignHCenter);
            labelScore->setWordWrap(true);
            labelTime->setFont(fontTime);
            labelTime->setFrameStyle(QFrame::Panel | QFrame::Sunken);
            labelTime->setText(score.serializeTime());
            labelTime->setTextFormat(Qt::RichText);
            labelTime->setAlignment(Qt::AlignHCenter);
            labelTime->setWordWrap(true);
        }
    }
}