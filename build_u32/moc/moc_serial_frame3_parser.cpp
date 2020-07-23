/****************************************************************************
** Meta object code from reading C++ file 'serial_frame3_parser.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../src_project_independent/serial_frame3_parser.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'serial_frame3_parser.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_TSerialFrame3Parser[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      21,   20,   20,   20, 0x05,

 // slots: signature, parameters, type, tag, flags
      41,   20,   20,   20, 0x0a,
      65,   20,   20,   20, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_TSerialFrame3Parser[] = {
    "TSerialFrame3Parser\0\0connectionUpdated()\0"
    "slSerialDevicePolling()\0slSerialDeviceTimeout()\0"
};

void TSerialFrame3Parser::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        TSerialFrame3Parser *_t = static_cast<TSerialFrame3Parser *>(_o);
        switch (_id) {
        case 0: _t->connectionUpdated(); break;
        case 1: _t->slSerialDevicePolling(); break;
        case 2: _t->slSerialDeviceTimeout(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData TSerialFrame3Parser::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject TSerialFrame3Parser::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_TSerialFrame3Parser,
      qt_meta_data_TSerialFrame3Parser, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &TSerialFrame3Parser::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *TSerialFrame3Parser::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *TSerialFrame3Parser::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_TSerialFrame3Parser))
        return static_cast<void*>(const_cast< TSerialFrame3Parser*>(this));
    return QObject::qt_metacast(_clname);
}

int TSerialFrame3Parser::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void TSerialFrame3Parser::connectionUpdated()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
