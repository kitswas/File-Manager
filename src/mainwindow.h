#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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

private slots:
	void on_actionExit_triggered();

	void on_actionNew_tab_triggered();

	void on_tabWidget_currentChanged(int index);

	void on_tabWidget_tabCloseRequested(int index);

	void on_addressBar_returnPressed();

	void on_treeView_clicked(const QModelIndex &index);

private:
	Ui::MainWindow *ui;
	void locate_in_tree(const QString &path);
	void show_warning(const QString &message);
};
#endif // MAINWINDOW_H
