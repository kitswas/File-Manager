#ifndef NAVPAGE_H
#define NAVPAGE_H

#include "diriteminfo.h"
#include "driveinfo.h"
#include "mainwindow.h"

#include <QAbstractItemView>
#include <QDir>

namespace Ui {
class Navpage;
}

/*!
 * \brief The Navpage class
 *
 * The main window contains a tab panel. Each tab is modelled by a Navpage.
 */
class Navpage : public QWidget
{
	Q_OBJECT

public:
	explicit Navpage(QFileSystemModel *model, MainWindow *root, QWidget *parent = nullptr);
	~Navpage();
	int change_dir(QString new_dir);
	inline QString get_current_dir() const { return current_dir->absolutePath(); }
	QStringList get_selection();

private:
	Ui::Navpage *ui;
	DriveInfo *driveInfo;
	DirItemInfo *itemInfo;
	MainWindow *root;
	QDir *current_dir;
	QAbstractItemView *dirView;
	QFileSystemModel *model;

	void set_up_dirview();

private slots:
	void dirView_open_item(const QModelIndex &index);
	void dirView_show_iteminfo(const QModelIndex &index);
};

#endif // NAVPAGE_H
