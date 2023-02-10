/*!
 * This file contains utility functions that are used throughout the application.
*/

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

/*!
 * \brief copyOrMoveDirectorySubtree
 * \param from
 * \param to
 * \param copyAndRemove If `true`, move instead of copy.
 * \param overWriteExistingFiles If `true`, overwrite existing files at the destination. **Destructive.**
 *
 * Copies a folder and all its contents.
 * Reference: https://forum.qt.io/topic/105993/copy-folder-qt-c/5?_=1675790958476&lang=en-GB
 */
void copyOrMoveDirectorySubtree(const QString &from,
                                const QString &to,
                                bool copyAndRemove,
                                bool overwriteExistingFiles);

#endif // UTILS_H
