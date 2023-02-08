#include "navpage.h"
#include "ui_navpage.h"

#include <QColumnView>
#include <QLayout>
#include <QListView>
#include <QProcess>
#include <QTableView>
#include <QTreeView>

Navpage::Navpage(QFileSystemModel *model, MainWindow *root, QWidget *parent)
	: QWidget(parent), ui(new Ui::Navpage), root(root), model(model)
{
	ui->setupUi(this);

	QListView *view = new QListView();
	view->setWordWrap(true);
	view->setViewMode(QListView::IconMode);
	view->setIconSize(QSize(48, 48));
	view->setGridSize(QSize(128, 72));
	view->setUniformItemSizes(true);
	view->setMovement(QListView::Static);
	view->setResizeMode(QListView::Adjust);
	view->setLayoutMode(QListView::Batched);
	view->setBatchSize(10);
	dirView = static_cast<QAbstractItemView *>(view);
	driveInfo = new DriveInfo(this);
	set_up_dirview();
	ui->verticalLayout->addWidget(dirView);
	ui->verticalLayout->addWidget(driveInfo);

	connect(dirView, &QAbstractItemView::doubleClicked, this, &Navpage::dirView_open_item);
}

Navpage::~Navpage()
{
	delete ui;
	delete dirView;
	delete driveInfo;
	delete current_dir;
}

int Navpage::change_dir(QString new_dir)
{
	current_dir = new QDir(new_dir);
	auto index = model->index(QDir::currentPath());
	qDebug() << index;
	dirView->setRootIndex(index);
	driveInfo->refreshDrive();
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
	if (root->check_n_change_dir(model->filePath(index), MainWindow::CDSource::Navpage, true))
		change_dir(model->filePath(index));
	else {
		qDebug() << "Should open the file here.";
		QProcess launcher;
		QString program;
		QStringList arguments;

#if defined(Q_OS_LINUX)
		program = "xdg-open";
		arguments << model->filePath(index);
#elif defined(Q_OS_WIN)
		program = "cmd.exe";
		arguments << "/C"
				  << "start"
				  << "" << model->filePath(index);
#elif defined(Q_OS_MACOS)
		program = "open";
		arguments << model->filePath(index);
#endif

		launcher.setProgram(program);
		launcher.setArguments(arguments);
		qDebug() << "Process started" << launcher.startDetached();
	}
}

QStringList Navpage::get_selection()
{
	QModelIndexList list = dirView->selectionModel()->selectedIndexes();
	QStringList path_list;
	foreach (const QModelIndex &index, list) {
		path_list.append(model->filePath(index));
	}
	qDebug() << path_list.join(",");
	return path_list;
}
