#include "driveinfo.h"
#include "ui_driveinfo.h"
#include "utils.h"

DriveInfo::DriveInfo(QWidget *parent)
	: QWidget(parent)
	, ui(new Ui::DriveInfo)
{
	ui->setupUi(this);
	info = nullptr;
}

DriveInfo::~DriveInfo()
{
	delete ui;
	delete info;
}

void DriveInfo::refreshDrive(const QString &path)
{
	if (info)
		delete info;
	info = new QStorageInfo(path);
	ui->name->setText(info->displayName());
	ui->filesys->setText(info->fileSystemType());
	ui->free_space->setText(format_bytes(info->bytesFree()));
	ui->size->setText(format_bytes(info->bytesTotal()));
}
