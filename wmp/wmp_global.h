#ifndef WMP_GLOBAL_H
#define WMP_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(WMP_LIBRARY)
#  define WMPSHARED_EXPORT  Q_DECL_EXPORT
//#  define LTC_EXPORT        Q_DECL_EXPORT
#else
#  define WMPSHARED_EXPORT  Q_DECL_IMPORT
#  define LTC_EXPORT        Q_DECL_IMPORT
#endif

#ifdef Q_OS_WIN
#define WIN_OS      Q_OS_WIN
#endif

#endif // WMP_GLOBAL_H
