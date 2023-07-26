//
// Created by julian on 5/17/21.
//

#include <QtGui/QResizeEvent>
#include "TableModel.h"

TableModel::TableModel(QObject *parent): QAbstractTableModel(parent) {

}

int TableModel::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return listOfWords.size();
}

int TableModel::columnCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return 3;
}

QVariant TableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= listOfWords.size() || index.row() < 0)
        return QVariant();

    WordInfo word = listOfWords.at(index.row());

    switch (role)
    {
    case Qt::DisplayRole:
    case Qt::EditRole:
        if (index.column() == 1)
            return word.word;
        else if (index.column() == 2)
            return word.translation;
        break;
    case Qt::CheckStateRole:
        if (index.column() == 0)
            return word.state ? Qt::Checked : Qt::Unchecked;
        break;
    default:
        break;
    }
    return QVariant();
}

QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal) {
        switch (section) {
            case 0:
                return tr("Chose");
            case 1:
                return tr("Word");
            case 2:
                return tr("Translation");

            default:
                return QVariant();
        }
    }
    return QVariant();
}

bool TableModel::setData(const QModelIndex &index, const QVariant &value, int role) {
    if (index.isValid() && role == Qt::EditRole) {
        int row = index.row();

        WordInfo w = listOfWords.value(row);

        switch (index.column())
        {
        case 0:
                break;
        case 1:
                w.word = value.toString();
                break;
        case 2:
                w.translation = value.toString();
                break;
        default:
                return false;
        }

        listOfWords.replace(row, w);
        emit(dataChanged(index, index));

        return true;
    }

    if (index.isValid() && role == Qt::CheckStateRole)
    {
        int row = index.row();
        WordInfo w = listOfWords.value(row);
        if (value == Qt::Checked)
        {
            w.state = true;
        }
        else
        {
            w.state = false;
        }
        listOfWords.replace(row, w);
        return true;
    }

    return false;
}

bool TableModel::insertRows(int position, int rows, const QModelIndex &index) {
    Q_UNUSED(index);
    beginInsertRows(QModelIndex(), position, position+rows-1);

    for (int row=0; row < rows; row++) {
        WordInfo pair("", "");
        listOfWords.insert(position, pair);
    }

    endInsertRows();
    return true;
}

bool TableModel::removeRows(int position, int rows, const QModelIndex &index) {
    Q_UNUSED(index);
    beginRemoveRows(QModelIndex(), position, position+rows-1);

    for (int row=0; row < rows; ++row) {
        listOfWords.removeAt(position);
    }

    endRemoveRows();
    return true;
}

//QModelIndex TableModel::index( int row, int column, const QModelIndex &parent ) const
//{
//
////    if ( !parent.isValid() )
////        parentItem = rootItem;
////    else
////        parentItem = static_cast<ModelItem*>( parent.internalPointer() );
//
//    if(listOfPairs.size() == 0)
//    {
//
//    }
//    FileInfo childItem = listOfPairs.value(row);
//    return createIndex( row, column, &childItem );
//}

Qt::ItemFlags TableModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;

    return QAbstractTableModel::flags(index) | Qt::ItemFlag::ItemIsUserCheckable | Qt::ItemFlag::ItemIsEnabled | Qt::ItemFlag::ItemIsEditable;
}

QList<WordInfo> TableModel::getList() {
    return listOfWords;
}


//QModelIndex TableModel::parent( const QModelIndex &index ) const
//{
//    if ( !index.isValid() )
//        return QModelIndex();
//
//    auto *childItem = static_cast<FileInfo*>( index.internalPointer() );
//    FileInfo *parentItem = childItem->parent();
//
//    if ( parentItem == rootItem )
//        return QModelIndex();
//
//    return createIndex( parentItem->row(), 0, parentItem );
//}
//
//QList<FileInfo> TableModel::getList() {
//    return listOfPairs;
//}
