/****************************************************************************
** Meta object code from reading C++ file 'view_config_serial_connect.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../src_project_independent/view_config_serial_connect.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'view_config_serial_connect.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_TViewConfigSerialConnect[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      26,   25,   25,   25, 0x05,
      41,   25,   25,   25, 0x05,

 // slots: signature, parameters, type, tag, flags
      53,   25,   25,   25, 0x08,
      65,   25,   25,   25, 0x08,
      80,   25,   25,   25, 0x08,
     100,   25,   25,   25, 0x08,
     119,   25,   25,   25, 0x08,
     135,   25,   25,   25, 0x0a,
     152,   25,   25,   25, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_TViewConfigSerialConnect[] = {
    "TViewConfigSerialConnect\0\0sgDisconnect()\0"
    "sgConnect()\0slConnect()\0slDisconnect()\0"
    "slRescanPortsList()\0slSetVisualState()\0"
    "slPortChecker()\0slLoadSettings()\0"
    "slSaveSettings()\0"
};

void TViewConfigSerialConnect::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        TViewConfigSerialConnect *_t = static_cast<TViewConfigSerialConnect *>(_o);
        switch (_id) {
        case 0: _t->sgDisconnect(); break;
        case 1: _t->sgConnect(); break;
        case 2: _t->slConnect(); break;
        case 3: _t->slDisconnect(); break;
        case 4: _t->slRescanPortsList(); break;
        case 5: _t->slSetVisualState(); break;
        case 6: _t->slPortChecker(); break;
        case 7: _t->slLoadSettings(); break;
        case 8: _t->slSaveSettings(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData TViewConfigSerialConnect::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject TViewConfigSerialConnect::staticMetaObject = {
    { &QGroupBox::staticMetaObject, qt_meta_stringdata_TViewConfigSerialConnect,
      qt_meta_data_TViewConfigSerialConnect, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &TViewConfigSerialConnect::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *TViewConfigSerialConnect::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *TViewConfigSerialConnect::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_TViewConfigSerialConnect))
        return static_cast<void*>(const_cast< TViewConfigSerialConnect*>(this));
    return QGroupBox::qt_metacast(_clname);
}

int TViewConfigSerialConnect::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGroupBox::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void TViewConfigSerialConnect::sgDisconnect()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void TViewConfigSerialConnect::sgConnect()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
