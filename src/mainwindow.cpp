#include "mainwindow.h"
#include "navpage.h"
#include "ui_mainwindow.h"

#include <QClipboard>
#include <QDebug>
#include <QDir>
#include <QInputDialog>
#include <QLineEdit>
#include <QMessageBox>
#include <QObject>
#include <QTabWidget>
#include <QTextEdit>
#include <QWidget>

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	visitedPaths.clear();

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
	visitedPaths.push_back(dir);
	return 0;
}

bool MainWindow::check_n_change_dir(const QString &path, CDSource source, bool suppress_warning)
{
	QDir *dir = new QDir(path);
	QString message = "This is not a folder.";
	if (dir->exists()) {
		QDir::setCurrent(path);

		if (source != CDSource::Navtree) {
			locate_in_tree(path);
		}
		if (source != CDSource::Navbar) {
			ui->addressBar->setText(dir->absolutePath());
			ui->addressBar->update();
		}
		if (source != CDSource::Tabchange) {
			Navpage *currentpage = static_cast<Navpage *>(ui->tabWidget->currentWidget());
			if (currentpage != nullptr) {
				currentpage->change_dir(dir->absolutePath());
				ui->tabWidget->setTabText(ui->tabWidget->currentIndex(), dir->dirName());
				ui->tabWidget->update();
			}
		}

		visitedPaths.push_back(path);
		qDebug() << visitedPaths.size();
		delete dir;
		return true;
	} else {
		if (!suppress_warning)
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

void MainWindow::on_treeView_activated(const QModelIndex &index)
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

void MainWindow::on_backButton_clicked()
{
	if (!visitedPaths.isEmpty()) {
		visitedPaths.pop_back(); // Remove current path
	}

	if (!visitedPaths.isEmpty()) {
		QString prev_path = visitedPaths.back();
		visitedPaths.pop_back(); // Remove previous path
		check_n_change_dir(prev_path, CDSource::Navbutton);
	}
}

void MainWindow::on_upButton_clicked()
{
	QDir dir = QDir::current();
	if (dir.cdUp())
		check_n_change_dir(dir.absolutePath(), CDSource::Navbutton);
}

void MainWindow::on_actionNew_folder_triggered()
{
	bool ok;
	QString path = QInputDialog::getText(this,
	                                     tr("Create a new folder"),
	                                     tr("Enter path:"),
	                                     QLineEdit::Normal,
	                                     tr("New folder"),
	                                     &ok);

	if (ok && !path.isEmpty()) {
		QDir dir;
		if (!dir.exists(path)) {
			dir.mkdir(path);
			qDebug() << "Directory created successfully";
		} else {
			qDebug() << "Directory already exists";
		}
	}
}

void MainWindow::on_actionDelete_triggered()
{
	Navpage *currentpage = static_cast<Navpage *>(ui->tabWidget->currentWidget());
	if (currentpage) {
		QStringList paths_to_delete = currentpage->get_selection();
		QMessageBox::StandardButton choice
			= QMessageBox::warning(this,
		                           "Confirm delete",
		                           "Are you sure you want to delete the selected items?",
		                           QMessageBox::Ok | QMessageBox::Cancel);
		if (choice == QMessageBox::Ok) {
			foreach (QString path, paths_to_delete) {
				QFileInfo fileInfo(path);
				if (fileInfo.isDir()) {
					QDir dir(path);
					if (!dir.removeRecursively()) {
						qDebug() << "Failed to delete folder: " << path;
					}
				} else {
					QFile file(path);
					if (!file.remove()) {
						qDebug() << "Failed to delete file: " << path;
					}
				}
			}
		}
	}
}

void MainWindow::on_actionRename_triggered()
{
	Navpage *currentpage = static_cast<Navpage *>(ui->tabWidget->currentWidget());
	if (currentpage) {
		QStringList selectedItems = currentpage->get_selection();
		foreach (QString selectedItem, selectedItems) {
			if (!selectedItem.isEmpty()) {
				bool ok;
				QFileInfo fileInfo(selectedItem);
				QString newName = QInputDialog::getText(this,
				                                        tr("Rename"),
				                                        tr("New name:"),
				                                        QLineEdit::Normal,
				                                        fileInfo.completeBaseName(),
				                                        &ok);
				if (ok && !newName.isEmpty()) {
					QFile item(selectedItem);
					QString itemType = fileInfo.isDir() ? "Folder" : "File";
					if (item.rename(newName)) {
						qDebug() << itemType << " renamed successfully";
					} else {
						qDebug() << "Error renaming " << itemType;
					}
				}
			}
		}
	}
}

void MainWindow::on_actionCopy_triggered()
{
	Navpage *currentpage = static_cast<Navpage *>(ui->tabWidget->currentWidget());
	if (currentpage) {
		itemsToMove.clear();
		itemsToCopy = currentpage->get_selection();
		qDebug() << "Copied successfully";
	}
}

void MainWindow::on_actionPaste_triggered()
{
	Navpage *currentpage = static_cast<Navpage *>(ui->tabWidget->currentWidget());
	if (currentpage) {
		foreach (QString path, itemsToCopy) {
			QFile item(path);
			QString newName = item.fileName();
			item.close();
			qDebug() << "Copy result" << item.copy(QDir::current().absoluteFilePath(newName));
		}
		foreach (QString path, itemsToMove) {
			QFile item(path);
			qDebug() << "Copy result" << QFile::copy(path, QDir::currentPath() + item.fileName());
			qDebug() << "Remove result" << item.remove();
		}

		//		if (!item.isEmpty()) {
		//			QFileInfo fileInfo(item);
		//			QString newName = QInputDialog::getText(this,
		//			                                        tr("Paste"),
		//			                                        tr("New name:"),
		//			                                        QLineEdit::Normal,
		//			                                        fileInfo.completeBaseName());
		//			if (!newName.isEmpty()) {
		//				QFile item(clipboard->text());
		//				QString itemType = fileInfo.isDir() ? "Folder" : "File";
		//				if (item.rename(newName)) {
		//					qDebug() << itemType << " pasted successfully";
		//				} else {
		//					qDebug() << "Error pasting " << itemType;
		//				}
		//			}
		//		}
	}
}

void MainWindow::on_actionCut_triggered()
{
	Navpage *currentpage = static_cast<Navpage *>(ui->tabWidget->currentWidget());
	if (currentpage) {
		itemsToCopy.clear();
		itemsToMove = currentpage->get_selection();
	}
}

//void MainWindow::on_actionSearch_triggered()
//{
//	Navpage *currentpage = static_cast<Navpage *>(ui->tabWidget->currentWidget());
//	if (currentpage) {
//		bool ok;
//		QString searchTerm = QInputDialog::getText(this,
//		                                           tr("Search"),
//		                                           tr("Enter the search term:"),
//		                                           QLineEdit::Normal,
//		                                           "",
//		                                           &ok);
//		if (ok && !searchTerm.isEmpty()) {
//			QStringList searchResults = currentpage->search(searchTerm);
//			if (!searchResults.isEmpty()) {
//				qDebug() << "Search results:";
//				foreach (QString result, searchResults) {
//					qDebug() << result;
//				}
//			} else {
//				qDebug() << "No search results found";
//			}
//		}
//	}
//}
