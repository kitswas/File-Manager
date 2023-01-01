#include "navpage.h"
#include "ui_navpage.h"

#include <QColumnView>
#include <QLayout>
#include <QListView>
#include <QTableView>
#include <QTreeView>

Navpage::Navpage(QFileSystemModel *model, MainWindow *root, QWidget *parent)
	: QWidget(parent), ui(new Ui::Navpage), root(root), model(model)
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

	connect(dirView, &QAbstractItemView::doubleClicked, this, &Navpage::dirView_open_item);
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

void Navpage::dirView_open_item(const QModelIndex &index)
{
	qDebug() << index;
	if (root->check_n_change_dir(model->filePath(index), MainWindow::CDSource::Navpage))
		change_dir(model->filePath(index));
	else {
		//TODO open as a file
	}
}
