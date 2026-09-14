/****************************************************************************
** Meta object code from reading C++ file 'weatherObj.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.19)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../resources/models/weatherApp/qmlFiles/weatherObj.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'weatherObj.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.19. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_weatherObj_t {
    QByteArrayData data[24];
    char stringdata0[242];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_weatherObj_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_weatherObj_t qt_meta_stringdata_weatherObj = {
    {
QT_MOC_LITERAL(0, 0, 10), // "weatherObj"
QT_MOC_LITERAL(1, 11, 12), // "resultsReady"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 8), // "formated"
QT_MOC_LITERAL(4, 34, 14), // "initialresults"
QT_MOC_LITERAL(5, 49, 7), // "results"
QT_MOC_LITERAL(6, 57, 23), // "weatherConditionChanged"
QT_MOC_LITERAL(7, 81, 14), // "getTimeAtIndex"
QT_MOC_LITERAL(8, 96, 5), // "index"
QT_MOC_LITERAL(9, 102, 14), // "getTempAtIndex"
QT_MOC_LITERAL(10, 117, 10), // "returnCity"
QT_MOC_LITERAL(11, 128, 10), // "store_city"
QT_MOC_LITERAL(12, 139, 4), // "city"
QT_MOC_LITERAL(13, 144, 14), // "terminalOutput"
QT_MOC_LITERAL(14, 159, 16), // "weatherCondition"
QT_MOC_LITERAL(15, 176, 14), // "currentWeather"
QT_MOC_LITERAL(16, 191, 6), // "STORMY"
QT_MOC_LITERAL(17, 198, 7), // "DRIZZLY"
QT_MOC_LITERAL(18, 206, 5), // "RAINY"
QT_MOC_LITERAL(19, 212, 5), // "SNOWY"
QT_MOC_LITERAL(20, 218, 5), // "MISTY"
QT_MOC_LITERAL(21, 224, 6), // "CLOUDY"
QT_MOC_LITERAL(22, 231, 5), // "CLEAR"
QT_MOC_LITERAL(23, 237, 4) // "NONE"

    },
    "weatherObj\0resultsReady\0\0formated\0"
    "initialresults\0results\0weatherConditionChanged\0"
    "getTimeAtIndex\0index\0getTempAtIndex\0"
    "returnCity\0store_city\0city\0terminalOutput\0"
    "weatherCondition\0currentWeather\0STORMY\0"
    "DRIZZLY\0RAINY\0SNOWY\0MISTY\0CLOUDY\0CLEAR\0"
    "NONE"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_weatherObj[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       1,   72, // properties
       1,   76, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   54,    2, 0x06 /* Public */,
       4,    1,   57,    2, 0x06 /* Public */,
       6,    0,   60,    2, 0x06 /* Public */,

 // methods: name, argc, parameters, tag, flags
       7,    1,   61,    2, 0x02 /* Public */,
       9,    1,   64,    2, 0x02 /* Public */,
      10,    0,   67,    2, 0x02 /* Public */,
      11,    1,   68,    2, 0x02 /* Public */,
      13,    0,   71,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void,

 // methods: parameters
    QMetaType::QString, QMetaType::Int,    8,
    QMetaType::QString, QMetaType::Int,    8,
    QMetaType::QString,
    QMetaType::Void, QMetaType::QString,   12,
    QMetaType::Void,

 // properties: name, type, flags
      14, 0x80000000 | 15, 0x00495009,

 // properties: notify_signal_id
       2,

 // enums: name, alias, flags, count, data
      15,   15, 0x0,    8,   81,

 // enum data: key, value
      16, uint(weatherObj::STORMY),
      17, uint(weatherObj::DRIZZLY),
      18, uint(weatherObj::RAINY),
      19, uint(weatherObj::SNOWY),
      20, uint(weatherObj::MISTY),
      21, uint(weatherObj::CLOUDY),
      22, uint(weatherObj::CLEAR),
      23, uint(weatherObj::NONE),

       0        // eod
};

void weatherObj::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<weatherObj *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->resultsReady((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->initialresults((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->weatherConditionChanged(); break;
        case 3: { QString _r = _t->getTimeAtIndex((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 4: { QString _r = _t->getTempAtIndex((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 5: { QString _r = _t->returnCity();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 6: _t->store_city((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 7: _t->terminalOutput(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (weatherObj::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&weatherObj::resultsReady)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (weatherObj::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&weatherObj::initialresults)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (weatherObj::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&weatherObj::weatherConditionChanged)) {
                *result = 2;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<weatherObj *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< currentWeather*>(_v) = _t->weatherCondition(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject weatherObj::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_weatherObj.data,
    qt_meta_data_weatherObj,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *weatherObj::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *weatherObj::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_weatherObj.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int weatherObj::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 1;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void weatherObj::resultsReady(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void weatherObj::initialresults(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void weatherObj::weatherConditionChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
