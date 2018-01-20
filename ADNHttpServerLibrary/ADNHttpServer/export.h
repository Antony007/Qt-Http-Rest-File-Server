#ifndef EXPORT_H
#define EXPORT_H

#include <QtCore/qglobal.h>

#if defined(ADNHTTPSERVER_LIBRARY)
#  define ADNHTTPSERVERSHARED_EXPORT Q_DECL_EXPORT
#else
#  define ADNHTTPSERVERSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // EXPORT_H
