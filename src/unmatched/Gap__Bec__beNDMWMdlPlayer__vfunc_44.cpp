struct igResult { int w0; igResult() {} igResult(const igResult &o) { w0 = o.w0; } bool operator==(const igResult &o) const { return w0 == o.w0; } };
extern "C" {
#include "dw4/reflected.h"

typedef struct Ref { int vt; unsigned rc; } Ref;
typedef struct Msg {
    char _pad0[8];
    int number;            /* +8  player number */
    char *info;            /* +12 */
    char _pad16[24];
    Ref *cache;            /* +40 */
} Msg;

void *igObject_GetAllocator(Msg *);
void *Memory_GetAllocatorBySelector(int);
Ref *beBaseInfoDataList_Create(void *);
void igObject_Destroy(Ref *);
struct PropertyRecord { char header[20]; beNDMWMdlPlayerInfoWork *value; };
PropertyRecord *igProperty_FindByName(Ref *, int, const char *);
int igStrCmp(int, const char *);
void beMessenger_SelectReceivers(int, const char *, const char *, int);
void beMessenger_AppendString(int, const char *);
void sprintf(char *, const char *, int);
void beMessenger_AppendFloat(int, float);
void beMessenger_AppendVec3(int, int *);
void beMessenger_AppendBool(int, int);
void beMessenger_DispatchSelected(int, const char *);
void *FUN_003bf830(void);
igResult igMetaEnum_GetValueByName(void *, int, int *);
void beMessenger_SendNamed(int, const char *, int, int, const char *);
void FUN_00445200(void *, Msg *);

extern unsigned char GPR_00554c14;
extern char DAT_004e0858[], DAT_00516110[], DAT_00516148[], DAT_00516228[], DAT_00516290[], DAT_005164b0[], DAT_005164b8[], DAT_005164c8[], DAT_005164d8[];
}
struct Tmp { Ref *p; Tmp(Ref *q) : p(q) {} ~Tmp() { Ref *q = p; if (q) { q->rc--; if ((q->rc & 0x7fffff) == 0) igObject_Destroy(q); } } };
extern int DAT_00587110[4], DAT_00585be0[4];
extern "C" igResult DAT_004fb410;

static inline void ensureCache(Msg *msg)
{
    if (msg->cache == 0) {
        void *al = igObject_GetAllocator(msg);
        void *al2;
        if (GPR_00554c14 != 0) {
            al2 = al;
        } else {
            al2 = Memory_GetAllocatorBySelector(DAT_00587110[0]);
        }
        Tmp t(beBaseInfoDataList_Create(al2));
        Ref *r = t.p;
        if (r) r->rc++;
        Ref *old = msg->cache;
        if (old) {
            old->rc--;
            if ((old->rc & 0x7fffff) == 0) igObject_Destroy(old);
        }
        msg->cache = r;
    }
}

extern "C" void Gap__Bec__beNDMWMdlPlayer__vfunc_44(beNDMWMdlPlayer *self, Msg *msg)
{
    beNDMWMdlPlayerInfoWork *pinfo;
    Ref *r;
    char *minfo = msg->info;
    char name[24];
    int vec[3];
    int tmp;
    ensureCache(msg);
    Ref *c0 = msg->cache;
    pinfo = igProperty_FindByName(c0, DAT_00585be0[0], DAT_00516110)->value;
    if (igStrCmp(pinfo->_seqCodeName, DAT_00516290) == 0) {
        const char *who = *(char **)(minfo + 8);
        int num = msg->number;
        const char *w2 = who ? who : DAT_004e0858;
        beMessenger_SelectReceivers(self->_messenger, DAT_00516228, w2, num);
        beMessenger_AppendString(self->_messenger, DAT_005164b8);
        sprintf(name, DAT_005164c8, msg->number);
        beMessenger_AppendString(self->_messenger, name);
        beMessenger_AppendFloat(self->_messenger, 480.0f);
        vec[0] = 0; vec[1] = 0x41200000; vec[2] = 0;
        beMessenger_AppendVec3(self->_messenger, vec);
        beMessenger_AppendBool(self->_messenger, 1);
        beMessenger_AppendBool(self->_messenger, 1);
        beMessenger_DispatchSelected(self->_messenger, DAT_005164d8);
    }
    if (pinfo->_isPanel != 0) {
        if (igMetaEnum_GetValueByName(FUN_003bf830(), pinfo->_seqCodeName, &tmp) == DAT_004fb410) {
            pinfo->_isPanel = 0;
            beMessenger_SendNamed(self->_messenger, DAT_00516148, 0, msg->number, DAT_005164b0);
        }
    }
    FUN_00445200(self, msg);
}
