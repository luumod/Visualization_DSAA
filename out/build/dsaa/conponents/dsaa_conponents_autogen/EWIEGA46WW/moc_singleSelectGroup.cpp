/****************************************************************************
** Meta object code from reading C++ file 'singleSelectGroup.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.2.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../../../dsaa/conponents/singleSelectGroup.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'singleSelectGroup.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.2.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_selectionItem_t {
    const uint offsetsAndSize[10];
    char stringdata0[44];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_selectionItem_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_selectionItem_t qt_meta_stringdata_selectionItem = {
    {
QT_MOC_LITERAL(0, 13), // "selectionItem"
QT_MOC_LITERAL(14, 8), // "selected"
QT_MOC_LITERAL(23, 0), // ""
QT_MOC_LITERAL(24, 14), // "selectionItem*"
QT_MOC_LITERAL(39, 4) // "item"

    },
    "selectionItem\0selected\0\0selectionItem*\0"
    "item"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_selectionItem[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   20,    2, 0x06,    1 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,

       0        // eod
};

void selectionItem::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<selectionItem *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->selected((*reinterpret_cast< std::add_pointer_t<selectionItem*>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< selectionItem* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (selectionItem::*)(selectionItem * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&selectionItem::selected)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject selectionItem::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_selectionItem.offsetsAndSize,
    qt_meta_data_selectionItem,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_selectionItem_t
, QtPrivate::TypeAndForceComplete<selectionItem, std::true_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<selectionItem *, std::false_type>



>,
    nullptr
} };


const QMetaObject *selectionItem::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *selectionItem::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_selectionItem.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int selectionItem::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void selectionItem::selected(selectionItem * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
struct qt_meta_stringdata_singleSelectGroup_t {
    const uint offsetsAndSize[16];
    char stringdata0[94];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_singleSelectGroup_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_singleSelectGroup_t qt_meta_stringdata_singleSelectGroup = {
    {
QT_MOC_LITERAL(0, 17), // "singleSelectGroup"
QT_MOC_LITERAL(18, 18), // "selectedItemChange"
QT_MOC_LITERAL(37, 0), // ""
QT_MOC_LITERAL(38, 8), // "selectID"
QT_MOC_LITERAL(47, 10), // "itemChange"
QT_MOC_LITERAL(58, 15), // "changeSelection"
QT_MOC_LITERAL(74, 14), // "selectionItem*"
QT_MOC_LITERAL(89, 4) // "item"

    },
    "singleSelectGroup\0selectedItemChange\0"
    "\0selectID\0itemChange\0changeSelection\0"
    "selectionItem*\0item"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_singleSelectGroup[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   32,    2, 0x06,    1 /* Public */,
       4,    0,   35,    2, 0x06,    3 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       5,    1,   36,    2, 0x08,    4 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 6,    7,

       0        // eod
};

void singleSelectGroup::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<singleSelectGroup *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->selectedItemChange((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 1: _t->itemChange(); break;
        case 2: _t->changeSelection((*reinterpret_cast< std::add_pointer_t<selectionItem*>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< selectionItem* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (singleSelectGroup::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&singleSelectGroup::selectedItemChange)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (singleSelectGroup::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&singleSelectGroup::itemChange)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject singleSelectGroup::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_singleSelectGroup.offsetsAndSize,
    qt_meta_data_singleSelectGroup,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_singleSelectGroup_t
, QtPrivate::TypeAndForceComplete<singleSelectGroup, std::true_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<selectionItem *, std::false_type>


>,
    nullptr
} };


const QMetaObject *singleSelectGroup::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *singleSelectGroup::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_singleSelectGroup.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int singleSelectGroup::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void singleSelectGroup::selectedItemChange(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void singleSelectGroup::itemChange()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
