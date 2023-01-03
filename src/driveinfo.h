#ifndef DRIVEINFO_H
#define DRIVEINFO_H

#include <QStorageInfo>
#include <QWidget>

namespace Ui {
class DriveInfo;
}

class DriveInfo : public QWidget
{
	Q_OBJECT

  public:
	explicit DriveInfo(QWidget *parent = nullptr);
	~DriveInfo();
	void refreshDrive();

private:
	Ui::DriveInfo *ui;
	QStorageInfo *info;
};

#endif // DRIVEINFO_H
