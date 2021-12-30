/****************************************************************************
** Meta object code from reading C++ file 'OsgContainer.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../OsgContainer.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'OsgContainer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_OsgContainer_t {
    QByteArrayData data[8];
    char stringdata0[63];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_OsgContainer_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_OsgContainer_t qt_meta_stringdata_OsgContainer = {
    {
QT_MOC_LITERAL(0, 0, 12), // "OsgContainer"
QT_MOC_LITERAL(1, 13, 8), // "slotSnow"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 5), // "state"
QT_MOC_LITERAL(4, 29, 8), // "slotRain"
QT_MOC_LITERAL(5, 38, 6), // "slotWu"
QT_MOC_LITERAL(6, 45, 8), // "slotFire"
QT_MOC_LITERAL(7, 54, 8) // "slotBoom"

    },
    "OsgContainer\0slotSnow\0\0state\0slotRain\0"
    "slotWu\0slotFire\0slotBoom"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_OsgContainer[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x0a /* Public */,
       4,    1,   42,    2, 0x0a /* Public */,
       5,    1,   45,    2, 0x0a /* Public */,
       6,    1,   48,    2, 0x0a /* Public */,
       7,    1,   51,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,

       0        // eod
};

void OsgContainer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        OsgContainer *_t = static_cast<OsgContainer *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->slotSnow((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->slotRain((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->slotWu((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->slotFire((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->slotBoom((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject OsgContainer::staticMetaObject = {
    { &QOpenGLWidget::staticMetaObject, qt_meta_stringdata_OsgContainer.data,
      qt_meta_data_OsgContainer,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *OsgContainer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *OsgContainer::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_OsgContainer.stringdata0))
        return static_cast<void*>(const_cast< OsgContainer*>(this));
    if (!strcmp(_clname, "osgViewer::Viewer"))
        return static_cast< osgViewer::Viewer*>(const_cast< OsgContainer*>(this));
    return QOpenGLWidget::qt_metacast(_clname);
}

int OsgContainer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QOpenGLWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
