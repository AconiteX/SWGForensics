/****************************************************************************
** Meta object code from reading C++ file 'objectstolua.h'
**
** Created: Thu 10. Mar 23:24:26 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/swgforensics/tools/objects/objectstolua/objectstolua.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'objectstolua.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ObjectsToLua[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      19,   13,   14,   13, 0x0a,
      47,   43,   14,   13, 0x0a,
      78,   13,   14,   13, 0x0a,
      88,   13,   14,   13, 0x0a,
     106,   13,   13,   13, 0x0a,
     127,  122,   13,   13, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_ObjectsToLua[] = {
    "ObjectsToLua\0\0bool\0openObjectIffTemplate()\0"
    "dir\0openObjectIffTemplateDir(QDir)\0"
    "openDir()\0convertToLuaDir()\0openFloorMesh()\0"
    "item\0selectedVariable(QListWidgetItem*)\0"
};

const QMetaObject ObjectsToLua::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_ObjectsToLua,
      qt_meta_data_ObjectsToLua, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ObjectsToLua::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ObjectsToLua::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ObjectsToLua::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ObjectsToLua))
        return static_cast<void*>(const_cast< ObjectsToLua*>(this));
    return QWidget::qt_metacast(_clname);
}

int ObjectsToLua::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: { bool _r = openObjectIffTemplate();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 1: { bool _r = openObjectIffTemplateDir((*reinterpret_cast< QDir(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 2: { bool _r = openDir();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 3: { bool _r = convertToLuaDir();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 4: openFloorMesh(); break;
        case 5: selectedVariable((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
