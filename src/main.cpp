#include "mainwindow.h"

#include <QApplication>
#include <QDir>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QDir::setCurrent(QDir::homePath());
	MainWindow w;
	w.add_page_to_tabpanel(QDir::homePath(), "Home");
	qDebug() << "Home" << QDir::homePath();
	w.show();
	return a.exec();
}
