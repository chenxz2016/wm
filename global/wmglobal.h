#ifndef WM_GLOBAL_H_
#define WM_GLOBAL_H_

#include <qglobal.h>

#if defined(WM_LIBRARY)
#    define WM_EXPORT Q_DECL_EXPORT
#    define WM_CORE_EXPORT Q_DECL_EXPORT
#else
#    define WM_EXPORT Q_DECL_IMPORT
#    define WM_CORE_EXPORT Q_DECL_IMPORT
#endif

namespace WM
{

enum WMUserStatus
{
    Offline,
    Online,
    Busy,
    Hide
};

enum WMLoginResult
{
    LoginSuccess,
    KeyReqSuccess,
    PacketError,
    IDError,
    PWDError,
    Timeout,
    WaitForVerify
};

enum WMCoreServiceRequestID
{
    CSLoginID = 0,      //WMP_PROTO_LOGIN_ID
    CSBeatHeartID,      //WMP_PROTO_BH_ID
    CSFileID,           //WMP_PROTO_FILE_ID
    CSMsgID,            //WMP_PROTO_MSG_ID
    CSUserID,           //WMP_PROTO_USER_ID
    CSVideoID,          //WMP_PROTO_VIDEO_ID
    CSVoiceID,          //WMP_PROTO_SOUND_ID
    CSGroupID,          //WMP_PROTO_GROUP_ID
    CSRegisterID,       //WMP_PROTO_REGISTER_ID
    CSSessionID         //WMP_PROTO_SESSION_ID
};

}

namespace WMAnimation
{

enum Direction
{
    LeftToRight,
    RightToLeft,
    TopToBottom,
    BottomToTop
};

}


#endif
