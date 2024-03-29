#include "searchwindow.h"
#include "ui_searchwindow.h"

#include <QDirIterator>
#include <QHeaderView>
#include <QPushButton>

SearchWindow::SearchWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::SearchWindow)
{
	ui->setupUi(this);

	ui->search_path->setText(QDir::currentPath());

	model = new QFileInfoListModel();
	ui->resultView->setModel(model);

	connect(ui->searchButton, &QPushButton::clicked, this, &SearchWindow::search);
}

SearchWindow::~SearchWindow()
{
	delete ui;
	delete model;
}

void SearchWindow::search()
{
	QString key = ui->search_key->text();
	QString searchpath = ui->search_path->text();
	Qt::CaseSensitivity caseSensitivity = ui->caseSensitive->isChecked() ? Qt::CaseSensitive
	                                                                     : Qt::CaseInsensitive;
	results.clear();

	QString oldTitle = this->windowTitle();
	this->setWindowTitle("Searching...please wait"); //Inform the user

	QDir::Filters filters = QDir::AllEntries | QDir::NoDotAndDotDot;

	if (ui->searchHidden->isChecked())
		filters |= QDir::Hidden;
	if (ui->searchSystem->isChecked())
		filters |= QDir::System;

	QDirIterator diritems(searchpath, filters, QDirIterator::Subdirectories);

	while (diritems.hasNext()) {
		const QFileInfo fileInfo = diritems.nextFileInfo();
		if (fileInfo.fileName().contains(key, caseSensitivity)) {
			results.append(fileInfo);
			qDebug() << fileInfo;
		}
	}

	static_cast<QFileInfoListModel *>(ui->resultView->model())->setQFileInfoList(results);
	ui->resultView->resizeColumnsToContents();

	this->setWindowTitle(oldTitle);
}
