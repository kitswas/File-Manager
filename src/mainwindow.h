#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QList>
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui
{
	class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = nullptr);
	~MainWindow();

	int add_page_to_tabpanel(QString dir, const QString &label);

	enum class CDSource { Navbar, Navpage, Navtree, Navbutton, Tabchange };

private slots:
	void on_actionExit_triggered();

	void on_actionNew_tab_triggered();

	void on_tabWidget_currentChanged(int index);

	void on_tabWidget_tabCloseRequested(int index);

	void on_addressBar_returnPressed();

	void on_treeView_activated(const QModelIndex &index);

	void on_backButton_clicked();

	void on_upButton_clicked();

private:
	Ui::MainWindow *ui;
	QList<QString> visitedPaths;

	bool check_n_change_dir(const QString &path, CDSource source, bool suppress_warning = false);
	void locate_in_tree(const QString &path);
	void show_warning(const QString &message);

	friend class Navpage;
};
#endif // MAINWINDOW_H
