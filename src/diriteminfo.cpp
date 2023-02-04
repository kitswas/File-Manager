#include "diriteminfo.h"
#include "ui_diriteminfo.h"
#include "utils.h"

// See https://doc.qt.io/qt-6/qfileinfo.html#details
extern Q_CORE_EXPORT int qt_ntfs_permission_lookup;

DirItemInfo::DirItemInfo(QFileInfo *info, QWidget *parent)
	: QWidget(parent)
	, ui(new Ui::DirItemInfo)
	, info(info)
{
	ui->setupUi(this);
}

DirItemInfo::~DirItemInfo()
{
	delete ui;
}

void DirItemInfo::refresh()
{
	ui->name->setText(info->fileName());
	ui->filesys->setText(info->filePath());
	QString permissions = "";
	//	qDebug() << (new QStorageInfo(QDir::current()))->fileSystemType();
	bool isNTFS = (new QStorageInfo(QDir::current()))->fileSystemType().compare("NTFS") == 0;
	if (isNTFS)
		qt_ntfs_permission_lookup++; // turn checking on
	if (info->isReadable())
		permissions += "Read ";
	if (info->isWritable())
		permissions += "Write ";
	if (info->isExecutable())
		permissions += "Execute ";
	if (isNTFS)
		qt_ntfs_permission_lookup--; // turn it off again
	ui->free_space->setText(permissions.trimmed());
	ui->size->setText(format_bytes(info->size()));
	//	info->permissions();
}
