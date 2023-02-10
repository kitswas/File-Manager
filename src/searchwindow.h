#ifndef SEARCHWINDOW_H
#define SEARCHWINDOW_H

#include "qfileinfolistmodel.h"

#include <QMainWindow>

namespace Ui {
class SearchWindow;
}

/*!
 * \brief The SearchWindow class is used to create the search windows.
 */
class SearchWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit SearchWindow(QWidget *parent = nullptr);
	~SearchWindow();

private:
	Ui::SearchWindow *ui;
	QFileInfoListModel *model;
	QList<QFileInfo> results;

	void search();
};

#endif // SEARCHWINDOW_H
