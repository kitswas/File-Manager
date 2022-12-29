#include "navpage.h"

Navpage::Navpage(QWidget *parent)
	: QWidget{parent}
{
}

int Navpage::change_dir(QString new_dir)
{
	current_dir = new QDir(new_dir);
	return 0;
}
