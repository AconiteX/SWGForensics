/****************************************************************************
** Meta object code from reading C++ file 'processlist.h'
**
** Created: Thu 10. Mar 23:24:21 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/swgforensics/processlist/processlist.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'processlist.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ProcessList[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      18,   13,   12,   12, 0x0a,
      52,   12,   12,   12, 0x0a,
      62,   12,   12,   12, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_ProcessList[] = {
    "ProcessList\0\0item\0selectedProcess(QListWidgetItem*)\0"
    "refresh()\0updateSearchString()\0"
};

const QMetaObject ProcessList::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_ProcessList,
      qt_meta_data_ProcessList, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ProcessList::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ProcessList::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ProcessList::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ProcessList))
        return static_cast<void*>(const_cast< ProcessList*>(this));
    return QWidget::qt_metacast(_clname);
}

int ProcessList::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: selectedProcess((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 1: refresh(); break;
        case 2: updateSearchString(); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
