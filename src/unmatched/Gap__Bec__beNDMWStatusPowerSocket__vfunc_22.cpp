#include "dw4/reflected.h"
extern "C" {
void *FUN_002eb010(int);
void *StringPool_Construct(void *);
const char *StringPool_Intern(void *, const char *);
void StringChunk_ReleaseHeader(int, int *);
void *FUN_00236f80(int, int);
const char *beNDMWItemBase_GetRecordString(void *, void *, const char *);
void beMessenger_SendNamed(int, const char *, const char *, int, const char *);
void beMessenger_SelectGroup(int, const char *);
void beMessenger_AppendString(int, const char *);
void beMessenger_DispatchSelected(int, const char *);
extern void *DAT_00586f20[4];
extern int DAT_0058b028[4];
extern char DAT_00519a90[];                 /* "MODELCTRL" */
extern char DAT_00519ef8[];                 /* "i_stpocket" */
extern char DAT_00519e98[];                 /* "SQ_0LINEOPEN" */
extern char DAT_00519ea8[];
extern char DAT_00519eb8[];
extern char DAT_00519ec8[];
extern char DAT_00519ed8[];
extern char DAT_00519ee8[];                 /* "SQ_5LINEOPEN" */
extern char DAT_00519b00[];                 /* "DISPOFF" */
extern char DAT_00519b78[];                 /* "DISPON" */
extern char DAT_00519b08[];                 /* "SWITCH" */
extern char DAT_00519c28[];                 /* "TEXTCTL" */
extern char DAT_00519db0[];                 /* "STWINFONT11" */
extern char DAT_00519f28[];                 /* "NAME" */
extern char DAT_00519f30[];                 /* "TEXTSET" */
extern char DAT_00519d98[];                 /* "font100" */
extern char DAT_00519dc0[];
extern char DAT_00519dc8[];
extern char DAT_00519dd0[];
extern char DAT_00519dd8[];
void Gap__Bec__beNDMWStatusPowerSocket__vfunc_22(beNDMWStatusPowerSocket *self);
}
struct SlotKind { char p[24]; int lineCount; };

class StringRef {
public:
    const char *p;
    StringRef() : p(0) {}
    ~StringRef() { if (p) { int *h = (int *)p - 2; int r = ((int *)p)[-1] - 1; ((int *)p)[-1] = r; if (r == 0) StringChunk_ReleaseHeader(*h, h); } }
    StringRef &operator=(const char *text) {
        if (DAT_00586f20[0] == 0) {
            void *pool = FUN_002eb010(16);
            if (pool != 0) pool = StringPool_Construct(pool);
            DAT_00586f20[0] = pool;
        }
        const char *token = StringPool_Intern(DAT_00586f20[0], text);
        const char *old = p;
        if (old) { int *h = (int *)old - 2; int r = ((int *)old)[-1] - 1; ((int *)old)[-1] = r; if (r == 0) StringChunk_ReleaseHeader(*h, h); }
        p = token;
        return *this;
    }
};

void Gap__Bec__beNDMWStatusPowerSocket__vfunc_22(beNDMWStatusPowerSocket *self) {
    int lines = -1;
    igObjectList *kinds = (igObjectList *)self->_powerSocket;
    if (kinds->_count > 0) {
        SlotKind *kind = ((SlotKind **)kinds->_data)[0];
        if (kind != 0 && kind->lineCount > -1) lines = kind->lineCount;
    }
    {
        StringRef sequence;
        switch (lines) {
        case 0:
        default: sequence = DAT_00519e98; break;
        case 1: sequence = DAT_00519ea8; break;
        case 2: sequence = DAT_00519eb8; break;
        case 3: sequence = DAT_00519ec8; break;
        case 4: sequence = DAT_00519ed8; break;
        case 5: sequence = DAT_00519ee8; break;
        }
        beMessenger_SendNamed(self->_messenger, DAT_00519a90, DAT_00519ef8, 0, sequence.p);
    }
    int i = 0;
    /* matching construct: the loop guard reads the pocket list through a const view, so the body reloads it as retail does */
    const beNDMWStatusPowerSocket *view = self;
    if (0 < ((igObjectList *)view->_wpuPocket)->_count) {
        do {
            const char *font;
            const char *show;
            switch (i) {
            default: font = DAT_00519d98; break;
            case 1: font = DAT_00519dc0; break;
            case 2: font = DAT_00519dc8; break;
            case 3: font = DAT_00519dd0; break;
            case 4: font = DAT_00519dd8; break;
            }
            void *item = ((void **)((igObjectList *)self->_wpuPocket)->_data)[i];
            if (item == 0) {
                show = DAT_00519b00;
            } else {
                show = DAT_00519b78;
                const char *name = beNDMWItemBase_GetRecordString(item, FUN_00236f80(self->_insight, DAT_0058b028[0]), DAT_00519f28);
                beMessenger_SelectGroup(self->_messenger, DAT_00519c28);
                beMessenger_AppendString(self->_messenger, DAT_00519db0);
                beMessenger_AppendString(self->_messenger, font);
                beMessenger_AppendString(self->_messenger, name);
                beMessenger_DispatchSelected(self->_messenger, DAT_00519f30);
            }
            beMessenger_SelectGroup(self->_messenger, DAT_00519c28);
            beMessenger_AppendString(self->_messenger, DAT_00519db0);
            beMessenger_AppendString(self->_messenger, font);
            beMessenger_AppendString(self->_messenger, show);
            beMessenger_DispatchSelected(self->_messenger, DAT_00519b08);
            i++;
        } while (i < ((igObjectList *)self->_wpuPocket)->_count);
    }
}
