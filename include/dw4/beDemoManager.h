#ifndef DW4_BEDEMOMANAGER_H
#define DW4_BEDEMOMANAGER_H
#include "dw4/reflected.h"

/* What a demo-manager keep-message does when the demo plays (beDemoKeepMes._kind). */
enum DemoKeepMesKind {
    DEMO_MES_SEND,             /* send the message, now or after _sendTime */
    DEMO_MES_SEND_UNTIL_TRUE,  /* send it again every update until the bool reply is true */
    DEMO_MES_SEND_UNTIL_FALSE, /* send it again every update until the bool reply is false */
    DEMO_MES_SWITCH,           /* send it and jump to the case matching the int reply */
    DEMO_MES_CASE,             /* a switch branch labelled _ramNo; reached in order, it skips to the end */
    DEMO_MES_SWITCH_END,       /* closes a switch */
    DEMO_MES_MSGBOX,           /* message box text; playing does nothing with it */
    DEMO_MES_LUA               /* run the Lua chunk named by _mesParam */
};

extern "C" {
void beDemoManager_AddKeepMes(beDemoManager *self, int kind, const char *group, const char *infoName, int ramNo, const char *message, const char *param, long long sendTime);
void beDemoManager_SwitchSD(beDemoManager *self, const char *group, const char *infoName, int ramNo, const char *message, const char *param);
void beDemoManager_SwitchEnd(beDemoManager *self);
void beDemoManager_Case(beDemoManager *self, int ramNo);
void beDemoManager_SetLua(beDemoManager *self, const char *chunk);
void beDemoManager_MsgBox(beDemoManager *self, const char *text, int ramNo);
void beDemoManager_Run(beDemoManager *self);
}

#endif
