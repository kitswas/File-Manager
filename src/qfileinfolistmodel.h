#ifndef QFILEINFOLISTMODEL_H
#define QFILEINFOLISTMODEL_H

#include <QAbstractTableModel>
#include <QFileInfo>

class QFileInfoListModel : public QAbstractTableModel
{
	Q_OBJECT

public:
	explicit QFileInfoListModel(QObject *parent = nullptr);
	~QFileInfoListModel();

	// Header:
	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

	// Basic functionality:
	int rowCount(const QModelIndex &parent = QModelIndex()) const override;
	int columnCount(const QModelIndex &parent) const override;

	QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
	void setQFileInfoList(const QList<QFileInfo> &fileInfos);

private:
	QList<QFileInfo> fileInfoList;
	QStringList header;
};

#endif // QFILEINFOLISTMODEL_H
