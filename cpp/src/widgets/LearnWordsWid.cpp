#include "widgets/LearnWordsWid.h"
#include <QKeyEvent>

// TODO write an event filter class for GameWid // https://doc.qt.io/qt-5/qobject.html#installEventFilter

LearnWordsWid::LearnWordsWid(QWidget *parent)
{
    makeLabels();
    gameSettingsWid = new GameSettingsWid(this, true);
    wordUpLabel->setWordWrap(true);
    wordDownLabel->setWordWrap(true);
    this->learnWidLayoutV->addWidget(wordUpLabel);
    this->learnWidLayoutV->addWidget(wordDownLabel);
    this->learnWidLayoutV->addWidget(wordEnterEdit);
    this->learnWidLayoutV->addWidget(stopLearn);
    this->setLayout(learnWidLayoutV);
    connect(stopLearn, SIGNAL(clicked()), this, SLOT(stopLearnSlot()));
    connect(gameSettingsWid, SIGNAL(startGameWithSettingsSig(GameSettings)), this, SLOT(startGameWid(GameSettings)));
    gameSettingsWid->show();
    connect(this, SIGNAL(checkWordSig()), this, SLOT(checkWord()));
}

LearnWordsWid::LearnWordsWid(QWidget *parent, std::shared_ptr<DatabaseService> databaseService, QList<WordInfo> words)
{
    if (!databaseService)
    {
        makeLabels();
        gameSettingsWid = new GameSettingsWid(this, true);
        wordUpLabel->setWordWrap(true);
        wordDownLabel->setWordWrap(true);
        this->learnWidLayoutV->addWidget(wordUpLabel);
        this->learnWidLayoutV->addWidget(wordDownLabel);
        this->learnWidLayoutV->addWidget(wordEnterEdit);
        this->learnWidLayoutV->addWidget(stopLearn);
        this->setLayout(learnWidLayoutV);
        connect(stopLearn, SIGNAL(clicked()), this, SLOT(stopLearnSlot()));
        connect(gameSettingsWid, SIGNAL(startGameWithSettingsSig(GameSettings)), this, SLOT(startGameWid(GameSettings)));
        // gameSettingsWid->show();
        connect(this, SIGNAL(checkWordSig()), this, SLOT(checkWord()));
        this->words = words;
        emit startGameWid(GameSettings());
    }
}

void LearnWordsWid::setDatabase(std::shared_ptr<DatabaseService> databaseService)
{
    this->databaseService = databaseService;
    if (this->databaseService->isOpen())
    {
        return;
    }
}

void LearnWordsWid::stopLearnSlot()
{
    emit stopLearnSig();
}

void LearnWordsWid::startGameWid(GameSettings settings)
{
    gameSettingsWid->close();
    this->settings = settings;
    if (this->databaseService == nullptr)
    {
        if (this->words.size() == 0)
            return;
        this->wordUpLabel->setText([&](const WordInfo &wordInfo)
                                   { return this->settings.wordToTranslation ? wordInfo.word : wordInfo.translation; }(this->words.at(whatTheWordIsNow)));
        this->wordDownLabel->setText([&](const WordInfo &wordInfo)
                                     { return this->settings.wordToTranslation ? wordInfo.translation : wordInfo.word; }(this->words.at(whatTheWordIsNow)));
    }

    if (this->databaseService->getWords(this->words, this->settings))
    {
        if (this->words.size() == 0)
            return;
        this->wordUpLabel->setText([&](const WordInfo &wordInfo)
                                   { return this->settings.wordToTranslation ? wordInfo.word : wordInfo.translation; }(this->words.at(whatTheWordIsNow)));
        this->wordDownLabel->setText([&](const WordInfo &wordInfo)
                                     { return this->settings.wordToTranslation ? wordInfo.translation : wordInfo.word; }(this->words.at(whatTheWordIsNow)));
    }
}

inline void LearnWordsWid::makeLabels()
{
    wordsFont.setPointSize(45);
    wordUpLabel->setFont(wordsFont);
    wordUpLabel->setAlignment(Qt::AlignHCenter);
    QColor c = QColor(0, 0, 0, 255);    // make it a class member
    p.setColor(QPalette::Active, QPalette::WindowText, c);
    wordUpLabel->setPalette(p);
    wordDownLabel->setFont(wordsFont);
    wordDownLabel->setAlignment(Qt::AlignHCenter);
}

void LearnWordsWid::nextWord()
{
    if (whatTheWordIsNow + 1 == this->words.size())
    {
        return stopLearnSlot();  
    }
    whatTheWordIsNow += 1;
    this->wordUpLabel->setText([&](const WordInfo &wordInfo)
                             { return this->settings.wordToTranslation ? wordInfo.word : wordInfo.translation; }
                             (this->words.at(whatTheWordIsNow)));
    this->wordDownLabel->setText([&](const WordInfo &wordInfo)
                             { return this->settings.wordToTranslation ? wordInfo.translation : wordInfo.word; }
                             (this->words.at(whatTheWordIsNow)));
    this->wordEnterEdit->clear();
}

void LearnWordsWid::checkWord()
{
    QString word = this->wordEnterEdit->text();
    qDebug() << word.toLower();
    qDebug() << [&](const WordInfo &wordInfo)
        { return this->settings.wordToTranslation ? wordInfo.translation : wordInfo.word; }(this->words.at(whatTheWordIsNow)).toLower();
    if (word.toLower() == [&](const WordInfo &wordInfo)
        { return this->settings.wordToTranslation ? wordInfo.translation : wordInfo.word; }(this->words.at(whatTheWordIsNow)).toLower())
    {
        if (repeats != 5)
        {
            alphaChannel -= (nonTransparent / 5);
            QColor c = QColor(0, 0, 0, alphaChannel);
            this->p.setColor(QPalette::Active, QPalette::WindowText, c);
            wordUpLabel->setPalette(p);
            repeats += 1;
            this->wordEnterEdit->clear();
            return;
        } else {
            repeats = 0;
            alphaChannel = nonTransparent;
            QColor c = QColor(0, 0, 0, alphaChannel);
            this->p.setColor(QPalette::Active, QPalette::WindowText, c);
            wordUpLabel->setPalette(p);
            return nextWord();
        }
    }
    else
    {
        alphaChannel = nonTransparent;
        QColor c = QColor(0, 0, 0, alphaChannel);
        this->p.setColor(QPalette::Active, QPalette::WindowText, c);
        wordUpLabel->setPalette(p);
        repeats = 0;
    }
    return;
}

LearnWordsWid::~LearnWordsWid()
{

}

void LearnWordsWid::keyPressEvent(QKeyEvent *event)
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