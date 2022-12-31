#include "mainwindow.h"
#include "navpage.h"
#include "ui_mainwindow.h"
#include <QDir>
#include <QFileSystemModel>
#include <QLineEdit>
#include <QMessageBox>
#include <QTabWidget>

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent), ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	/*ui->treeWidget->setColumnCount(1);
	QList<QTreeWidgetItem> drives;
	for (auto &item : QDir::drives()) {
		drives.append(new QTreeWidgetItem());
	}*/
	//	ui->treeWidget->addTopLevelItems();
	QFileSystemModel *model = new QFileSystemModel;
	model->setRootPath(QDir::currentPath());
	ui->treeView->setModel(model);
	QHeaderView *header = ui->treeView->header();
	for (int i = 1; i < header->count(); ++i) {
		header->hideSection(i);
	}
	auto index = model->index(QDir::currentPath());
	ui->treeView->selectionModel()->select(index,
	                                       QItemSelectionModel::ClearAndSelect
	                                           | QItemSelectionModel::Rows);
	ui->treeView->resizeColumnToContents(0);
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::on_actionExit_triggered()
{
	exit(EXIT_SUCCESS);
}

int MainWindow::add_page_to_tabpanel(QString dir, const QString &label)
{
	Navpage *newpage = new Navpage();
	newpage->change_dir(dir);
	ui->tabWidget->addTab(newpage, label);
	return 0;
}

void MainWindow::on_actionNew_tab_triggered()
{
	add_page_to_tabpanel(QDir::homePath(), "Home");
}

void MainWindow::on_tabWidget_currentChanged(int index)
{
	Navpage *currentpage = (Navpage *) (ui->tabWidget->currentWidget());
	if (currentpage != nullptr) {
		ui->addressBar->setText(currentpage->get_current_dir());
		QDir::setCurrent(currentpage->get_current_dir());
	}
}

void MainWindow::on_tabWidget_tabCloseRequested(int index)
{
	ui->tabWidget->removeTab(index);
}

void MainWindow::on_addressBar_returnPressed()
{
	QDir *path = new QDir(ui->addressBar->text());
	if (path->exists()) {
		Navpage *currentpage = (Navpage *) (ui->tabWidget->currentWidget());
		if (currentpage != nullptr) {
			currentpage->change_dir(path->absolutePath());
			ui->tabWidget->setTabText(ui->tabWidget->currentIndex(), path->dirName());
		}
	} else {
		QMessageBox *alert = new QMessageBox();
		alert->setText("The folder does not exist.");
		alert->setIcon(QMessageBox::Warning);
		alert->setWindowIcon(windowIcon());
		alert->exec();
		delete alert;
	}
	delete path;
}

void MainWindow::on_treeView_clicked(const QModelIndex &index)
{
	QFileSystemModel *model = static_cast<QFileSystemModel *>(ui->treeView->model());
	QDir *path = new QDir(model->filePath(index));
	if (path->exists()) {
		ui->addressBar->setText(path->absolutePath());
		Navpage *currentpage = (Navpage *) (ui->tabWidget->currentWidget());
		if (currentpage != nullptr) {
			currentpage->change_dir(path->absolutePath());
			ui->tabWidget->setTabText(ui->tabWidget->currentIndex(), path->dirName());
		}
	} else {
		QMessageBox *alert = new QMessageBox();
		alert->setText("The folder does not exist.");
		alert->setIcon(QMessageBox::Warning);
		alert->exec();
		delete alert;
	}
	delete path;
}
