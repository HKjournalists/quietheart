/****************************************************************************
** Meta object code from reading C++ file 'inputwidget.h'
**
** Created: Wed Oct 21 11:10:43 2009
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "inputwidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'inputwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_InputWidget[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

       0        // eod
};

static const char qt_meta_stringdata_InputWidget[] = {
    "InputWidget\0"
};

const QMetaObject InputWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_InputWidget,
      qt_meta_data_InputWidget, 0 }
};

const QMetaObject *InputWidget::metaObject() const
{
    return &staticMetaObject;
}

void *InputWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_InputWidget))
        return static_cast<void*>(const_cast< InputWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int InputWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
QT_END_MOC_NAMESPACE
