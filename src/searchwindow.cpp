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
	//	QPushButton *searchButton = new QPushButton("Search", ui->buttonBox);
	//	searchButton->setAutoDefault(true);
	//	ui->buttonBox->addButton(searchButton, QDialogButtonBox::ButtonRole::ApplyRole);

	ui->search_path->setText(QDir::currentPath());

	connect(ui->searchButton, &QPushButton::clicked, this, &SearchWindow::search);
}

SearchWindow::~SearchWindow()
{
	delete ui;
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

	QDirIterator diritems(searchpath, QDirIterator::Subdirectories);

	while (diritems.hasNext()) {
		const QFileInfo fileInfo = diritems.nextFileInfo();
		if (fileInfo.fileName().compare(".") == 0
		    || fileInfo.fileName().compare("..") == 0) //filters dot and dotdot
			continue;
		if (!fileInfo.isHidden()) {
			if (fileInfo.fileName().contains(key, caseSensitivity)) {
				results.append(fileInfo);
				qDebug() << fileInfo;
				ui->listWidget->addItem("Name: " + fileInfo.fileName()
				                        + "\tPath:" + fileInfo.absolutePath());
				//				ui->listWidget->addItem(fileInfo);
			}
		}
	}

	this->setWindowTitle(oldTitle);
}
