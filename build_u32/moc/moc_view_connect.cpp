/****************************************************************************
** Meta object code from reading C++ file 'view_connect.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../src/view_connect.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'view_connect.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_TViewMachineConnect[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      21,   20,   20,   20, 0x0a,
      38,   20,   20,   20, 0x0a,
      55,   20,   20,   20, 0x0a,
      76,   20,   20,   20, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_TViewMachineConnect[] = {
    "TViewMachineConnect\0\0slSaveSettings()\0"
    "slLoadSettings()\0slSerialPortOpened()\0"
    "slSerialPortClosed()\0"
};

void TViewMachineConnect::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        TViewMachineConnect *_t = static_cast<TViewMachineConnect *>(_o);
        switch (_id) {
        case 0: _t->slSaveSettings(); break;
        case 1: _t->slLoadSettings(); break;
        case 2: _t->slSerialPortOpened(); break;
        case 3: _t->slSerialPortClosed(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData TViewMachineConnect::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject TViewMachineConnect::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_TViewMachineConnect,
      qt_meta_data_TViewMachineConnect, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &TViewMachineConnect::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *TViewMachineConnect::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *TViewMachineConnect::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_TViewMachineConnect))
        return static_cast<void*>(const_cast< TViewMachineConnect*>(this));
    return QWidget::qt_metacast(_clname);
}

int TViewMachineConnect::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
