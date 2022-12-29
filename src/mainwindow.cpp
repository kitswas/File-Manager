#include "mainwindow.h"
#include "navpage.h"
#include "ui_mainwindow.h"
#include <QDir>
#include <QLineEdit>
#include <QMessageBox >
#include <QTabWidget>

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent), ui(new Ui::MainWindow)
{
	ui->setupUi(this);
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
	QTabWidget *tabWidget = findChild<QTabWidget *>("tabWidget");
	tabWidget->addTab(newpage, label);
	return 0;
}

void MainWindow::on_actionNew_tab_triggered()
{
	add_page_to_tabpanel(QDir::homePath(), "Home");
}

void MainWindow::on_tabWidget_currentChanged(int index)
{
	QTabWidget *tabWidget = findChild<QTabWidget *>("tabWidget");
	QLineEdit *addressBar = findChild<QLineEdit *>("addressBar");
	Navpage *currentpage = (Navpage *)(tabWidget->currentWidget());
	if (currentpage != nullptr)
		addressBar->setText(currentpage->get_current_dir());
}

void MainWindow::on_tabWidget_tabCloseRequested(int index)
{
	QTabWidget *tabWidget = findChild<QTabWidget *>("tabWidget");
	tabWidget->removeTab(index);
}

void MainWindow::on_addressBar_returnPressed()
{
	QLineEdit *addressBar = findChild<QLineEdit *>("addressBar");
	QDir *path = new QDir(addressBar->text());
	if (path->exists()) {
		QTabWidget *tabWidget = findChild<QTabWidget *>("tabWidget");
		Navpage *currentpage = (Navpage *) (tabWidget->currentWidget());
		if (currentpage != nullptr) {
			currentpage->change_dir(path->absolutePath());
			tabWidget->setTabText(tabWidget->currentIndex(), path->dirName());
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
