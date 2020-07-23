/****************************************************************************
** Meta object code from reading C++ file 'view_calibration_structure.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../src_project_independent/view_calibration_structure.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'view_calibration_structure.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_TViewCalibrationStructureControl[] = {

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
      34,   33,   33,   33, 0x0a,
      59,   33,   33,   33, 0x0a,
      84,   33,   33,   33, 0x0a,
     100,   33,   33,   33, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_TViewCalibrationStructureControl[] = {
    "TViewCalibrationStructureControl\0\0"
    "slUpdateVisualFromData()\0"
    "slUpdateDataFromVisual()\0slAddNewPoint()\0"
    "slDelLastPoint()\0"
};

void TViewCalibrationStructureControl::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        TViewCalibrationStructureControl *_t = static_cast<TViewCalibrationStructureControl *>(_o);
        switch (_id) {
        case 0: _t->slUpdateVisualFromData(); break;
        case 1: _t->slUpdateDataFromVisual(); break;
        case 2: _t->slAddNewPoint(); break;
        case 3: _t->slDelLastPoint(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData TViewCalibrationStructureControl::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject TViewCalibrationStructureControl::staticMetaObject = {
    { &QGroupBox::staticMetaObject, qt_meta_stringdata_TViewCalibrationStructureControl,
      qt_meta_data_TViewCalibrationStructureControl, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &TViewCalibrationStructureControl::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *TViewCalibrationStructureControl::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *TViewCalibrationStructureControl::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_TViewCalibrationStructureControl))
        return static_cast<void*>(const_cast< TViewCalibrationStructureControl*>(this));
    return QGroupBox::qt_metacast(_clname);
}

int TViewCalibrationStructureControl::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGroupBox::qt_metacall(_c, _id, _a);
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
