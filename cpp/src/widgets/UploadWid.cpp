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

// std::map<QString, QString> present_simple = {
//     {"yo", "o"},
//     {"tu", "as"},
//     {"el", "a"},
//     {"nosotros", "amos"},
//     {"vosotros", "ais"},
//     {"ellos", "an"},
//     {"vos", "as"}
// };



// std::map<QString, std::vector<QString>> read_csv_verbs(const QString& filename, const QString& encoding = "utf-8") {
//     std::map<QString, std::vector<QString>> translation_dict;
//     QFile file(filename);
    
//     if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
//         QTextStream stream(&file);
//         while (!stream.atEnd()) {
//             QString line = stream.readLine();
//             QStringList tokens = line.split(',');
//             if (tokens.size() >= 4) {
//                 translation_dict[tokens[0]] = {tokens[1], tokens[2], tokens[3]};
//             }
//         }
//     }

//     return translation_dict;
// }

// QString random_translation(const std::map<QString, QString>& translation_dict) {
//     std::vector<QString> translations;
//     for (const auto& entry : translation_dict) {
//         translations.push_back(entry.first);
//     }
    
//     std::random_device rd;
//     std::mt19937 gen(rd());
//     std::shuffle(translations.begin(), translations.end(), gen);
    
//     int index = std::uniform_int_distribution<int>(0, translations.size() - 1)(gen);
//     return translations[index];
// }

// std::tuple<QString, QString, QString> parse_verb(const QString& verb) {
//     QString reflex = "";
//     QString ending = verb.mid(verb.size() - 2);
//     QString root = verb.left(verb.size() - 2);
    
//     if (ending == "se") {
//         reflex = ending;
//         ending = verb.mid(verb.size() - 4, 2);
//         root = verb.left(verb.size() - 4);
//     }
    
//     return std::make_tuple(root, ending, reflex);
// }

// QString conjunction(const QString& root, const QString& ending, const QString& kind, const QString& rule = "") {
//     if (rule.isEmpty()) {
//         QString new_ending; // = present_simple.value(kind);
//         return root + new_ending;
//     }
    
//     return "";
// }

// void verbs_flow() {
//     QString filename = "verbs.csv";  // Replace with the path to your CSV file
//     std::map<QString, std::vector<QString>> translation_dict = read_csv_verbs(filename.toUtf8().constData());
//     std::vector<QString> words_to_test;
    
//     for (const auto& entry : translation_dict) {
//         words_to_test.push_back(entry.first);
//     }
    
//     std::random_device rd;
//     std::mt19937 gen(rd());
//     std::shuffle(words_to_test.begin(), words_to_test.end(), gen);

//     int correct_answers = 0;
//     int wrong_answers = 0;

//     for (const auto& translation : words_to_test) {
//         std::cout << "Translate: " << translation.toUtf8().constData() << std::endl;
//         std::string user_input_in;
//         std::cout << "Enter the corresponding word (or 'q' to quit): ";
//         std::cin >> user_input_in;
//         QString user_input(user_input_in.c_str());

//         if (user_input == "q") {
//             break;
//         }
        
//         QString verb = QString::fromStdString(translation_dict[translation.toUtf8().constData()][0].toStdString());
//         QString root, ending, reflex;
//         std::tie(root, ending, reflex) = parse_verb(verb);
//         QString parsed = conjunction(root, ending, "yo");

//         if (user_input == parsed) {
//             std::cout << "Correct!" << std::endl;
//             correct_answers++;
//         } else {
//             std::cout << "Wrong! The correct word is: " << parsed.toUtf8().constData() << std::endl;
//             wrong_answers++;
//         }
//     }

//     std::cout << "Session score: " << correct_answers << " correct, " << wrong_answers << " wrong" << std::endl;
// }

// void words_flow() {
//     QString filename = "words.csv";  // Replace with the path to your CSV file
//     std::map<QString, QString> translation_dict = read_csv_words(filename.toUtf8().constData());

//     std::string num_words_in;
//     std::cout << "Enter the number of most recent words to be tested on (enter 'all' for all words): ";
//     std::cin >> num_words_in;
//     QString num_words(num_words_in.c_str());
    
//     std::vector<QString> words_to_test;
    
//     if (num_words == "all") {
//         for (const auto& entry : translation_dict) {
//             words_to_test.push_back(entry.first);
//         }
//     } else {
//         int num = num_words.toInt();
//         auto it = translation_dict.rbegin();
        
//         while (num > 0 && it != translation_dict.rend()) {
//             words_to_test.push_back(it->first);
//             ++it;
//             --num;
//         }
//     }
    
//     std::random_device rd;
//     std::mt19937 gen(rd());
//     std::shuffle(words_to_test.begin(), words_to_test.end(), gen);

//     int correct_answers = 0;
//     int wrong_answers = 0;

//     for (const auto& translation : words_to_test) {
//         std::cout << "Translate: " << translation.toUtf8().constData() << std::endl;
//         std::string user_input_in;
//         std::cout << "Enter the corresponding word (or 'q' to quit): ";
//         std::cin >> user_input_in;
//         QString user_input(user_input_in.c_str());

//         if (user_input == "q") {
//             break;
//         }
        
//         QString correct_word = translation_dict[translation];

//         if (user_input == correct_word) {
//             std::cout << "Correct!" << std::endl;
//             correct_answers++;
//         } else {
//             std::cout << "Wrong! The correct word is: " << correct_word.toUtf8().constData() << std::endl;
//             wrong_answers++;

//             for (int i = 0; i < 5; i++) {
//                 std::cout << "Try again: ";
//                 std::cin >> user_input_in;
//                 user_input = user_input_in.c_str();

//                 if (user_input == correct_word) {
//                     std::cout << "Correct!" << std::endl;
//                     correct_answers++;
//                     break;
//                 } else {
//                     std::cout << "Wrong!" << std::endl;
//                 }
//             }
//         }
//     }

//     int total_answers = correct_answers + wrong_answers;
//     double percentage_correct = (total_answers > 0) ? (static_cast<double>(correct_answers) / total_answers) * 100 : 0.0;

//     std::cout << "Session score: " << correct_answers << " correct, " << wrong_answers << " wrong (" << percentage_correct << "% correct)" << std::endl;
// }