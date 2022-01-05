/****************************************************************************
** Meta object code from reading C++ file 'osgearthwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../osgearthwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'osgearthwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_OSGEarthWindow_t {
    QByteArrayData data[8];
    char stringdata0[85];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_OSGEarthWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_OSGEarthWindow_t qt_meta_stringdata_OSGEarthWindow = {
    {
QT_MOC_LITERAL(0, 0, 14), // "OSGEarthWindow"
QT_MOC_LITERAL(1, 15, 15), // "signDrawLineWid"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 1), // "a"
QT_MOC_LITERAL(4, 34, 17), // "slotShowLonLatAlt"
QT_MOC_LITERAL(5, 52, 9), // "osg::Vec3"
QT_MOC_LITERAL(6, 62, 3), // "lla"
QT_MOC_LITERAL(7, 66, 18) // "slotReDefaultCombo"

    },
    "OSGEarthWindow\0signDrawLineWid\0\0a\0"
    "slotShowLonLatAlt\0osg::Vec3\0lla\0"
    "slotReDefaultCombo"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_OSGEarthWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    1,   32,    2, 0x0a /* Public */,
       7,    0,   35,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Float,    3,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void,

       0        // eod
};

void OSGEarthWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        OSGEarthWindow *_t = static_cast<OSGEarthWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signDrawLineWid((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 1: _t->slotShowLonLatAlt((*reinterpret_cast< const osg::Vec3(*)>(_a[1]))); break;
        case 2: _t->slotReDefaultCombo(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (OSGEarthWindow::*_t)(float );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&OSGEarthWindow::signDrawLineWid)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject OSGEarthWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_OSGEarthWindow.data,
      qt_meta_data_OSGEarthWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *OSGEarthWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *OSGEarthWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_OSGEarthWindow.stringdata0))
        return static_cast<void*>(const_cast< OSGEarthWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int OSGEarthWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void OSGEarthWindow::signDrawLineWid(float _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
