#include "searchwindow.h"
#include "ui_searchwindow.h"

#include <QDirIterator>
#include <QPushButton>

SearchWindow::SearchWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::SearchWindow)
{
	ui->setupUi(this);

	//Setup search buttons
	QPushButton *searchButton = new QPushButton("Search", ui->buttonBox);
	ui->buttonBox->addButton(searchButton, QDialogButtonBox::ButtonRole::ApplyRole);

	connect(searchButton, &QPushButton::clicked, this, &SearchWindow::search);
}

SearchWindow::~SearchWindow()
{
	delete ui;
}

void SearchWindow::search()
{
	QString key = ui->lineEdit->text();
	Qt::CaseSensitivity caseSensitivity = ui->caseSensitive->isChecked() ? Qt::CaseSensitive
	                                                                     : Qt::CaseInsensitive;
	results.clear();
	QDirIterator subdirs(QDir::current(), QDirIterator::Subdirectories);

	while (subdirs.hasNext()) {
		const QFileInfo fileInfo = subdirs.nextFileInfo();
		if (!fileInfo.isHidden()) //filters dot and dotdot
		{
			if (fileInfo.fileName().contains(key, caseSensitivity)) {
				results.append(fileInfo);
				qDebug() << fileInfo;
				ui->listWidget->addItem("Name: " + fileInfo.fileName()
				                        + "\tPath:" + fileInfo.absolutePath());
				//				ui->listWidget->addItem(fileInfo);
			}
		}
	}
}
