//Сторонняя библиотека скачана с ресурса автора
//URL - http://qextserialport.github.io

#ifndef QEXTSERIALPORT_GLOBAL_H
#define QEXTSERIALPORT_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef QEXTSERIALPORT_LIB
# define QEXTSERIALPORT_EXPORT Q_DECL_EXPORT
#else
# define QEXTSERIALPORT_EXPORT Q_DECL_IMPORT
#endif

#undef QEXTSERIALPORT_EXPORT
#define QEXTSERIALPORT_EXPORT

#endif // QEXTSERIALPORT_GLOBAL_H

