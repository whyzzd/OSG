/****************************************************************************
** Meta object code from reading C++ file 'CPickHandler.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../CPickHandler.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CPickHandler.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_CPickHandler_t {
    QByteArrayData data[10];
    char stringdata0[97];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CPickHandler_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CPickHandler_t qt_meta_stringdata_CPickHandler = {
    {
QT_MOC_LITERAL(0, 0, 12), // "CPickHandler"
QT_MOC_LITERAL(1, 13, 17), // "signShowLonLatAlt"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 9), // "osg::Vec3"
QT_MOC_LITERAL(4, 42, 3), // "lla"
QT_MOC_LITERAL(5, 46, 13), // "signReDefault"
QT_MOC_LITERAL(6, 60, 16), // "slotGetDrawIndex"
QT_MOC_LITERAL(7, 77, 1), // "n"
QT_MOC_LITERAL(8, 79, 15), // "slotDrawLineWid"
QT_MOC_LITERAL(9, 95, 1) // "a"

    },
    "CPickHandler\0signShowLonLatAlt\0\0"
    "osg::Vec3\0lla\0signReDefault\0"
    "slotGetDrawIndex\0n\0slotDrawLineWid\0a"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CPickHandler[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x06 /* Public */,
       5,    0,   37,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    1,   38,    2, 0x0a /* Public */,
       8,    1,   41,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void, QMetaType::Float,    9,

       0        // eod
};

void CPickHandler::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CPickHandler *_t = static_cast<CPickHandler *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signShowLonLatAlt((*reinterpret_cast< const osg::Vec3(*)>(_a[1]))); break;
        case 1: _t->signReDefault(); break;
        case 2: _t->slotGetDrawIndex((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->slotDrawLineWid((*reinterpret_cast< float(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (CPickHandler::*_t)(const osg::Vec3 & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CPickHandler::signShowLonLatAlt)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (CPickHandler::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CPickHandler::signReDefault)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject CPickHandler::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_CPickHandler.data,
      qt_meta_data_CPickHandler,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *CPickHandler::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CPickHandler::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_CPickHandler.stringdata0))
        return static_cast<void*>(const_cast< CPickHandler*>(this));
    if (!strcmp(_clname, "osgGA::GUIEventHandler"))
        return static_cast< osgGA::GUIEventHandler*>(const_cast< CPickHandler*>(this));
    return QObject::qt_metacast(_clname);
}

int CPickHandler::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void CPickHandler::signShowLonLatAlt(const osg::Vec3 & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void CPickHandler::signReDefault()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
