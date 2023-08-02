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
#include "DatabaseService.h"

class StartWin : public QMainWindow
{
    Q_OBJECT

public:
    explicit StartWin(QWidget *parent = Q_NULLPTR);
    virtual ~StartWin() {}

private:
    StartWid *startWid = new StartWid(this);
    GameWid *gameWid;
    UploadWid *uploadWid;
    

    // TODO make database as shared_ptr
    std::shared_ptr<DatabaseService> databaseService = std::make_shared<DatabaseService>();

    void initFirstScreen();

private slots:
    void startGameWid();
    void initialScreen(const ScoreInfo& score);
    void initialScreen();
    void uploadFileWid();
};

#endif // START_WIN_H