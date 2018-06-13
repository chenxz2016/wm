#include "remotectrl.h"

#ifdef Q_OS_WIN
#include <QMap>
#include <windows.h>
#include <minwindef.h>
#include <WinUser.h>
#pragma comment (lib,"user32.lib")
const QMap<int,char> keyBoardMap={
    {Qt::Key_Left,0x25},
    {Qt::Key_Up,0x26},
    {Qt::Key_Right,0x27},
    {Qt::Key_Down,0x28},
    {Qt::Key_Backspace,0x08},
    {Qt::Key_Tab,0x09},
    {Qt::Key_Clear,0x0C},
    {Qt::Key_Return,0x0D},
    {Qt::Key_Enter,0x0D},
    {Qt::Key_Shift,0x10},
    {Qt::Key_Control,0x11},
    {Qt::Key_Alt,0x12},
    {Qt::Key_Pause,0x13},
    {Qt::Key_CapsLock,0x14},
    {Qt::Key_Escape,0x1B},
    {Qt::Key_Space,0x20},
    {Qt::Key_PageUp,0x21},
    {Qt::Key_PageDown,0x22},
    {Qt::Key_End,0x23},
    {Qt::Key_Home,0x24},
    {Qt::Key_Select,0x29},
    {Qt::Key_Print,0x2A},
    {Qt::Key_Execute,0x2B},
    {Qt::Key_Printer,0x2C},
    {Qt::Key_Insert,0x2D},
    {Qt::Key_Delete,0x2E},
    {Qt::Key_Help,0x2F},
    {Qt::Key_0,0x30},
    {Qt::Key_ParenRight,0x30}, // )
    {Qt::Key_1,0x31},
    {Qt::Key_Exclam,0x31}, // !
    {Qt::Key_2,0x32},
    {Qt::Key_At,0x32}, // @
    {Qt::Key_3,0x33},
    {Qt::Key_NumberSign,0x33}, // #
    {Qt::Key_4,0x34},
    {Qt::Key_Dollar,0x34}, // $
    {Qt::Key_5,0x35},
    {Qt::Key_Percent,0x35}, // %
    {Qt::Key_6,0x36},
    {Qt::Key_AsciiCircum,0x36}, // ^
    {Qt::Key_7,0x37},
    {Qt::Key_Ampersand,0x37}, // &
    {Qt::Key_8,0x38},
    {Qt::Key_Asterisk,0x38}, // *
    {Qt::Key_9,0x39},
    {Qt::Key_ParenLeft,0x39}, // (
    {Qt::Key_A,0x41},
    {Qt::Key_B,0x42},
    {Qt::Key_C,0x43},
    {Qt::Key_D,0x44},
    {Qt::Key_E,0x45},
    {Qt::Key_F,0x46},
    {Qt::Key_G,0x47},
    {Qt::Key_H,0x48},
    {Qt::Key_I,0x49},
    {Qt::Key_J,0x4A},
    {Qt::Key_K,0x4B},
    {Qt::Key_L,0x4C},
    {Qt::Key_M,0x4D},
    {Qt::Key_N,0x4E},
    {Qt::Key_O,0x4F},
    {Qt::Key_P,0x50},
    {Qt::Key_Q,0x51},
    {Qt::Key_R,0x52},
    {Qt::Key_S,0x53},
    {Qt::Key_T,0x54},
    {Qt::Key_U,0x55},
    {Qt::Key_V,0x56},
    {Qt::Key_W,0x57},
    {Qt::Key_X,0x58},
    {Qt::Key_Y,0x59},
    {Qt::Key_Z,0x5A},
    {Qt::Key_multiply,0x6A},
    {Qt::Key_F1,0x70},
    {Qt::Key_F2,0x71},
    {Qt::Key_F3,0x72},
    {Qt::Key_F4,0x73},
    {Qt::Key_F5,0x74},
    {Qt::Key_F6,0x75},
    {Qt::Key_F7,0x76},
    {Qt::Key_F8,0x77},
    {Qt::Key_F9,0x78},
    {Qt::Key_F10,0x79},
    {Qt::Key_F11,0x7A},
    {Qt::Key_F12,0x7B},
    {Qt::Key_F13,0x7C},
    {Qt::Key_F14,0x7D},
    {Qt::Key_F15,0x7E},
    {Qt::Key_F16,0x7F},
    {Qt::Key_F17,0x80},
    {Qt::Key_F18,0x81},
    {Qt::Key_F19,0x82},
    {Qt::Key_F20,0x83},
    {Qt::Key_F21,0x84},
    {Qt::Key_F22,0x85},
    {Qt::Key_F23,0x86},
    {Qt::Key_F24,0x87},
    {Qt::Key_NumLock,0x90},
    {Qt::Key_ScrollLock,0x91},
    {Qt::Key_VolumeDown,0xAE},
    {Qt::Key_VolumeUp,0xAF},
    {Qt::Key_VolumeMute,0xAD},
    {Qt::Key_MediaStop,0xB2},
    {Qt::Key_MediaPlay,0xB3},
    {Qt::Key_Plus,0xBB}, // +
    {Qt::Key_Minus,0xBD}, // -
    {Qt::Key_Underscore,0xBD}, // _
    {Qt::Key_Equal,0xBB}, // =
    {Qt::Key_Semicolon,0xBA}, // ;
    {Qt::Key_Colon,0xBA}, // :
    {Qt::Key_Comma,0xBC}, // ,
    {Qt::Key_Less,0xBC}, // <
    {Qt::Key_Period,0xBE}, // .
    {Qt::Key_Greater,0xBE}, // >
    {Qt::Key_Slash,0xBF},  // /
    {Qt::Key_Question,0xBF}, // ?
    {Qt::Key_BracketLeft,0xDB}, // [
    {Qt::Key_BraceLeft,0xDB}, // {
    {Qt::Key_BracketRight,0xDD}, // ]
    {Qt::Key_BraceRight,0xDD}, // }
    {Qt::Key_Bar,0xDC}, // |
    {Qt::Key_Backslash,0xDC}, //
    {Qt::Key_Apostrophe,0xDE}, //
    {Qt::Key_QuoteDbl,0xDE}, // "
    {Qt::Key_QuoteLeft,0xC0}, // `
    {Qt::Key_AsciiTilde,0xC0}, // ~
};

