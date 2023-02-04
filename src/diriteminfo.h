#ifndef DIRITEMINFO_H
#define DIRITEMINFO_H

#include <QStorageInfo>
#include <QWidget>

namespace Ui {
class DirItemInfo;
}

class DirItemInfo : public QWidget
{
	Q_OBJECT

public:
	explicit DirItemInfo(QFileInfo *info, QWidget *parent = nullptr);
	~DirItemInfo();
	void refresh();

private:
	Ui::DirItemInfo *ui;
	QFileInfo *info;
};

#endif // DIRITEMINFO_H
