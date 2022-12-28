#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "navpage.h"
#include <QTabWidget>
#include <QLineEdit>
#include <QDir>

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
	QLineEdit *addressBar = findChild<QLineEdit *>("addressBar");
	Navpage *currentpage = (Navpage *)(tabWidget->currentWidget());
	addressBar->setText(currentpage->get_current_dir());
	return 0;
}

void MainWindow::on_actionNew_tab_triggered()
{
	add_page_to_tabpanel(QDir::homePath(), "Home");
}
