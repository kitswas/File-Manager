#include "mainwindow.h"
#include "navpage.h"

#include <QApplication>
#include <QDir>
#include <QLineEdit>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MainWindow w;
	Navpage *homepage = new Navpage();
	homepage->change_dir(QDir::homePath());
	QTabWidget *tabWidget = w.findChild<QTabWidget*>("tabWidget");
	tabWidget->addTab(homepage, "Home");
	QLineEdit *addressBar = w.findChild<QLineEdit*>("addressBar");
	Navpage *currentpage = (Navpage*)(tabWidget->currentWidget());
	addressBar->setText(currentpage->get_current_dir());
	w.show();
	return a.exec();
}
