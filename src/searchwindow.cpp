#include "searchwindow.h"
#include "ui_searchwindow.h"

SearchWindow::SearchWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::SearchWindow)
{
	ui->setupUi(this);

	//Setup search buttons
	ui->buttonBox->addButton("Search", QDialogButtonBox::ButtonRole::ApplyRole);
}

SearchWindow::~SearchWindow()
{
	delete ui;
}
