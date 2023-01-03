#ifndef UTILS_H
#define UTILS_H

#include <QtCore>

QString to_higher_unit_from_bytes(qint64 bytes)
{
	QString result;
	qint64 higher = bytes;
	int index = 0;
	QString units[] = {"B", "KB", "MB", "GB", "TB"};
	while (higher > 1000) {
		++index;
		higher /= 1000;
	}
	result = QString::number(higher) + " " + units[index];
	return result;
}

#endif // UTILS_H
