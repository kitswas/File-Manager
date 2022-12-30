#include "navpage.h"
#include "ui_navpage.h"

Navpage::Navpage(QWidget *parent) :
	  QWidget(parent),
	  ui(new Ui::Navpage)
{
	ui->setupUi(this);
}

Navpage::~Navpage()
{
	delete ui;
}

int Navpage::change_dir(QString new_dir)
{
	current_dir = new QDir(new_dir);
	return 0;
}
