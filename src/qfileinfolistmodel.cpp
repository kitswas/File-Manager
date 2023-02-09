#include "qfileinfolistmodel.h"

QFileInfoListModel::QFileInfoListModel(QObject *parent)
	: QAbstractTableModel(parent)
{
	header << "Name"
		   << "Type"
		   << "Path";
}

QFileInfoListModel::~QFileInfoListModel() {}

QVariant QFileInfoListModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (orientation == Qt::Horizontal && role == Qt::DisplayRole && section >= 0
	    && section < header.size()) {
		qDebug() << "header data " << header.at(section) << " fetched for section " << section;
		return header.at(section);
	}
	return QVariant();
}

int QFileInfoListModel::columnCount(const QModelIndex &parent) const
{
	Q_UNUSED(parent);
	return header.size();
}

int QFileInfoListModel::rowCount(const QModelIndex &parent) const
{
	// For list models only the root node (an invalid parent) should return the list's size. For all
	// other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
	if (parent.isValid())
		return 0;

	return fileInfoList.size();
}

QVariant QFileInfoListModel::data(const QModelIndex &index, int role) const
{
	QStringList _data;
	_data << fileInfoList.at(index.row()).fileName()
		  << (fileInfoList.at(index.row()).isFile() ? "File" : "Folder")
		  << fileInfoList.at(index.row()).absoluteFilePath();

	if (!index.isValid())
		return QVariant();

	if (index.row() < 0 || index.row() >= fileInfoList.size())
		return QVariant();

	if (role == Qt::DisplayRole || role == Qt::EditRole)
		return _data.at(index.column());

	return QVariant();
}

void QFileInfoListModel::setQFileInfoList(const QList<QFileInfo> &fileInfos)
{
	beginResetModel();
	fileInfoList = fileInfos;
	endResetModel();
}
