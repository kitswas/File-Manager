#ifndef NAVPAGE_H
#define NAVPAGE_H

#include <QDir>
#include <QWidget>

class Navpage : public QWidget
{
	Q_OBJECT
private:
	QDir *current_dir;

public:
	explicit Navpage(QWidget *parent = nullptr);
	int change_dir(QString new_dir);
	inline QString get_current_dir() { return current_dir->absolutePath(); }
signals:
};

#endif // NAVPAGE_H
