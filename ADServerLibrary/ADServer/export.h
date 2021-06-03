#ifndef EXPORT_H
#define EXPORT_H

#include <QtCore/qglobal.h>

#if defined(ADSERVER_LIBRARY)
#  define ADSERVERSHARED_EXPORT Q_DECL_EXPORT
#else
#  define ADSERVERSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // EXPORT_H
