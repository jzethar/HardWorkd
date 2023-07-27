#include "widgets/StartWid.h"

StartWid::StartWid(QWidget *parent)
{
    this->startWidLayoutV->addWidget(labelTime);
    this->startWidLayoutV->addWidget(labelScore);
    this->startWidLayoutV->addWidget(startGame);
    this->setLayout(startWidLayoutV);
    connect(startGame, SIGNAL(clicked()), this, SLOT(startGameSlot()));
}

StartWid::~StartWid()
{
    delete startGame;
    delete startWidLayoutV;
    delete labelScore;
    delete labelTime;
}

void StartWid::startGameSlot() {
    emit startGameSig();
}

void StartWid::setDatabase(const DatabaseService &databaseService)
{
    this->databaseService = databaseService;
    if (this->databaseService.isOpen())
    {
        ScoreInfo score;
        if (databaseService.getLastScore(score))
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