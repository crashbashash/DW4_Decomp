#include "dw4/reflected.h"
/* matching construct: dummy-virtual class (22 slots) so arg0->v22() compiles to the retail vtable call; it carries no data. */
class beNDMWWindowSelectVTable { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void v22();
 };
extern "C" {
int beMessenger_AppendBool(int, int);
int beMessenger_AppendInt(int, int);
int beMessenger_AppendString(int, void *);
int beMessenger_AppendVec3(int, void *);
int beMessenger_DispatchSelected(int, void *);
int beMessenger_GetBool(int, int);
int beMessenger_GetInt(int, int);
int beMessenger_SelectReceivers(int, void *, int, int);
int beMessenger_SendNamed(int, void *, int, int, void *);
int beNDMWWindowSelect_CanRequestFO2TOP(beNDMWWindowSelectVTable *);
int beNDMWWindow_ClearQueuedText(beNDMWWindowSelectVTable *);
int beNDMWWindow_PlayQueuedModelClose(beNDMWWindowSelectVTable *);
int beNDMWWindow_PollCloseComplete(beNDMWWindowSelectVTable *);
extern int DAT_0051a918[4];
extern int DAT_0051a928[4];
extern int DAT_0051a938[4];
extern int DAT_0051a948[4];
extern int DAT_0051a958[4];
extern int DAT_0051a960[4];
void Gap__Bec__beNDMWWindowSelect__vfunc_21(beNDMWWindowSelectVTable *arg0);
}
void Gap__Bec__beNDMWWindowSelect__vfunc_21(beNDMWWindowSelectVTable *arg0) {
    /* matching construct: typed view of the dummy-virtual receiver; data is reached only through s. */
    beNDMWWindowSelect *s = (beNDMWWindowSelect *)arg0;
    float sp30[3];
    int i;
    igDataList *t;
    switch (s->_st0) {
    case 0:
        arg0->v22();
        beMessenger_SelectReceivers(s->_messenger, DAT_0051a918, s->_infoName, s->_playerNo);
        beMessenger_AppendInt(s->_messenger, s->_selectMax);
        beMessenger_AppendInt(s->_messenger, s->_startPoint);
        /* _offsetPos is an igVec3f (three floats); the reflected header declares the words as int. */
        sp30[0] = ((float *)s->_offsetPos)[0];
        sp30[1] = ((float *)s->_offsetPos)[1];
        sp30[2] = ((float *)s->_offsetPos)[2];
        beMessenger_AppendVec3(s->_messenger, sp30);
        if (s->_isNoCancel != 0) {
            beMessenger_AppendString(s->_messenger, DAT_0051a928);
        }
        t = *(igDataList **)&s->_decideList;
        if (t != 0) {
            i = 0;
            if (0 < t->_count) {
                do {
                    beMessenger_AppendBool(s->_messenger, ((unsigned char *)(((igDataList *)s->_decideList)->_data + i))[0] /* matching construct: int _data + i keeps retail addu operand order */);
                    i++;
                } while (i < ((igDataList *)s->_decideList)->_count);
            }
        }
        beMessenger_DispatchSelected(s->_messenger, DAT_0051a938);
        s->_st0 = s->_st0 + 1;
        s->_st3 = 0;
        s->_st2 = 0;
        s->_st1 = 0;
    case 1:
        beMessenger_SendNamed(s->_messenger, DAT_0051a918, s->_infoName, s->_playerNo, DAT_0051a948);
        ((beNDMWWindow *)s->_mother)->_retCode = beMessenger_GetInt(s->_messenger, 0);
        beMessenger_SendNamed(s->_messenger, DAT_0051a918, s->_infoName, s->_playerNo, DAT_0051a958);
        if ((beMessenger_GetBool(s->_messenger, 0) & 0xFF) == 0) {
            break;
        }
        s->_st0 = s->_st0 + 1;
        s->_st3 = 0;
        s->_st2 = 0;
        s->_st1 = 0;
    case 2:
        beNDMWWindow_PlayQueuedModelClose(arg0);
        beNDMWWindow_ClearQueuedText(arg0);
        s->_st0 = s->_st0 + 1;
        s->_st3 = 0;
        s->_st2 = 0;
        s->_st1 = 0;
    case 3:
        if (beNDMWWindow_PollCloseComplete(arg0) != 0) {
            s->_isRun = 0;
        }
        break;
    case 4:
        if (beNDMWWindowSelect_CanRequestFO2TOP(arg0) != 0) {
            beMessenger_SelectReceivers(s->_messenger, DAT_0051a918, s->_infoName, s->_playerNo);
            beMessenger_AppendInt(s->_messenger, s->_selectMax);
            t = *(igDataList **)&s->_decideList;
            if (t != 0) {
                i = 0;
                if (0 < t->_count) {
                    do {
                        beMessenger_AppendBool(s->_messenger, ((unsigned char *)(((igDataList *)s->_decideList)->_data + i))[0] /* matching construct: int _data + i keeps retail addu operand order */);
                        i++;
                    } while (i < ((igDataList *)s->_decideList)->_count);
                }
            }
            beMessenger_DispatchSelected(s->_messenger, DAT_0051a960);
            beMessenger_SendNamed(s->_messenger, DAT_0051a918, s->_infoName, s->_playerNo, DAT_0051a948);
            ((beNDMWWindow *)s->_mother)->_retCode = beMessenger_GetInt(s->_messenger, 0);
        }
        s->_st0 = 1;
        s->_st3 = 0;
        s->_st2 = 0;
        s->_st1 = 0;
        break;
    }
}
