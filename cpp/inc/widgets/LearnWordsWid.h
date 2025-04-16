#ifndef LEARN_WORDS_WID_H
#define LEARN_WORDS_WID_H

#include <QWidget>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>

#include "DatabaseService.h"
#include "widgets/GameSettingsWid.h"

class LearnWordsWid : public QWidget
{
    Q_OBJECT
    
public:
    LearnWordsWid(QWidget *parent = nullptr);
    LearnWordsWid(QWidget *parent, std::shared_ptr<DatabaseService> databaseService, QList<WordInfo> words);
    // LearnWordsWid::LearnWordsWid(QWidget *parent, bool erc);
    ~LearnWordsWid();
    void setDatabase(std::shared_ptr<DatabaseService> databaseService);

private:
    QWidget *parent;

    QFont wordsFont;
    GameSettingsWid *gameSettingsWid;

    QLabel *wordUpLabel = new QLabel;
    QLabel *wordDownLabel = new QLabel;
    QLineEdit *wordEnterEdit = new QLineEdit;
    QPushButton *stopLearn = new QPushButton(QString("Stop Learning Mode"));
    QVBoxLayout *learnWidLayoutV = new QVBoxLayout;

    GameSettings settings;
    QList<WordInfo> words;
    std::shared_ptr<DatabaseService> databaseService;

    QPalette p = QPalette();
    int whatTheWordIsNow = 0;
    int repeats = 0;
    int alphaChannel = 255;
    const int nonTransparent = 255;

    void updateLastDataBasePath(const QString &lastPath);
    inline void makeLabels();
    void keyPressEvent(QKeyEvent *event);
    void nextWord();

private slots:
    void startGameWid(GameSettings settings);
    void checkWord();
    void stopLearnSlot();

signals:
    void checkWordSig();
    void stopLearnSig();
};



#endif //LEARN_WORDS
