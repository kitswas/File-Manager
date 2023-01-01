#include "mainwindow.h"
#include "navpage.h"
#include "ui_mainwindow.h"
#include <QDebug>
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

	for (auto &item : QDir::drives()) {
		qDebug() << item;
		// This clearly shows that QDir::drives() doesn't detect connected MTP Devices
	}

	QFileSystemModel *model = new QFileSystemModel;
	//	model->setRootPath(QDir::currentPath());
	qDebug() << "setRootPath" << QDir::rootPath();
	model->setRootPath(QDir::rootPath());
	ui->treeView->setModel(model);
	QHeaderView *header = ui->treeView->header();
	for (int i = 1; i < header->count(); ++i) {
		header->hideSection(i);
	}
	ui->treeView->setSelectionMode(QAbstractItemView::SingleSelection);
	ui->treeView->setSelectionBehavior(QAbstractItemView::SelectRows);
	//	QModelIndex index = model->index(QDir::currentPath());
	//	qDebug() << "index" << index;

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
	Navpage *newpage = new Navpage(static_cast<QFileSystemModel *>(ui->treeView->model()));
	newpage->change_dir(dir);
	ui->tabWidget->addTab(newpage, label);
	return 0;
}

void MainWindow::locate_in_tree(const QString &path)
{
	QFileSystemModel *model = static_cast<QFileSystemModel *>(ui->treeView->model());
	QDir dir(path);
	while (dir.cdUp()) {
		auto index = model->index(dir.path());
		ui->treeView->expand(index);
	}
	auto index = model->index(path);
	ui->treeView->selectionModel()->select(index, QItemSelectionModel::ClearAndSelect);
	ui->treeView->update();
}

void MainWindow::on_actionNew_tab_triggered()
{
	add_page_to_tabpanel(QDir::homePath(), "Home");
}

void MainWindow::on_tabWidget_currentChanged([[maybe_unused]] int index)
{
	Navpage *currentpage = static_cast<Navpage *>(ui->tabWidget->currentWidget());
	if (currentpage != nullptr) {
		ui->addressBar->setText(currentpage->get_current_dir());
		locate_in_tree(currentpage->get_current_dir());
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
		Navpage *currentpage = static_cast<Navpage *>(ui->tabWidget->currentWidget());
		if (currentpage != nullptr) {
			currentpage->change_dir(path->absolutePath());
			ui->tabWidget->setTabText(ui->tabWidget->currentIndex(), path->dirName());
			locate_in_tree(currentpage->get_current_dir());
		}
	} else {
		show_warning("The folder does not exist.");
	}
	delete path;
}

void MainWindow::on_treeView_clicked(const QModelIndex &index)
{
	QFileSystemModel *model = static_cast<QFileSystemModel *>(ui->treeView->model());
	QDir *path = new QDir(model->filePath(index));
	if (path->exists()) {
		Navpage *currentpage = static_cast<Navpage *>(ui->tabWidget->currentWidget());
		if (currentpage != nullptr) {
			currentpage->change_dir(path->absolutePath());
			ui->tabWidget->setTabText(ui->tabWidget->currentIndex(), path->dirName());
			ui->addressBar->setText(path->absolutePath());
		}
	} else {
		show_warning("This is not a folder.");
	}
	delete path;
}

void MainWindow::show_warning(const QString &message)
{
	QMessageBox *alert = new QMessageBox();
	alert->setText(message);
	alert->setIcon(QMessageBox::Warning);
	alert->setWindowIcon(windowIcon());
	alert->exec();
	delete alert;
}