#elif defined(Q_OS_UNIX)
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <linux/input.h>
#include <linux/uinput.h>
#include <stdio.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#define MOUSE_LEFT_BUTTON       BTN_LEFT
#define MOUSE_RIGHT_BUTTON      BTN_RIGHT
#define MOUSE_MIDDLE_BUTTON     BTN_MIDDLE
#elif defined(Q_OS_OSX)

#endif


static void ctrl_key(int fd, int code,int kval)
{
#ifdef Q_OS_WIN
    Q_UNUSED(fd)
    Q_UNUSED(code)
    Q_UNUSED(kval)
#elif defined(Q_OS_UNIX)
    struct input_event event;
    event.type = EV_KEY;
    event.value = kval;
    event.code = code;
    gettimeofday(&event.time, 0},
    write(fd, &event, sizeof(event));
    event.type = EV_SYN;
    event.code = SYN_REPORT;
    event.value = 0;
    write(fd, &event, sizeof(event));
#elif defined(Q_OS_OSX)

#endif


}

static void ctrl_mouse_pos(int fd,int x,int y)
{
#ifdef Q_OS_WIN
    Q_UNUSED(fd)
    SetCursorPos(x,y);
#elif defined(Q_OS_UNIX)
    struct input_event event;
    memset(&event, 0, sizeof(event));
    gettimeofday(&event.time, NULL);
    event.type = EV_REL;
    event.code = REL_X;
    event.value = x;
    write(fd, &event, sizeof(event));
    event.type = EV_REL;
    event.code = REL_Y;
    event.value = y;
    write(fd, &event, sizeof(event));
    event.type = EV_SYN;
    event.code = SYN_REPORT;
    event.value = 0;
    write(fd, &event, sizeof(event));

#elif defined(Q_OS_OSX)

#endif
}

static void ctrl_mouse_wheel(int fd,int delta)
{
#ifdef Q_OS_WIN
    Q_UNUSED(fd)
    Q_UNUSED(delta)
#elif defined(Q_OS_UNIX)
    struct input_event event;
    memset(&event, 0, sizeof(event));
    gettimeofday(&event.time, NULL);
    event.type = REL_WHEEL;
    event.code = REL_X;
    event.value = delta;
    write(fd, &event, sizeof(event));

    event.type = EV_SYN;
    event.code = SYN_REPORT;
    event.value = 0;
    write(fd, &event, sizeof(event));
#elif defined(Q_OS_OSX)

#endif
}

class RemoteCtrlPrivate
{
public:
    RemoteCtrlPrivate()
#if defined(Q_OS_UNIX)
        :mouseHandle(0)
        ,keyHandle(0)
#endif
    {}
    ~RemoteCtrlPrivate()
    {
#if defined(Q_OS_UNIX)
        close(mouseHandle);
        close(keyHandle);
#endif
    }
#if defined(Q_OS_UNIX)
    int mouseHandle;
    int keyHandle;
#endif
};

RemoteCtrl::RemoteCtrl(const QString &host)
    :h(host)
    ,p_d(new RemoteCtrlPrivate)
{
#if defined(Q_OS_UNIX)
    p_d->keyHandle = open("/dev/input/event1", O_RDWR);
    if(p_d->keyHandle <= 0)
    {
        qWarning() << "Get Key Failed.";
    }
    p_d->mouseHandle = open("/dev/input/event2", O_RDWR);
    if(p_d->mouseHandle <= 0)
    {
        qWarning() << "Get Mouse Failed.";
    }
#endif
}

