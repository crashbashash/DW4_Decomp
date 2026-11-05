/* 0x003def80 - NameSel update: one step of the name-entry state machine (_st0 selects the phase, _st1 the step inside it).
 * Phases: 0 open the windows, 1 typing (D-pad moves the cursor, Cross enters, Circle erases, START leaves), 2 close,
 * 3 question (_isQuestion until _isAnswer), 4 leave early, 5 shut every window and set _isEnd. Returns _isEnd.
 * The receiver is the reflected beNDMWLoadIntf2NameSel (288 bytes registered); reflection lists its fields up to +100 and
 * the per-cell save area below is the unlisted tail of the same object (+104..), so NameSelRam is that tail laid over it. */
#include "dw4/reflected.h"
/* The retail unit was C++ with exceptions on (it keeps an exception index record);
 * the code is C, so the whole unit keeps C linkage. */
extern "C" {
typedef struct Vec3f { float x, y, z; } Vec3f;
typedef struct NameSelSave { int tate, yoko, cur; } NameSelSave;
typedef struct NameSelTail {
    char _reflected[104];   /* the reflected fields (+0..+100), reached through NS */
    NameSelSave save[8];    /* +104 */
    int mode[9];            /* +200 */
    unsigned short name[9]; /* +236 */
} NameSelTail;
typedef union NameSelRam {
    beNDMWLoadIntf2NameSel n;
    NameSelTail t;
} NameSelRam;
typedef struct NameRow { const char *name; int a, b; } NameRow;
typedef struct CharRow { int mod; unsigned short v[32]; } CharRow;
extern NameRow DAT_004cec74[];
extern CharRow DAT_004cc860[];
extern char DAT_00516ca8[], DAT_00516cd0[], DAT_00516d30[], DAT_00516d40[], DAT_00516dd8[];
extern char DAT_00516f50[], DAT_00516f60[], DAT_00516f70[], DAT_00516f80[], DAT_00516f98[], DAT_00516fb0[], DAT_00516fd0[];
extern char DAT_00516fe8[], DAT_00516ff8[], DAT_00517008[], DAT_00517018[], DAT_00517028[], DAT_00517030[], DAT_00517040[];
extern char DAT_00517050[], DAT_00517060[], DAT_00517070[];
bePadData *bePadManager_GetPadForPlayer(int, int);
void beNDMWLoadIntf2ComMdlCtrl__StartAt(beNDMWLoadIntf2ComMdlCtrl *, int, const char *, const char *, Vec3f *, int);
void beNDMWLoadIntf2ComMdlCtrl__Play(beNDMWLoadIntf2ComMdlCtrl *, int, const char *, const char *, int);
void beNDMWLoadIntf2ComMdlCtrl__Close(beNDMWLoadIntf2ComMdlCtrl *, int, const char *, const char *, int);
unsigned char beNDMWLoadIntf2ComMdlCtrl__IsOpenQueueEmpty(beNDMWLoadIntf2ComMdlCtrl *, unsigned char, unsigned char, int);
unsigned char beNDMWLoadIntf2ComMdlCtrl__IsCloseQueueEmpty(beNDMWLoadIntf2ComMdlCtrl *, unsigned char, unsigned char, int);
void sprintf(char *, const char *, ...);
void FUN_003de480(NameSelRam *, int);
void FUN_003de7a0(NameSelRam *, int);
void FUN_003de990(NameSelRam *, int);
#define NS (s->n)
#define CM ((beNDMWLoadIntf2ComMdlCtrl *)NS._comMdlCtrl)
#define POS(v) { Vec3f *u = (Vec3f *)&CM->_pos; v.x = u->x; v.y = u->y; v.z = u->z; }
#define DRAWPOS(v, nm, md, fl) POS(v) beNDMWLoadIntf2ComMdlCtrl__StartAt(CM, NS._ramNo, nm, md, &v, fl);
#define LANG(A, B) switch (NS._langID) { case 0: A; break; default: case 1: B; break; }
#define LANGDRAW(b, fl) LANG(beNDMWLoadIntf2ComMdlCtrl__Play(CM, NS._ramNo, DAT_00516ff8, b, fl), beNDMWLoadIntf2ComMdlCtrl__Play(CM, NS._ramNo, DAT_00517008, b, fl))
#define LANGDRAW0(b, fl) LANG(beNDMWLoadIntf2ComMdlCtrl__Close(CM, NS._ramNo, DAT_00516ff8, b, fl), beNDMWLoadIntf2ComMdlCtrl__Close(CM, NS._ramNo, DAT_00517008, b, fl))
#define SETCH s->t.name[NS._nameCurPos] = DAT_004cc860[NS._tatePoint].v[(NS._yokoPoint + NS._yokoCurPos) % DAT_004cc860[NS._tatePoint].mod];
#define NEXT NS._st1++; NS._st3 = 0; NS._st2 = 0;
unsigned char beNDMWLoadIntf2NameSel__Update(NameSelRam *s, int arg1) {
    bePadData *pad;
    unsigned char up, down, left, right;
    int trigger, edge, repeat;
    unsigned char upTmp;
    Vec3f pos0, pos1, pos2, pos3, pos4, pos5, pos6, pos7, pos8, pos9;
    char buf0[80], buf1[80], buf2[80], buf3[80], buf4[80], buf5[80], buf6[80], buf7[80], buf8[80], buf9[80], buf10[80], buf11[80], buf12[80], buf13[80], buf14[80], buf15[80];
    if (NS._isEnd == 1) return 1;
    trigger = 0; up = 0; down = 0; left = 0; right = 0;
    if ((arg1 & 0xFF) == 1) {
        pad = bePadManager_GetPadForPlayer(NS._padManager, NS._ramNo);
        trigger = pad->_trigger;
        repeat = pad->_repeat;
        edge = pad->_lTrg | pad->_lRpt;
        upTmp = 1;
        if ((edge & 1) == 0 && ((trigger | repeat) & 0x10) == 0) upTmp = 0;
        up = upTmp;
        down = (edge & 4) || ((trigger | repeat) & 0x40);
        left = (edge & 8) || ((trigger | repeat) & 0x80);
        right = (edge & 2) || ((trigger | repeat) & 0x20);
    }
    switch (NS._st0) {
    case 0:
        switch (NS._st1) {
        case 0:
            POS(pos0) beNDMWLoadIntf2ComMdlCtrl__StartAt(CM, NS._ramNo, DAT_00516ca8, DAT_004cec74[NS._selDataNo].name, &pos0, 1);
            DRAWPOS(pos1, DAT_00516f50, DAT_00516cd0, 1)
            DRAWPOS(pos2, DAT_00516f60, DAT_00516cd0, 1)
            DRAWPOS(pos3, DAT_00516f70, DAT_00516cd0, 1)
            DRAWPOS(pos4, DAT_00516f80, DAT_00516cd0, 1)
            DRAWPOS(pos5, DAT_00516f98, DAT_00516cd0, 1)
            DRAWPOS(pos6, DAT_00516fb0, DAT_00516cd0, 1)
            DRAWPOS(pos7, DAT_00516fd0, DAT_00516cd0, 1)
            NS._isSideCur = 1;
            SETCH
            sprintf(buf0, DAT_00516fe8, NS._nameCurPos);
            switch (NS._langID) {
            case 0: DRAWPOS(pos8, DAT_00516ff8, buf0, 0) break;
            default: case 1: DRAWPOS(pos9, DAT_00517008, buf0, 0) break;
            }
            FUN_003de480(s, 0);
            FUN_003de7a0(s, 0);
            FUN_003de990(s, 0);
            NEXT
            break;
        case 1:
            if (beNDMWLoadIntf2ComMdlCtrl__IsOpenQueueEmpty(CM, down, up, trigger) == 1) { NEXT }
            break;
        case 2:
            if (NS._nameCurPos >= NS._nameMojiMax) NS._nameCurPos = NS._nameMojiMax - 1;
            sprintf(buf1, DAT_00517018, NS._yokoCurPos);
            beNDMWLoadIntf2ComMdlCtrl__Play(CM, NS._ramNo, DAT_00516f60, buf1, 1);
            NEXT
            break;
        case 3:
            if (beNDMWLoadIntf2ComMdlCtrl__IsOpenQueueEmpty(CM, down, up, trigger) == 1) { NS._st0 = 1; NS._st3 = 0; NS._st2 = 0; NS._st1 = 0; }
            break;
        }
        break;
    case 1:
        switch (NS._st1) {
        case 0:
            if (right) {
                NS._yokoCurPos++;
                if (NS._yokoCurPos >= 5) {
                    NS._yokoCurPos = 4;
                    if (DAT_004cc860[NS._tatePoint].mod > 5) {
                        NS._yokoPoint++;
                        if (NS._yokoPoint >= DAT_004cc860[NS._tatePoint].mod) NS._yokoPoint = 0;
                        if (NS._isSideCur == 1) {
                            beNDMWLoadIntf2ComMdlCtrl__Play(CM, NS._ramNo, DAT_00516fd0, DAT_00517028, 1);
                            sprintf(buf2, DAT_00517030, NS._nameCurPos);
                            LANGDRAW(buf2, 1)
                        }
                        FUN_003de7a0(s, 0);
                    }
                } else {
                    sprintf(buf3, DAT_00517018, NS._yokoCurPos);
                    beNDMWLoadIntf2ComMdlCtrl__Play(CM, NS._ramNo, DAT_00516f60, buf3, 1);
                    sprintf(buf4, DAT_00517030, NS._nameCurPos);
                    LANGDRAW(buf4, 1)
                }
                SETCH
                FUN_003de990(s, 0);
                NEXT
            } else if (left) {
                NS._yokoCurPos--;
                if (NS._yokoCurPos < 0) {
                    NS._yokoCurPos = 0;
                    if (DAT_004cc860[NS._tatePoint].mod > 5) {
                        NS._yokoPoint--;
                        if (0 > NS._yokoPoint) NS._yokoPoint = DAT_004cc860[NS._tatePoint].mod - 1;
                        FUN_003de7a0(s, 0);
                        if (NS._isSideCur == 1) {
                            beNDMWLoadIntf2ComMdlCtrl__Play(CM, NS._ramNo, DAT_00516fb0, DAT_00517028, 1);
                            sprintf(buf5, DAT_00517030, NS._nameCurPos);
                            LANGDRAW(buf5, 1)
                        }
                    }
                } else {
                    sprintf(buf6, DAT_00517018, NS._yokoCurPos);
                    beNDMWLoadIntf2ComMdlCtrl__Play(CM, NS._ramNo, DAT_00516f60, buf6, 1);
                    sprintf(buf7, DAT_00517030, NS._nameCurPos);
                    LANGDRAW(buf7, 1)
                }
                SETCH
                FUN_003de990(s, 0);
                NEXT
            } else if (up) {
                beNDMWLoadIntf2ComMdlCtrl__Play(CM, NS._ramNo, DAT_00516f98, DAT_00517028, 1);
                sprintf(buf8, DAT_00517030, NS._nameCurPos);
                LANGDRAW(buf8, 1)
                NS._tatePoint--;
                if (NS._tatePoint < NS._tateMin) NS._tatePoint = NS._tateMax - 1;
                if (DAT_004cc860[NS._tatePoint].mod > 5) {
                    beNDMWLoadIntf2ComMdlCtrl__Play(CM, NS._ramNo, DAT_00516fb0, DAT_00517040, 0);
                    beNDMWLoadIntf2ComMdlCtrl__Play(CM, NS._ramNo, DAT_00516fd0, DAT_00517040, 0);
                    NS._isSideCur = 1;
                } else {
                    beNDMWLoadIntf2ComMdlCtrl__Play(CM, NS._ramNo, DAT_00516fb0, DAT_00517050, 0);
                    beNDMWLoadIntf2ComMdlCtrl__Play(CM, NS._ramNo, DAT_00516fd0, DAT_00517050, 0);
                    NS._isSideCur = 0;
                }
                NS._yokoPoint = 0;
                SETCH
                NEXT
                FUN_003de990(s, 0);
                FUN_003de480(s, 0);
                FUN_003de7a0(s, 0);
            } else if (down) {
                beNDMWLoadIntf2ComMdlCtrl__Play(CM, NS._ramNo, DAT_00516f80, DAT_00517028, 1);
                sprintf(buf9, DAT_00517030, NS._nameCurPos);
                LANGDRAW(buf9, 1)
                NS._tatePoint++;
                if (NS._tatePoint >= NS._tateMax) NS._tatePoint = NS._tateMin;
                if (DAT_004cc860[NS._tatePoint].mod > 5) {
                    beNDMWLoadIntf2ComMdlCtrl__Play(CM, NS._ramNo, DAT_00516fb0, DAT_00517040, 0);
                    beNDMWLoadIntf2ComMdlCtrl__Play(CM, NS._ramNo, DAT_00516fd0, DAT_00517040, 0);
                    NS._isSideCur = 1;
                } else {
                    beNDMWLoadIntf2ComMdlCtrl__Play(CM, NS._ramNo, DAT_00516fb0, DAT_00517050, 0);
                    beNDMWLoadIntf2ComMdlCtrl__Play(CM, NS._ramNo, DAT_00516fd0, DAT_00517050, 0);
                    NS._isSideCur = 0;
                }
                NS._yokoPoint = 0;
                SETCH
                NEXT
                FUN_003de990(s, 0);
                FUN_003de7a0(s, 0);
                FUN_003de480(s, 0);
            } else if (trigger & 0x4000) {
                if (NS._nameCurPos < NS._nameMojiMax) {
                    s->t.save[NS._nameCurPos].tate = NS._tatePoint;
                    s->t.save[NS._nameCurPos].yoko = NS._yokoPoint;
                    s->t.save[NS._nameCurPos].cur = NS._yokoCurPos;
                    s->t.mode[NS._nameCurPos] = 2;
                    SETCH
                    sprintf(buf10, DAT_00517060, NS._nameCurPos);
                    LANGDRAW(buf10, 1)
                    NS._nameCurPos++;
                    s->t.name[NS._nameCurPos + 1] = 0;
                    s->t.mode[NS._nameCurPos] = 1;
                    NS._st1 = 3; NS._st3 = 0; NS._st2 = 0;
                }
                FUN_003de990(s, 0);
            } else if (trigger & 0x2000) {
                s->t.name[NS._nameCurPos] = 0;
                NS._nameCurPos--;
                LANG(beNDMWLoadIntf2ComMdlCtrl__Play(CM, NS._ramNo, DAT_00516ff8, DAT_00517070, 1), beNDMWLoadIntf2ComMdlCtrl__Play(CM, NS._ramNo, DAT_00517008, DAT_00517070, 1))
                if (NS._nameCurPos < 0) {
                    NS._nameCurPos = -1; NS._st0 = 4; NS._st3 = 0; NS._st2 = 0; NS._st1 = 0;
                } else {
                    NS._tatePoint = s->t.save[NS._nameCurPos].tate;
                    NS._yokoPoint = s->t.save[NS._nameCurPos].yoko;
                    NS._yokoCurPos = s->t.save[NS._nameCurPos].cur;
                    SETCH
                    sprintf(buf11, DAT_00517018, NS._yokoCurPos);
                    beNDMWLoadIntf2ComMdlCtrl__Play(CM, NS._ramNo, DAT_00516f60, buf11, 1);
                    FUN_003de7a0(s, 0);
                    FUN_003de480(s, 0);
                    NS._st1 = 2; NS._st3 = 0; NS._st2 = 0;
                }
                FUN_003de990(s, 0);
            } else if (trigger & 8) {
                if (NS._nameCurPos > 0) {
                    sprintf(buf12, DAT_00517060, NS._nameCurPos);
                    LANGDRAW(buf12, 1)
                    s->t.name[NS._nameCurPos] = 0;
                    NS._nameCurPos--;
                    FUN_003de990(s, 0);
                    NS._st1 = 4; NS._st3 = 0; NS._st2 = 0;
                }
            }
            break;
        case 1:
            if (beNDMWLoadIntf2ComMdlCtrl__IsOpenQueueEmpty(CM, down, up, trigger) & 0xFF) { NS._st1 = 0; NS._st3 = 0; NS._st2 = 0; }
            break;
        case 2:
            if (beNDMWLoadIntf2ComMdlCtrl__IsOpenQueueEmpty(CM, down, up, trigger) & 0xFF) {
                sprintf(buf13, DAT_00516fe8, NS._nameCurPos);
                LANGDRAW(buf13, 0)
                s->t.mode[NS._nameCurPos] = 1;
                FUN_003de990(s, 0);
                NS._st1 = 0; NS._st3 = 0; NS._st2 = 0;
            }
            break;
        case 3:
            if (beNDMWLoadIntf2ComMdlCtrl__IsOpenQueueEmpty(CM, down, up, trigger) & 0xFF) {
                if (NS._nameCurPos >= NS._nameMojiMax) {
                    NS._nameCurPos = NS._nameMojiMax - 1; NS._st0 = 2; NS._st3 = 0; NS._st2 = 0; NS._st1 = 0;
                } else {
                    sprintf(buf14, DAT_00516fe8, NS._nameCurPos);
                    LANGDRAW(buf14, 0)
                    SETCH
                    FUN_003de990(s, 0);
                }
                {
                    int i;
                    for (i = NS._nameCurPos + 1; i < NS._nameMojiMax; i++) s->t.name[i] = 0;
                }
                NS._st1 = 0; NS._st3 = 0; NS._st2 = 0;
            }
            break;
        case 4:
            if (beNDMWLoadIntf2ComMdlCtrl__IsOpenQueueEmpty(CM, down, up, trigger) & 0xFF) { NS._st0 = 2; NS._st3 = 0; NS._st2 = 0; NS._st1 = 0; }
            break;
        }
        break;
    case 2:
        switch (NS._st1) {
        case 0:
            LANGDRAW(DAT_00516dd8, 1)
            NEXT
            break;
        case 1:
            if (beNDMWLoadIntf2ComMdlCtrl__IsCloseQueueEmpty(CM, down, up, trigger) == 1) { NS._st0 = 3; NS._st3 = 0; NS._st2 = 0; NS._st1 = 0; }
            break;
        }
        break;
    case 3:
        switch (NS._st1) {
        case 0:
            NS._isQuestion = 1;
            NS._isAnswer = 0;
            NEXT
            break;
        case 1:
            if (NS._isAnswer == 1) {
                NS._isQuestion = 0;
                if (NS._isNameOK == 1) { NEXT NS._isMakeName = 1; }
                else { NS._isMakeName = 0; NS._st1 = 4; NS._st3 = 0; NS._st2 = 0; }
            }
            break;
        case 2:
            LANGDRAW0(DAT_00516d40, 1)
            NEXT
            break;
        case 3:
            if (beNDMWLoadIntf2ComMdlCtrl__IsCloseQueueEmpty(CM, down, up, trigger) == 1) { NS._st0 = 5; NS._st3 = 0; NS._st2 = 0; NS._st1 = 0; }
            break;
        case 4:
            NS._tatePoint = s->t.save[NS._nameCurPos].tate;
            NS._yokoPoint = s->t.save[NS._nameCurPos].yoko;
            NS._yokoCurPos = s->t.save[NS._nameCurPos].cur;
            s->t.mode[NS._nameCurPos] = 1;
            sprintf(buf15, DAT_00516fe8, NS._nameCurPos);
            LANGDRAW(buf15, 0)
            sprintf(buf15, DAT_00517018, NS._yokoCurPos);
            beNDMWLoadIntf2ComMdlCtrl__Play(CM, NS._ramNo, DAT_00516f60, buf15, 1);
            FUN_003de7a0(s, 0);
            FUN_003de480(s, 0);
            FUN_003de990(s, 0);
            NEXT
            break;
        case 5:
            if (beNDMWLoadIntf2ComMdlCtrl__IsCloseQueueEmpty(CM, down, up, trigger) == 1) { NS._st0 = 1; NS._st3 = 0; NS._st2 = 0; NS._st1 = 0; }
            break;
        }
        break;
    case 4:
        switch (NS._st1) {
        case 0:
            LANGDRAW0(DAT_00516d30, 1)
            NEXT
            break;
        case 1:
            if (beNDMWLoadIntf2ComMdlCtrl__IsCloseQueueEmpty(CM, down, up, trigger) == 1) { NS._st0 = 5; NS._st3 = 0; NS._st2 = 0; NS._st1 = 0; }
            break;
        }
        break;
    case 5:
        switch (NS._st1) {
        case 0:
            FUN_003de480(s, 1);
            FUN_003de7a0(s, 1);
            FUN_003de990(s, 1);
            beNDMWLoadIntf2ComMdlCtrl__Close(CM, NS._ramNo, DAT_00516ca8, DAT_00516d30, 1);
            beNDMWLoadIntf2ComMdlCtrl__Close(CM, NS._ramNo, DAT_00516f70, DAT_00516d30, 1);
            beNDMWLoadIntf2ComMdlCtrl__Close(CM, NS._ramNo, DAT_00516f50, DAT_00516d30, 1);
            beNDMWLoadIntf2ComMdlCtrl__Close(CM, NS._ramNo, DAT_00516f60, DAT_00516d30, 1);
            beNDMWLoadIntf2ComMdlCtrl__Close(CM, NS._ramNo, DAT_00516f80, DAT_00516d30, 1);
            beNDMWLoadIntf2ComMdlCtrl__Close(CM, NS._ramNo, DAT_00516f98, DAT_00516d30, 1);
            beNDMWLoadIntf2ComMdlCtrl__Close(CM, NS._ramNo, DAT_00516fb0, DAT_00516d30, 1);
            beNDMWLoadIntf2ComMdlCtrl__Close(CM, NS._ramNo, DAT_00516fd0, DAT_00516d30, 1);
            NEXT
            break;
        case 1:
            if (beNDMWLoadIntf2ComMdlCtrl__IsCloseQueueEmpty(CM, 1, up, trigger) == 1) NS._isEnd = 1;
            break;
        }
        break;
    }
    return NS._isEnd;
}
} /* extern "C" */
