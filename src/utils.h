#ifndef UTILS_H
#define UTILS_H

#include <QtCore>

/*!
 * \brief Format the provided number as bytes.
 * \param bytes
 * \return a string
 * 
 * Aims to present the number in a human-friendly format.  
 * Converts bytes to a higher order unit ("KB", "MB", "GB", "TB"), if possible. 
 */
QString format_bytes(qint64 bytes)
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