#ifndef NAVPAGE_H
#define NAVPAGE_H

#include <QDir>
#include <QWidget>

namespace Ui {
class Navpage;
}

class Navpage : public QWidget
{
	Q_OBJECT

public:
	explicit Navpage(QWidget *parent = nullptr);
	~Navpage();
	int change_dir(QString new_dir);
	inline QString get_current_dir() const { return current_dir->absolutePath(); }

private:
	Ui::Navpage *ui;
	QDir *current_dir;
};

#endif // NAVPAGE_H