RemoteCtrl::~RemoteCtrl()
{
    delete p_d;
}

void RemoteCtrl::setMousePos(const QPoint &pos)
{
#ifdef Q_OS_WIN
    ctrl_mouse_pos(0,pos.x(),pos.y());
#elif defined(Q_OS_UNIX)
    if(p_d->mouseHandle<=0)
    {
        qWarning() << "MouseCtrl: mouse handle is invalid.";
        return ;
    }
    ctrl_mouse_pos(p_d->mouseHandle,pos.x(),pos.y());
#elif defined(Q_OS_OSX)

#endif
}

void RemoteCtrl::setMousePress(Qt::MouseButton button)
{
#ifdef Q_OS_WIN
    switch(button)
    {
    case Qt::LeftButton:
        mouse_event(MOUSEEVENTF_LEFTDOWN,0,0,0,0);
        break;
    case Qt::RightButton:
        mouse_event(MOUSEEVENTF_RIGHTDOWN,0,0,0,0);
        break;
    case Qt::MiddleButton:
        mouse_event(MOUSEEVENTF_MIDDLEDOWN,0,0,0,0);
        break;
    default:
        break;
    }
#elif defined(Q_OS_UNIX)
    if(p_d->keyHandle<=0)
    {
        qWarning() << "RemoteCtrl: key handle is invalid.";
        return ;
    }
    int code;
    switch(button)
    {
    case Qt::LeftButton:
        code = BTN_LEFT;
        break;
    case Qt::RightButton:
        code = BTN_RIGHT;
        break;
    case Qt::MiddleButton:
        code = BTN_MIDDLE;
        break;
    default:
        break;
    }
    ctrl_key(p_d->keyHandle,code,1);
#elif defined(Q_OS_OSX)

#endif
}

void RemoteCtrl::setMouseRelease(Qt::MouseButton button)
{
#ifdef Q_OS_WIN
    switch(button)
    {
    case Qt::LeftButton:
        mouse_event(MOUSEEVENTF_LEFTUP,0,0,0,0);
        break;
    case Qt::RightButton:
        mouse_event(MOUSEEVENTF_RIGHTUP,0,0,0,0);
        break;
    case Qt::MiddleButton:
        mouse_event(MOUSEEVENTF_MIDDLEUP,0,0,0,0);
        break;
    default:
        break;
    }
#elif defined(Q_OS_UNIX)
    if(p_d->keyHandle<=0)
    {
        qWarning() << "RemoteCtrl: key handle is invalid.";
        return ;
    }
    int code;
    switch(button)
    {
    case Qt::LeftButton:
        code = BTN_LEFT;
        break;
    case Qt::RightButton:
        code = BTN_RIGHT;
        break;
    case Qt::MiddleButton:
        code = BTN_MIDDLE;
        break;
    default:
        break;
    }
    ctrl_key(p_d->keyHandle,code,0);
#elif defined(Q_OS_OSX)

#endif
}

void RemoteCtrl::setMouseWheeled(int delta)
{
#ifdef Q_OS_WIN
    mouse_event(MOUSEEVENTF_WHEEL,0,0,0,delta);
#elif defined(Q_OS_UNIX)

    if(p_d->mouseHandle<=0)
    {
        qWarning() << "RemoteCtrl: mouse handle is invalid.";
        return ;
    }

    ctrl_mouse_wheel(p_d->keyHandle,delta);
    ctrl_key(p_d->keyHandle,code,0);
#elif defined(Q_OS_OSX)

#endif
}

void RemoteCtrl::setKeyboardPress(int key)
{
#ifdef Q_OS_WIN
    BYTE vk = keyBoardMap[key];
    if(!vk)
        return ;

    keybd_event(vk,0,0,0);
#elif defined(Q_OS_UNIX)
    if(p_d->keyHandle<=0)
    {
        qWarning() << "RemoteCtrl: key handle is invalid.";
        return ;
    }

    ctrl_key(p_d->keyHandle,key,1);
#elif defined(Q_OS_OSX)

#endif
}

void RemoteCtrl::setKeyboardRelease(int key)
{
#ifdef Q_OS_WIN
    BYTE vk = keyBoardMap[key];
    if(!vk)
        return ;

    keybd_event(vk,0,KEYEVENTF_KEYUP,0);
#elif defined(Q_OS_UNIX)
    if(p_d->keyHandle<=0)
    {
        qWarning() << "RemoteCtrl: key handle is invalid.";
        return ;
    }
    ctrl_key(p_d->keyHandle,key,0);
#elif defined(Q_OS_OSX)

#endif
}
