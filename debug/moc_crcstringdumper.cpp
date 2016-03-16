/****************************************************************************
** Meta object code from reading C++ file 'crcstringdumper.h'
**
** Created: Thu 10. Mar 23:24:20 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/swgforensics/tools/crcdumper/crcstringdumper.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'crcstringdumper.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_crcstringdumper[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      21,   17,   16,   16, 0x05,

 // slots: signature, parameters, type, tag, flags
      46,   16,   16,   16, 0x0a,
      68,   16,   16,   16, 0x0a,
     100,   89,   16,   16, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_crcstringdumper[] = {
    "crcstringdumper\0\0str\0outputToConsole(QString)\0"
    "startDumpingStrings()\0stopDumpingStrings()\0"
    "breakpoint\0handleBreakpoint(Breakpoint*)\0"
};

const QMetaObject crcstringdumper::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_crcstringdumper,
      qt_meta_data_crcstringdumper, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &crcstringdumper::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *crcstringdumper::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *crcstringdumper::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_crcstringdumper))
        return static_cast<void*>(const_cast< crcstringdumper*>(this));
    if (!strcmp(_clname, "BreakpointHandler"))
        return static_cast< BreakpointHandler*>(const_cast< crcstringdumper*>(this));
    return QWidget::qt_metacast(_clname);
}

int crcstringdumper::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: outputToConsole((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: startDumpingStrings(); break;
        case 2: stopDumpingStrings(); break;
        case 3: handleBreakpoint((*reinterpret_cast< Breakpoint*(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void crcstringdumper::outputToConsole(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
