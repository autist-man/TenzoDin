/****************************************************************************
** Meta object code from reading C++ file 'ctrl_tenso.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../src/ctrl_tenso.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ctrl_tenso.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_TControlTenso[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      15,   14,   14,   14, 0x05,

 // slots: signature, parameters, type, tag, flags
      34,   14,   14,   14, 0x0a,
      55,   14,   14,   14, 0x0a,
      72,   14,   14,   14, 0x0a,
      89,   14,   14,   14, 0x0a,
     106,   14,   14,   14, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_TControlTenso[] = {
    "TControlTenso\0\0sgNewDiagramData()\0"
    "slClearDiagramData()\0slSaveSettings()\0"
    "slLoadSettings()\0slLoadTextData()\0"
    "slSaveTextData()\0"
};

void TControlTenso::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        TControlTenso *_t = static_cast<TControlTenso *>(_o);
        switch (_id) {
        case 0: _t->sgNewDiagramData(); break;
        case 1: _t->slClearDiagramData(); break;
        case 2: _t->slSaveSettings(); break;
        case 3: _t->slLoadSettings(); break;
        case 4: _t->slLoadTextData(); break;
        case 5: _t->slSaveTextData(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData TControlTenso::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject TControlTenso::staticMetaObject = {
    { &TSerialFrame3Parser::staticMetaObject, qt_meta_stringdata_TControlTenso,
      qt_meta_data_TControlTenso, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &TControlTenso::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *TControlTenso::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *TControlTenso::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_TControlTenso))
        return static_cast<void*>(const_cast< TControlTenso*>(this));
    return TSerialFrame3Parser::qt_metacast(_clname);
}

int TControlTenso::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = TSerialFrame3Parser::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void TControlTenso::sgNewDiagramData()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
