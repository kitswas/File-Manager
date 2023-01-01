#include "navpage.h"
#include "ui_navpage.h"

#include <QColumnView>
#include <QFileSystemModel>
#include <QLayout>
#include <QListView>
#include <QTableView>
#include <QTreeView>

Navpage::Navpage(QFileSystemModel *model, QWidget *parent)
	: QWidget(parent), ui(new Ui::Navpage), model(model)
{
	ui->setupUi(this);
	layout = new QHBoxLayout(this);
	setLayout(layout);
	QListView *view = new QListView();
	view->setUniformItemSizes(true);
	view->setWordWrap(true);
	view->setViewMode(QListView::IconMode);
	view->setMovement(QListView::Static);
	view->setResizeMode(QListView::Adjust);
	dirView = static_cast<QAbstractItemView *>(view);
	layout->addWidget(dirView);
	set_up_dirview();
}

Navpage::~Navpage()
{
	delete ui;
	delete dirView;
	delete current_dir;
}

int Navpage::change_dir(QString new_dir)
{
	current_dir = new QDir(new_dir);
	QDir::setCurrent(get_current_dir());
	auto index = model->index(QDir::currentPath());
	qDebug() << index;
	dirView->setRootIndex(index);
	return 0;
}

void Navpage::set_up_dirview()
{
	if (dirView->objectName().isEmpty())
		dirView->setObjectName("dirView");
	dirView->resize(0, 0);
	dirView->adjustSize();
	QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
	sizePolicy.setHorizontalStretch(1);
	sizePolicy.setVerticalStretch(1);
	//	sizePolicy.setHeightForWidth(dirView->sizePolicy().hasHeightForWidth());
	dirView->setSizePolicy(sizePolicy);
	dirView->setMinimumSize(QSize(400, 300));
	dirView->setAcceptDrops(true);

	dirView->setModel(model);
	qDebug() << dirView;
	auto index = model->index(QDir::currentPath());
	qDebug() << index;
	dirView->setRootIndex(index);
}
