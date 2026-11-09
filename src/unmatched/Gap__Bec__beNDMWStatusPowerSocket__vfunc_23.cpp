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
void Gap__Bec__beNDMWStatusPowerSocket__vfunc_23(beNDMWStatusPowerSocket *self, int open);
void beNDMWWindow_ClearQueuedText(beNDMWStatusPowerSocket *);
void beNDMWWindow_PlayQueuedModelClose(void);
void beNDMWWindow_PresentModelAtOrigin(beNDMWStatusPowerSocket *, const char *, int, const char *, const char *);
extern char DAT_00519e78[];                 /* "i_stsoubi" */
extern char DAT_00519e88[];                 /* "SQ_POWEROPEN" */
extern char DAT_00519a58[];                 /* "SQ_CLOSE" */
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

void Gap__Bec__beNDMWStatusPowerSocket__vfunc_23(beNDMWStatusPowerSocket *self, int open) {
    int *a1;
    int v1;
    void *pool;
    int *old;
    igDataList *l;
    int n;
    int i;
    int **slot;
    int *nw;
    int *a12;
    int v12;
    void *pool2;
    int *old2;
    igDataList *l2;
    int n2;
    int i2;
    int **slot2;
    int *nw2;
    if (open) {
        beNDMWWindow_PresentModelAtOrigin(self, DAT_00519e78, 0, DAT_00519e88, DAT_00519a58);
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
            beNDMWWindow_PresentModelAtOrigin(self, DAT_00519ef8, 0, sequence.p, DAT_00519a58);
        }

    } else {
        beNDMWWindow_PlayQueuedModelClose();
        l = (igDataList *)self->_modelCloseInfoNameList;
        n = l->_count;
        for (i = 0; i < n; i++) {
            slot = &((int **)l->_data)[i];
            if (DAT_00586f20[0] == 0) {
                pool = FUN_002eb010(0x10);
                if (pool != 0) {
                    pool = StringPool_Construct(pool);
                }
                DAT_00586f20[0] = pool;
            }
            nw = (int *)StringPool_Intern(DAT_00586f20[0], (const char *)0);
            old = *slot;
            if (old != 0) {
                a1 = old - 2;
                v1 = old[-1] - 1;
                old[-1] = v1;
                if (v1 == 0) {
                    StringChunk_ReleaseHeader(*a1, a1);
                }
            }
            *slot = nw;
        }
        l->_count = 0;
        ((igDataList *)self->_modelCloseRamNoList)->_count = 0;
        l2 = (igDataList *)self->_modelCloseSeqNameList;
        n2 = l2->_count;
        for (i2 = 0; i2 < n2; i2++) {
            slot2 = &((int **)l2->_data)[i2];
            if (DAT_00586f20[0] == 0) {
                pool2 = FUN_002eb010(0x10);
                if (pool2 != 0) {
                    pool2 = StringPool_Construct(pool2);
                }
                DAT_00586f20[0] = pool2;
            }
            nw2 = (int *)StringPool_Intern(DAT_00586f20[0], (const char *)0);
            old2 = *slot2;
            if (old2 != 0) {
                a12 = old2 - 2;
                v12 = old2[-1] - 1;
                old2[-1] = v12;
                if (v12 == 0) {
                    StringChunk_ReleaseHeader(*a12, a12);
                }
            }
            *slot2 = nw2;
        }
        l2->_count = 0;
        beNDMWWindow_ClearQueuedText(self);
    }
}
