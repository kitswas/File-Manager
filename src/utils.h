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
QString format_bytes(qint64 bytes);

#endif // UTILS_H
