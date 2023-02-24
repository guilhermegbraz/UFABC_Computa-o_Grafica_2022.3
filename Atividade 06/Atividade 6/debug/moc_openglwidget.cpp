/****************************************************************************
** Meta object code from reading C++ file 'openglwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../openglwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'openglwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_OpenGLWidget_t {
    QByteArrayData data[15];
    char stringdata0[248];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_OpenGLWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_OpenGLWidget_t qt_meta_stringdata_OpenGLWidget = {
    {
QT_MOC_LITERAL(0, 0, 12), // "OpenGLWidget"
QT_MOC_LITERAL(1, 13, 16), // "statusBarMessage"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 18), // "enableComboShaders"
QT_MOC_LITERAL(4, 50, 21), // "enableSliderHighlight"
QT_MOC_LITERAL(5, 72, 15), // "enableToonCombo"
QT_MOC_LITERAL(6, 88, 20), // "enableSliderRotation"
QT_MOC_LITERAL(7, 109, 14), // "toggleDarkMode"
QT_MOC_LITERAL(8, 124, 15), // "toggleWireframe"
QT_MOC_LITERAL(9, 140, 18), // "toggleOrthographic"
QT_MOC_LITERAL(10, 159, 18), // "showFileOpenDialog"
QT_MOC_LITERAL(11, 178, 12), // "changeShader"
QT_MOC_LITERAL(12, 191, 20), // "changeHighlightModel"
QT_MOC_LITERAL(13, 212, 15), // "changeToonColor"
QT_MOC_LITERAL(14, 228, 19) // "changeSpeedRotation"

    },
    "OpenGLWidget\0statusBarMessage\0\0"
    "enableComboShaders\0enableSliderHighlight\0"
    "enableToonCombo\0enableSliderRotation\0"
    "toggleDarkMode\0toggleWireframe\0"
    "toggleOrthographic\0showFileOpenDialog\0"
    "changeShader\0changeHighlightModel\0"
    "changeToonColor\0changeSpeedRotation"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_OpenGLWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   79,    2, 0x06 /* Public */,
       3,    1,   82,    2, 0x06 /* Public */,
       4,    1,   85,    2, 0x06 /* Public */,
       5,    1,   88,    2, 0x06 /* Public */,
       6,    1,   91,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    1,   94,    2, 0x0a /* Public */,
       8,    1,   97,    2, 0x0a /* Public */,
       9,    1,  100,    2, 0x0a /* Public */,
      10,    0,  103,    2, 0x0a /* Public */,
      11,    1,  104,    2, 0x0a /* Public */,
      12,    1,  107,    2, 0x0a /* Public */,
      13,    1,  110,    2, 0x0a /* Public */,
      14,    1,  113,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,

       0        // eod
};

void OpenGLWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<OpenGLWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->statusBarMessage((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->enableComboShaders((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->enableSliderHighlight((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->enableToonCombo((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: _t->enableSliderRotation((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: _t->toggleDarkMode((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: _t->toggleWireframe((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: _t->toggleOrthographic((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: _t->showFileOpenDialog(); break;
        case 9: _t->changeShader((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->changeHighlightModel((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->changeToonColor((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 12: _t->changeSpeedRotation((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (OpenGLWidget::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&OpenGLWidget::statusBarMessage)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (OpenGLWidget::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&OpenGLWidget::enableComboShaders)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (OpenGLWidget::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&OpenGLWidget::enableSliderHighlight)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (OpenGLWidget::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&OpenGLWidget::enableToonCombo)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (OpenGLWidget::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&OpenGLWidget::enableSliderRotation)) {
                *result = 4;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject OpenGLWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<QOpenGLWidget::staticMetaObject>(),
    qt_meta_stringdata_OpenGLWidget.data,
    qt_meta_data_OpenGLWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *OpenGLWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *OpenGLWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_OpenGLWidget.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "QOpenGLFunctions_4_0_Core"))
        return static_cast< QOpenGLFunctions_4_0_Core*>(this);
    return QOpenGLWidget::qt_metacast(_clname);
}

int OpenGLWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QOpenGLWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void OpenGLWidget::statusBarMessage(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void OpenGLWidget::enableComboShaders(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void OpenGLWidget::enableSliderHighlight(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void OpenGLWidget::enableToonCombo(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void OpenGLWidget::enableSliderRotation(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
