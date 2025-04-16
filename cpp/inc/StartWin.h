#ifndef START_WIN_H
#define START_WIN_H

#include <QSqlDatabase>
#include <QMainWindow>
#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>

#include "widgets/GameWid.h"
#include "widgets/StartWid.h"
#include "widgets/UploadWid.h"
#include "widgets/LearnWordsWid.h"
#include "DatabaseService.h"

class StartWin : public QMainWindow
{
    Q_OBJECT

public:
    explicit StartWin(QWidget *parent = Q_NULLPTR);
    virtual ~StartWin() {}

private:
    const QString filePath = "/var/lib/hardwork/last_database.txt";

    StartWid *startWid = new StartWid(this);
    GameWid *gameWid;
    UploadWid *uploadWid;
    LearnWordsWid *learnWid;

    std::shared_ptr<DatabaseService> databaseService = std::make_shared<DatabaseService>();

    // void initFirstScreen();
    void readLastDataBaseFile();

private slots:
    void startGameWid();
    void ERCLearnWordsWid(const ScoreInfo& score, const QList<WordInfo> &words);
    void initialScreen(const ScoreInfo& score,  const QList<WordInfo> &words);
    void initialScreen(const ScoreInfo& score);
    void initialScreen();
    void uploadFileWid();
    void learnWordsWid();
};

#endif // START_WIN_H