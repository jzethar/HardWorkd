#ifndef START_WID_H
#define START_WID_H

#include <QWidget>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>

#include "DatabaseService.h"

class StartWid : public QWidget
{
    Q_OBJECT
    
public:
    StartWid(QWidget *parent = nullptr);
    StartWid(QWidget *parent, std::shared_ptr<DatabaseService> databaseService);
    ~StartWid();
    void setDatabase(std::shared_ptr<DatabaseService> databaseService);

private:
    QWidget *parent;
    
    QLabel *labelScore = new QLabel(this);
    QLabel *labelTime = new QLabel(this);
    QPushButton *startGame = new QPushButton(QString("Start Game"));
    QPushButton *uploadCSVFile = new QPushButton(QString("Upload CSV"));
    QPushButton *learnWords = new QPushButton(QString("Learn Words"));
    QPushButton *chooseDbButton = new QPushButton(QString("Choose database"));
    QVBoxLayout *startWidLayoutV = new QVBoxLayout;

    QLineEdit *databaseFile = new QLineEdit;
    QHBoxLayout *databaseLayoutH = new QHBoxLayout;

    std::shared_ptr<DatabaseService> databaseService;

    void updateLastDataBasePath(const QString &lastPath);

private slots:
    void startGameSlot();
    void uploadFileSlot();
    void chooseDatabaseFile();
    void learnWordsSlot();

signals:
    void startGameSig();
    void uploadFileSig();
    void learnWordsSig();
};



#endif //START_WID_H
