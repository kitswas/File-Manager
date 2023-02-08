#include "searchwindow.h"
#include "ui_searchwindow.h"

SearchWindow::SearchWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::SearchWindow)
{
	ui->setupUi(this);
}

SearchWindow::~SearchWindow()
{
	delete ui;
}
