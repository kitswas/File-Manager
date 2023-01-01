#ifndef NAVPAGE_H
#define NAVPAGE_H

#include <QAbstractItemView>
#include <QDir>
#include <QFileSystemModel>
#include <QWidget>

namespace Ui {
class Navpage;
}

class Navpage : public QWidget
{
	Q_OBJECT

public:
	explicit Navpage(QFileSystemModel *model, QWidget *parent = nullptr);
	~Navpage();
	int change_dir(QString new_dir);
	inline QString get_current_dir() const { return current_dir->absolutePath(); }

private:
	Ui::Navpage *ui;
	QDir *current_dir;
	QAbstractItemView *dirView;
	QLayout *layout;
	QFileSystemModel *model;

	void set_up_dirview();
};

#endif // NAVPAGE_H
