#include "mainwindow.h"

#include <QApplication>
#include <QDir>
#include <QStyleFactory>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QDir::setCurrent(QDir::homePath());
#if defined(Q_OS_WIN)
	if (QSysInfo::productVersion().toInt() >= 10)
		QApplication::setStyle(QStyleFactory::create("Fusion"));
#endif
	MainWindow w;
	w.add_page_to_tabpanel(QDir::homePath(), "Home");
	qDebug() << "Home" << QDir::homePath();
	w.showMaximized(); // Maximize on launch
	return a.exec();
}
