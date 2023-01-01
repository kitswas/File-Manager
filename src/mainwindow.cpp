#include "navpage.h"
#include "ui_mainwindow.h"

#include <QDebug>
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
	Navpage *newpage = new Navpage(static_cast<QFileSystemModel *>(ui->treeView->model()), this);
	newpage->change_dir(dir);
	ui->tabWidget->addTab(newpage, label);
	return 0;
}

bool MainWindow::check_n_change_dir(const QString &path, CDSource source)
{
	QDir *dir = new QDir(path);
	QString message = "This is not a folder.";
	if (dir->exists()) {
		if (source != CDSource::Navtree) {
			locate_in_tree(path);
		}
		if (source != CDSource::Navbar) {
			ui->addressBar->setText(dir->absolutePath());
		}
		if (source != CDSource::Tabchange) {
			Navpage *currentpage = static_cast<Navpage *>(ui->tabWidget->currentWidget());
			if (currentpage != nullptr) {
				currentpage->change_dir(dir->absolutePath());
				ui->tabWidget->setTabText(ui->tabWidget->currentIndex(), dir->dirName());
			}
		}

		QDir::setCurrent(path);
		delete dir;
		return true;
	} else {
		show_warning(message);
		delete dir;
		return false;
	}
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
	check_n_change_dir(ui->addressBar->text(), CDSource::Navbar);
}

void MainWindow::on_treeView_clicked(const QModelIndex &index)
{
	QFileSystemModel *model = static_cast<QFileSystemModel *>(ui->treeView->model());
	check_n_change_dir(model->filePath(index), CDSource::Navtree);
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
