/****************************************************************************
** Meta object code from reading C++ file 'gamelobby.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Chess-cpp/Client/onlineGame/gamelobby.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'gamelobby.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_gameLobby_t {
    QByteArrayData data[29];
    char stringdata0[313];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_gameLobby_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_gameLobby_t qt_meta_stringdata_gameLobby = {
    {
QT_MOC_LITERAL(0, 0, 9), // "gameLobby"
QT_MOC_LITERAL(1, 10, 11), // "updateRooms"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 6), // "cJSON*"
QT_MOC_LITERAL(4, 30, 5), // "Lists"
QT_MOC_LITERAL(5, 36, 12), // "socketClosed"
QT_MOC_LITERAL(6, 49, 18), // "socketClosedfailed"
QT_MOC_LITERAL(7, 68, 11), // "TimeoutJoin"
QT_MOC_LITERAL(8, 80, 12), // "someoneLeave"
QT_MOC_LITERAL(9, 93, 8), // "ShowGame"
QT_MOC_LITERAL(10, 102, 9), // "PlayWhite"
QT_MOC_LITERAL(11, 112, 9), // "PlayBlack"
QT_MOC_LITERAL(12, 122, 6), // "moveTo"
QT_MOC_LITERAL(13, 129, 11), // "onlineMove*"
QT_MOC_LITERAL(14, 141, 4), // "Full"
QT_MOC_LITERAL(15, 146, 9), // "RoomClose"
QT_MOC_LITERAL(16, 156, 8), // "ListFull"
QT_MOC_LITERAL(17, 165, 15), // "createRoomsList"
QT_MOC_LITERAL(18, 181, 16), // "sendJointRequest"
QT_MOC_LITERAL(19, 198, 2), // "ID"
QT_MOC_LITERAL(20, 201, 11), // "ServerClose"
QT_MOC_LITERAL(21, 213, 10), // "SocketBugs"
QT_MOC_LITERAL(22, 224, 11), // "JoinTimeOut"
QT_MOC_LITERAL(23, 236, 5), // "Leave"
QT_MOC_LITERAL(24, 242, 12), // "List_is_full"
QT_MOC_LITERAL(25, 255, 16), // "This_Game_isFull"
QT_MOC_LITERAL(26, 272, 16), // "I_wannaPlayAgain"
QT_MOC_LITERAL(27, 289, 12), // "ReturnToMenu"
QT_MOC_LITERAL(28, 302, 10) // "CancelHost"

    },
    "gameLobby\0updateRooms\0\0cJSON*\0Lists\0"
    "socketClosed\0socketClosedfailed\0"
    "TimeoutJoin\0someoneLeave\0ShowGame\0"
    "PlayWhite\0PlayBlack\0moveTo\0onlineMove*\0"
    "Full\0RoomClose\0ListFull\0createRoomsList\0"
    "sendJointRequest\0ID\0ServerClose\0"
    "SocketBugs\0JoinTimeOut\0Leave\0List_is_full\0"
    "This_Game_isFull\0I_wannaPlayAgain\0"
    "ReturnToMenu\0CancelHost"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_gameLobby[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      23,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      12,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  129,    2, 0x06 /* Public */,
       5,    0,  132,    2, 0x06 /* Public */,
       6,    0,  133,    2, 0x06 /* Public */,
       7,    0,  134,    2, 0x06 /* Public */,
       8,    0,  135,    2, 0x06 /* Public */,
       9,    0,  136,    2, 0x06 /* Public */,
      10,    0,  137,    2, 0x06 /* Public */,
      11,    0,  138,    2, 0x06 /* Public */,
      12,    1,  139,    2, 0x06 /* Public */,
      14,    0,  142,    2, 0x06 /* Public */,
      15,    0,  143,    2, 0x06 /* Public */,
      16,    0,  144,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      17,    1,  145,    2, 0x0a /* Public */,
      18,    1,  148,    2, 0x0a /* Public */,
      20,    0,  151,    2, 0x0a /* Public */,
      21,    0,  152,    2, 0x0a /* Public */,
      22,    0,  153,    2, 0x0a /* Public */,
      23,    0,  154,    2, 0x0a /* Public */,
      24,    0,  155,    2, 0x0a /* Public */,
      25,    0,  156,    2, 0x0a /* Public */,
      26,    0,  157,    2, 0x0a /* Public */,
      27,    0,  158,    2, 0x0a /* Public */,
      28,    0,  159,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 13,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, QMetaType::Int,   19,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void gameLobby::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        gameLobby *_t = static_cast<gameLobby *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->updateRooms((*reinterpret_cast< cJSON*(*)>(_a[1]))); break;
        case 1: _t->socketClosed(); break;
        case 2: _t->socketClosedfailed(); break;
        case 3: _t->TimeoutJoin(); break;
        case 4: _t->someoneLeave(); break;
        case 5: _t->ShowGame(); break;
        case 6: _t->PlayWhite(); break;
        case 7: _t->PlayBlack(); break;
        case 8: _t->moveTo((*reinterpret_cast< onlineMove*(*)>(_a[1]))); break;
        case 9: _t->Full(); break;
        case 10: _t->RoomClose(); break;
        case 11: _t->ListFull(); break;
        case 12: _t->createRoomsList((*reinterpret_cast< cJSON*(*)>(_a[1]))); break;
        case 13: _t->sendJointRequest((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 14: _t->ServerClose(); break;
        case 15: _t->SocketBugs(); break;
        case 16: _t->JoinTimeOut(); break;
        case 17: _t->Leave(); break;
        case 18: _t->List_is_full(); break;
        case 19: _t->This_Game_isFull(); break;
        case 20: _t->I_wannaPlayAgain(); break;
        case 21: _t->ReturnToMenu(); break;
        case 22: _t->CancelHost(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (gameLobby::*)(cJSON * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&gameLobby::updateRooms)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (gameLobby::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&gameLobby::socketClosed)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (gameLobby::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&gameLobby::socketClosedfailed)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (gameLobby::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&gameLobby::TimeoutJoin)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (gameLobby::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&gameLobby::someoneLeave)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (gameLobby::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&gameLobby::ShowGame)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (gameLobby::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&gameLobby::PlayWhite)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (gameLobby::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&gameLobby::PlayBlack)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (gameLobby::*)(onlineMove * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&gameLobby::moveTo)) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (gameLobby::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&gameLobby::Full)) {
                *result = 9;
                return;
            }
        }
        {
            using _t = void (gameLobby::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&gameLobby::RoomClose)) {
                *result = 10;
                return;
            }
        }
        {
            using _t = void (gameLobby::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&gameLobby::ListFull)) {
                *result = 11;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject gameLobby::staticMetaObject = {
    { &QGraphicsView::staticMetaObject, qt_meta_stringdata_gameLobby.data,
      qt_meta_data_gameLobby,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *gameLobby::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *gameLobby::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_gameLobby.stringdata0))
        return static_cast<void*>(this);
    return QGraphicsView::qt_metacast(_clname);
}

int gameLobby::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 23)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 23;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 23)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 23;
    }
    return _id;
}

// SIGNAL 0
void gameLobby::updateRooms(cJSON * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void gameLobby::socketClosed()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void gameLobby::socketClosedfailed()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void gameLobby::TimeoutJoin()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void gameLobby::someoneLeave()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void gameLobby::ShowGame()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void gameLobby::PlayWhite()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}

// SIGNAL 7
void gameLobby::PlayBlack()
{
    QMetaObject::activate(this, &staticMetaObject, 7, nullptr);
}

// SIGNAL 8
void gameLobby::moveTo(onlineMove * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void gameLobby::Full()
{
    QMetaObject::activate(this, &staticMetaObject, 9, nullptr);
}

// SIGNAL 10
void gameLobby::RoomClose()
{
    QMetaObject::activate(this, &staticMetaObject, 10, nullptr);
}

// SIGNAL 11
void gameLobby::ListFull()
{
    QMetaObject::activate(this, &staticMetaObject, 11, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
