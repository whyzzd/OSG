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
    QByteArrayData data[11];
    char stringdata0[108];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_OsgContainer_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_OsgContainer_t qt_meta_stringdata_OsgContainer = {
    {
QT_MOC_LITERAL(0, 0, 12), // "OsgContainer"
QT_MOC_LITERAL(1, 13, 9), // "startWork"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 8), // "slotSnow"
QT_MOC_LITERAL(4, 33, 5), // "state"
QT_MOC_LITERAL(5, 39, 8), // "slotRain"
QT_MOC_LITERAL(6, 48, 6), // "slotWu"
QT_MOC_LITERAL(7, 55, 8), // "slotFire"
QT_MOC_LITERAL(8, 64, 8), // "slotBoom"
QT_MOC_LITERAL(9, 73, 16), // "slotAddNetArcgis"
QT_MOC_LITERAL(10, 90, 17) // "slotRemvNetArcgis"

    },
    "OsgContainer\0startWork\0\0slotSnow\0state\0"
    "slotRain\0slotWu\0slotFire\0slotBoom\0"
    "slotAddNetArcgis\0slotRemvNetArcgis"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_OsgContainer[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    1,   55,    2, 0x0a /* Public */,
       5,    1,   58,    2, 0x0a /* Public */,
       6,    1,   61,    2, 0x0a /* Public */,
       7,    1,   64,    2, 0x0a /* Public */,
       8,    1,   67,    2, 0x0a /* Public */,
       9,    0,   70,    2, 0x0a /* Public */,
      10,    0,   71,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void OsgContainer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        OsgContainer *_t = static_cast<OsgContainer *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->startWork(); break;
        case 1: _t->slotSnow((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->slotRain((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->slotWu((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->slotFire((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->slotBoom((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->slotAddNetArcgis(); break;
        case 7: _t->slotRemvNetArcgis(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (OsgContainer::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&OsgContainer::startWork)) {
                *result = 0;
                return;
            }
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
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void OsgContainer::startWork()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
