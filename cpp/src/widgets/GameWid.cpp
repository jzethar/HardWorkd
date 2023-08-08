#include "widgets/GameWid.h"
// #include <QDataTime>
#include <QKeyEvent>

// TODO write an event filter class for GameWid // https://doc.qt.io/qt-5/qobject.html#installEventFilter


GameWid::GameWid(QWidget *parent)
{
    makeLabels();
    gameSettingsWid = new GameSettingsWid(this);
    this->gameWidLayoutV->addWidget(secondsLabel);
    this->gameWidLayoutV->addWidget(wordLabel);
    this->gameWidLayoutV->addWidget(wordEnterEdit);
    this->gameWidLayoutV->addWidget(stopGame);
    this->setLayout(gameWidLayoutV);
    connect(stopGame, SIGNAL(clicked()), this, SLOT(stopGameSlot()));
    connect(gameSettingsWid, SIGNAL(startGameWithSettingsSig(GameSettings)), this, SLOT(startGameWid(GameSettings)));
    connect(timerForWord, SIGNAL(timeout()), this, SLOT(updateTime()));
    gameSettingsWid->show();
    connect(this, SIGNAL(checkWordSig()), this, SLOT(checkWord()));
}

inline void GameWid::makeLabels()
{
    wordsFont.setPointSize(45);
    wordLabel->setFont(wordsFont);
    secondsLabel->setFont(wordsFont);
    wordLabel->setAlignment(Qt::AlignHCenter);
    secondsLabel->setAlignment(Qt::AlignCenter);
}

GameWid::~GameWid()
{
    delete wordEnterEdit;
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
                this->secondsLabel->setText(QString::number(this->timeForWord));
                // TODO update it with normal view
                this->wordLabel->setText([&](const WordInfo &wordInfo)
                                         { return this->settings.wordToTranslation ? wordInfo.word : wordInfo.translation; }
                                         (this->words.at(whatTheWordIsNow)));
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
    this->secondsLabel->setText(QString::number(this->timeForWord));
    if (this->timeForWord == 0)
    {
        return nextWord();
    }
    this->timerForWord->start(1000);
}

void GameWid::nextWord()
{
    this->timeForWord = this->settings.timer;
    if (whatTheWordIsNow + 1 == this->words.size())
    {
        return stopGameSlot();
    }
    whatTheWordIsNow += 1;
    this->words[whatTheWordIsNow].correctness = false;
    this->wordLabel->setText([&](const WordInfo &wordInfo)
                             { return this->settings.wordToTranslation ? wordInfo.word : wordInfo.translation; }(this->words.at(whatTheWordIsNow)));
    this->secondsLabel->setText(QString::number(this->timeForWord));
    this->timerForWord->start(1000);
    this->wordEnterEdit->clear();
}

void GameWid::checkWord()
{
    QString word = this->wordEnterEdit->text();
    qDebug() << word.toLower();
    qDebug() << [&](const WordInfo &wordInfo)
        { return this->settings.wordToTranslation ? wordInfo.translation : wordInfo.word; }(this->words.at(whatTheWordIsNow)).toLower();
    if (word.toLower() == [&](const WordInfo &wordInfo)
        { return this->settings.wordToTranslation ? wordInfo.translation : wordInfo.word; }(this->words.at(whatTheWordIsNow)).toLower())
    {
        this->words[whatTheWordIsNow].correctness = true;
        this->score += 1;
    }
    else
    {
        this->words[whatTheWordIsNow].correctness = false;
    }
    return nextWord();
}


// It works!!!! We dont need (k) task!!!

void GameWid::keyPressEvent(QKeyEvent *event)
{
    auto *keyEvent = static_cast<QKeyEvent *>(event);
    switch (keyEvent->key())
    {
    case Qt::Key_Return:
        emit checkWordSig();
        return;
    default:
        break;
    }
    return;
}

bool GameWid::eventKeyPress(QEvent *event)
{
    auto *keyEvent = static_cast<QKeyEvent *>(event);
    switch (keyEvent->key())
    {
    case Qt::Key_Return:
        emit checkWordSig();
        return true;    
    default:
        break;
    }
    return true;
}


bool GameWid::eventFilter(QObject *target, QEvent *event)
{
    if(target == wordEnterEdit)
    {
        switch( event->type() )
        {
        case QEvent::KeyPress:
            return eventKeyPress(event);
        default:
            break;
        };
    }

    return true;
}