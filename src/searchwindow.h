#ifndef SEARCHWINDOW_H
#define SEARCHWINDOW_H

#include <QFileInfo>
#include <QMainWindow>

namespace Ui {
class SearchWindow;
}

class SearchWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit SearchWindow(QWidget *parent = nullptr);
	~SearchWindow();

private:
	Ui::SearchWindow *ui;
	QList<QFileInfo> results;

	void search();
};

#endif // SEARCHWINDOW_H
