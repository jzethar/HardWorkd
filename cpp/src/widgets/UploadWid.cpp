#include <iostream>
#include <utility>
#include "QHeaderView"
#include <QMessageBox>
#include "widgets/UploadWid.h"


UploadWid::UploadWid(QWidget *parent)
{
    this->nmNchsLayoutH->addWidget(nmFile);
    this->nmNchsLayoutH->addWidget(chsFile);
    // this->nmNchsLayoutH->addWidget(saveFile);
    // this->nmNchsLayoutH->addWidget(chooseDb);
    this->nmNchsLayoutH->addWidget(saveWordsInDb);
    this->table = new TableModel(this);
    this->CSVTable->setModel(table);
    this->CSVTable->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    LearnLayoutV->addLayout(nmNchsLayoutH);
    LearnLayoutV->addWidget(CSVTable);
    this->setLayout(LearnLayoutV);
    connect(chsFile, SIGNAL(clicked()), this, SLOT(chooseCSVFile()));
    connect(saveWordsInDb, SIGNAL(clicked()), this, SLOT(saveInDatabase())); 
    setFixedSize(600, 600);
}

// TODO add check for opened / existed database
void UploadWid::setDatabase(std::shared_ptr<DatabaseService> databaseService)
{
    this->databaseService = databaseService;
    if (this->databaseService->isOpen())
    {
        return;
    }
}

void UploadWid::saveInDatabase() 
{
    QList<WordInfo> words = table->getList();
    if (!databaseService->saveNewWords(words))
    {
        QMessageBox::critical(this, "Attention", "Can't save in database");
        return;
    }
    emit uploadDoneSig();
}

// void UploadWid::saveNewFile()
// {
//     QString fileName = QFileDialog::getSaveFileName(this, tr("Choose a place"), "");
//     nmFile->setText(fileName);
//     writeCSVFile(fileName);
//     // resWin();
// }

void UploadWid::chooseCSVFile()
{
    if (table->rowCount(QModelIndex()) > 0)
    {
        QModelIndex index = QModelIndex();
        table->removeRows(0, table->rowCount(QModelIndex()), index);
    }
    fileInfoVec.clear();
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Save dictionary"), "",
                                                    tr("Csv files (*.csv)"));
    nmFile->setText(fileName);
    readCSVWords(fileName);
}

void UploadWid::writeCSVFile(QString fileName)
{
    std::map<QString, QString> translation_dict;
    QString encoding = "utf-16";
    QFile file(fileName);

    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream stream(&file);
        QList<WordInfo> words = table->getList();
        for (const auto &w : words)
        {
            if (w.state)
                stream << w.word << "," << w.translation << "\n";
        }
    }
}

void UploadWid::readCSVWords(QString fileName) {
    std::map<QString, QString> translation_dict;
    QString encoding = "utf-16";
    QFile file(fileName);
    
    // TODO update function for different types of deliminator and opportunity to read words with ""
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream stream(&file);
        while (!stream.atEnd()) {
            QString line = stream.readLine();
            QStringList tokens = line.split(',');
            if (tokens.size() >= 2) {
                fileInfoVec.push_back(WordInfo(tokens[0], tokens[1]));
            }
        }
    }

    int row = 0;
    QModelIndex index = QModelIndex();
    for (const auto &i : fileInfoVec)
    {
        if (row == 0)
        {
            table->insertRows(row, 1, QModelIndex());
        }
        else
        {
            table->insertRows(row, 1, index);
        }
        index = table->index(row, 0, index);
        if (!table->setData(index, i.state, Qt::EditRole))
        {
            QMessageBox::critical(this, "Attention", "Can't set data");
            return;
        }
        index = table->index(row, 1, index);
        if (!table->setData(index, i.word, Qt::EditRole))
        {
            QMessageBox::critical(this, "Attention", "Can't set data");
            return;
        }
        index = table->index(row, 2, index);
        if (!table->setData(index, i.translation, Qt::EditRole))
        {
            QMessageBox::critical(this, "Attention", "Can't set data");
            return;
        }

        row++;
    }

    return;
}
