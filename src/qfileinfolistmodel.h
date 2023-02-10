#ifndef QFILEINFOLISTMODEL_H
#define QFILEINFOLISTMODEL_H

#include <QAbstractTableModel>
#include <QFileInfo>

/*!
 * \brief The QFileInfoListModel class is a model for a list of `QFileInfo` objects.
 * 
 * References:
 * - [Qt6 - Model Subclassing Reference](https://doc.qt.io/qt-6/model-view-programming.html#model-subclassing-reference)
 * 
 * The implementations of the Qt library classes
 * [QStringListModel](https://github.com/qt/qtbase/blob/6.4.2/src/corelib/itemmodels/qstringlistmodel.cpp) and
 * [QAbstractItemModel](https://github.com/qt/qtbase/blob/6.4.2/src/corelib/itemmodels/qabstractitemmodel.cpp)
 * were also referenced during the creation of this model.
 * 
 * **Warning:** This class overrides only a few functions, just enough to make it work for its current usages.
 * Before using it elsewhere, you may need to adapt it to your requirements.
 * 
 */
class QFileInfoListModel : public QAbstractTableModel
{
	Q_OBJECT

public:
	explicit QFileInfoListModel(QObject *parent = nullptr);
	~QFileInfoListModel();

	// Header:

	QVariant headerData(int section,
	                    Qt::Orientation orientation,
	                    int role = Qt::DisplayRole) const override;

	// Basic functionality:

	int rowCount(const QModelIndex &parent = QModelIndex()) const override;
	int columnCount(const QModelIndex &parent) const override;
	QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

	/*!
	 * \brief QFileInfoListModel::setQFileInfoList
	 * \param fileInfos
	 * 
	 * Sets the model's internal QFileInfo list to `fileInfos`.
	 * The model will notify any attached views that its underlying data has changed.
	 */
	void setQFileInfoList(const QList<QFileInfo> &fileInfos);

private:
	QList<QFileInfo> fileInfoList;
	QStringList header;
};

#endif // QFILEINFOLISTMODEL_H
