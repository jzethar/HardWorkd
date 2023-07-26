#include "widgets/StartWid.h"

StartWid::StartWid(QWidget *parent)
{
    this->startWidLayoutV->addWidget(startGame);
    this->setLayout(startWidLayoutV);
    connect(startGame, SIGNAL(clicked()), this, SLOT(startGameSlot()));
}

StartWid::~StartWid()
{
    delete startGame;
    delete startWidLayoutV;
}

void StartWid::startGameSlot() {
    emit startGameSig();
}

void StartWid::setDatabase(const DatabaseService& databaseService) {
    this->databaseService = databaseService;
}