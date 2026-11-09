/* Bool flags use daddiu, ram->_ramNo and ram->_svSeqName are hoisted into locals before the NAME
 * ternary, switch(st3) has case 0 and default, info is declared first, the on-demand data list is held by an igSmartPointer<igObject>, and the decide-list
 * byte test uses an unsigned index. */
#include "dw4/igSmartPointer.h"
static inline int st2Of(const beBaseInfoRam *r) { return r->_st2; }
extern "C" {
extern char DAT_0050f8b0[];
int sprintf(...);
int FUN_002eb010(...);
igObject *beBaseInfoDataList_Create(...);
int Memory_GetAllocatorBySelector(...);
int StringChunk_ReleaseHeader(...);
int StringPool_Construct(...);
int *StringPool_Intern(...);
int beMessenger_AppendString(...);
int beMessenger_AppendVec3(...);
int beMessenger_DispatchSelected(...);
int beMessenger_GetBool(...);
int beMessenger_SelectGroup(...);
int beMessenger_SelectReceivers(...);
int beMessenger_SendNamed(...);
int *bePadManager_GetPadForPlayer(...);
int igObject_GetAllocator(...);
beSelectCtrlInfoRamData *igProperty_FindByName(...);
extern int DAT_004e0858[4];
extern int DAT_0050f800[4];
extern int DAT_0050f808[4];
extern int DAT_0050f818[4];
extern int DAT_0050f820[4];
extern int DAT_0050f830[4];
extern int DAT_0050f840[4];
extern int DAT_0050f850[4];
extern int DAT_0050f860[4];
extern int DAT_0050f870[4];
extern int DAT_0050f878[4];
extern int DAT_0050f888[4];
extern int DAT_0050f890[4];
extern int DAT_0050f8a0[4];
extern int DAT_0050f8c0[4];
extern int DAT_00585be0[4];
extern int DAT_00586f20[4];
extern int DAT_00587110[4];
extern unsigned char GPR_00554c14;
}

#define NAME (info->_name ? info->_name : (int)&DAT_004e0858[0])
typedef struct DecideList { char pad[16]; unsigned char *data; } DecideList;
/* Owning stack reference to the freshly created data list; released on scope exit (reference count
 * in the low 23 bits of _refCount). */

extern "C" void Gap__Bec__beSelectCtrl__vfunc_31(beSelectCtrl *self, beBaseInfoRam *ram) {
    beBaseInfo *info;
    float vec[3];
    char buf1[16];
    char buf2[16];
    char buf3[16];
    char buf4[16];
    int hold;
    beSelectCtrlInfoRamData *rd;
    int trig;
    int *old;
    int state;
    bool moved;
    beSelectCtrlInfoWork *wk;
    int *pad;
    bool up;
    int allocator;
    bool down;
    int v;
    int cur;
    int cnt;
    unsigned input;
    int *hd;
    bool left;
    bool right;
    int *s;

    if (ram->_isRun == 0) return;
    info = (beBaseInfo *)ram->_parentInfo;
    if (ram->_dataList == 0) {
        igObject *s3;
        igObject *o;
        allocator = igObject_GetAllocator(ram);
        allocator = GPR_00554c14 != 0 ? allocator : Memory_GetAllocatorBySelector(DAT_00587110[0]);
        igSmartPointer<igObject> ref(beBaseInfoDataList_Create(allocator));
        s3 = ref.p;
        if (s3 != 0) s3->_refCount = s3->_refCount + 1;
        o = (igObject *)ram->_dataList;
        if (o != 0) {
            o->_refCount = o->_refCount - 1;
            if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o);
        }
        ram->_dataList = (int)s3;
    }
    rd = igProperty_FindByName(ram->_dataList, DAT_00585be0[0], &DAT_0050f800[0]);
    wk = (beSelectCtrlInfoWork *)rd->_work;
    pad = bePadManager_GetPadForPlayer(self->_padManager, ram->_ramNo);
    state = ram->_st0;
    input = pad[18];
    trig = pad[9];
    hold = pad[17] & 0xF0;
    switch (state) {
    case 0:
        switch (ram->_st1) {
        case 0:
            { int rn = ram->_ramNo; beMessenger_SelectReceivers(self->_messenger, &DAT_0050f808[0], NAME, rn); }
            vec[0] = *(float *)&wk->_offsetPos[0];
            vec[1] = *(float *)&wk->_offsetPos[1];
            vec[2] = *(float *)&wk->_offsetPos[2];
            beMessenger_AppendVec3(self->_messenger, vec);
            beMessenger_AppendString(self->_messenger, &DAT_0050f818[0]);
            beMessenger_DispatchSelected(self->_messenger, &DAT_0050f820[0]);
            ram->_st1 = ram->_st1 + 1;
            ram->_st3 = 0;
            ram->_st2 = 0;
            return;
        case 1:
            { int rn = ram->_ramNo; beMessenger_SelectReceivers(self->_messenger, &DAT_0050f808[0], NAME, rn); }
            beMessenger_AppendString(self->_messenger, &DAT_0050f818[0]);
            beMessenger_DispatchSelected(self->_messenger, &DAT_0050f830[0]);
            if ((beMessenger_GetBool(self->_messenger, 0) & 0xFF) != 1) {
                sprintf(buf1, &DAT_0050f840[0], rd->_selectNo);
                { int rn = ram->_ramNo; beMessenger_SendNamed(self->_messenger, &DAT_0050f808[0], NAME, rn, buf1); }
                ram->_st0 = ram->_st0 + 1;
                ram->_st3 = 0;
                ram->_st2 = 0;
                ram->_st1 = 0;
                return;
            }
            break;
        }
        break;
    case 1:
        switch (ram->_st1) {
        case 0:
            if (trig != 0 || hold != 0) {
                switch (ram->_st3) {
                case 0:
                    cur = rd->_selectNo;
                    moved = false;
                    up = true;
                    if (!(trig & 8) && !(hold & 0x80)) up = false;
                    down = true;
                    if (!(trig & 2) && !(hold & 0x20)) down = false;
                    left = true;
                    if (!(trig & 1) && !(hold & 0x10)) left = false;
                    right = true;
                    if (!(trig & 4) && !(hold & 0x40)) right = false;
                    v = rd->_isTateSelect;
                    if ((v != 0 && left) || (v == 0 && up)) {
                        if (cur != 0) {
                            cur = cur - 1;
                            moved = true;
                            sprintf(buf2, &DAT_0050f850[0], cur);
                            if (DAT_00586f20[0] == 0) {
                                v = FUN_002eb010(0x10);
                                if (v != 0) v = StringPool_Construct(v);
                                DAT_00586f20[0] = v;
                            }
                            s = StringPool_Intern(DAT_00586f20[0], buf2);
                            old = (int *)wk->_svSeqName;
                            if (old != 0) {
                                hd = old - 2;
                                v = old[-1] - 1;
                                old[-1] = v;
                                if (v == 0) StringChunk_ReleaseHeader(*hd, hd);
                            }
                            wk->_svSeqName = (int)s;
                        }
                    } else if (((v != 0 && right) || (v == 0 && down)) && cur != wk->_selectMax - 1) {
                        cur = cur + 1;
                        moved = true;
                        sprintf(buf3, &DAT_0050f860[0], cur);
                        if (DAT_00586f20[0] == 0) {
                            v = FUN_002eb010(0x10);
                            if (v != 0) v = StringPool_Construct(v);
                            DAT_00586f20[0] = v;
                        }
                        s = StringPool_Intern(DAT_00586f20[0], buf3);
                        old = (int *)wk->_svSeqName;
                        if (old != 0) {
                            hd = old - 2;
                            v = old[-1] - 1;
                            old[-1] = v;
                            if (v == 0) StringChunk_ReleaseHeader(*hd, hd);
                        }
                        wk->_svSeqName = (int)s;
                    }
                    if (moved) {
                        rd->_selectNo = cur;
                        { int sq = wk->_svSeqName; int rn = ram->_ramNo; beMessenger_SendNamed(self->_messenger, &DAT_0050f808[0], NAME, rn, sq); }
                        ram->_st3 = ram->_st3 + 1;
                    }
                    break;
                default:
                    { int rn = ram->_ramNo; beMessenger_SelectReceivers(self->_messenger, &DAT_0050f808[0], NAME, rn); }
                    beMessenger_AppendString(self->_messenger, wk->_svSeqName);
                    beMessenger_DispatchSelected(self->_messenger, &DAT_0050f830[0]);
                    if (beMessenger_GetBool(self->_messenger, 0) == 0) ram->_st3 = 0;
                }
            }
            if (input & 0x2000) {
                if (wk->_isCancel != 0) {
                    rd->_selectNo = -1;
                    ram->_st0 = ram->_st0 + 1;
                    ram->_st3 = 0;
                    ram->_st2 = 0;
                    ram->_st1 = 0;
                    return;
                }
                beMessenger_SelectGroup(self->_messenger, &DAT_0050f870[0]);
                beMessenger_AppendString(self->_messenger, &DAT_0050f878[0]);
                beMessenger_DispatchSelected(self->_messenger, &DAT_0050f888[0]);
                ram->_st1 = 2;
                ram->_st3 = 0;
                ram->_st2 = 0;
                return;
            }
            if (input & 0x4000) {
                DecideList *dl = (DecideList *)wk->_decideList;
                if (dl != 0 && ((unsigned char *)dl->data)[(unsigned)rd->_selectNo] == 0) {
                    beMessenger_SelectGroup(self->_messenger, &DAT_0050f870[0]);
                    beMessenger_AppendString(self->_messenger, &DAT_0050f878[0]);
                    beMessenger_DispatchSelected(self->_messenger, &DAT_0050f888[0]);
                    ram->_st1 = 2;
                    ram->_st3 = 0;
                    ram->_st2 = 0;
                    return;
                }
                sprintf(buf4, &DAT_0050f890[0], rd->_selectNo);
                if (DAT_00586f20[0] == 0) {
                    v = FUN_002eb010(0x10);
                    if (v != 0) v = StringPool_Construct(v);
                    DAT_00586f20[0] = v;
                }
                s = StringPool_Intern(DAT_00586f20[0], buf4);
                old = (int *)wk->_svSeqName;
                if (old != 0) {
                    hd = old - 2;
                    v = old[-1] - 1;
                    old[-1] = v;
                    if (v == 0) StringChunk_ReleaseHeader(*hd, hd);
                }
                wk->_svSeqName = (int)s;
                { int sq = wk->_svSeqName; int rn = ram->_ramNo; beMessenger_SendNamed(self->_messenger, &DAT_0050f808[0], NAME, rn, sq); }
                ram->_st1 = ram->_st1 + 1;
                ram->_st3 = 0;
                ram->_st2 = 0;
                return;
            }
            break;
        case 1:
            { int rn = ram->_ramNo; beMessenger_SelectReceivers(self->_messenger, &DAT_0050f808[0], NAME, rn); }
            beMessenger_AppendString(self->_messenger, wk->_svSeqName);
            beMessenger_DispatchSelected(self->_messenger, &DAT_0050f830[0]);
            if (beMessenger_GetBool(self->_messenger, 0) == 0) {
                ram->_st0 = ram->_st0 + 1;
                ram->_st3 = 0;
                ram->_st2 = 0;
                ram->_st1 = 0;
                return;
            }
            break;
        case 2:
            if (st2Of(ram) < 0x10) {
                ram->_st2 = ram->_st2 + 1;
                ram->_st3 = 0;
                return;
            }
            ram->_st1 = 0;
            ram->_st3 = 0;
            ram->_st2 = 0;
            return;
        }
        break;
    case 2:
        switch (ram->_st1) {
        case 0:
            if (rd->_selectNo != -1) s = (int *)&DAT_0050f8a0[0];
            else s = (int *)DAT_0050f8b0;
            if (DAT_00586f20[0] == 0) {
                v = FUN_002eb010(0x10);
                if (v != 0) v = StringPool_Construct(v);
                DAT_00586f20[0] = v;
            }
            hd = StringPool_Intern(DAT_00586f20[0], s);
            old = (int *)wk->_svSeqName;
            if (old != 0) {
                int *h2 = old - 2;
                v = old[-1] - 1;
                old[-1] = v;
                if (v == 0) StringChunk_ReleaseHeader(*h2, h2);
            }
            wk->_svSeqName = (int)hd;
            { int sq = wk->_svSeqName; int rn = ram->_ramNo; beMessenger_SendNamed(self->_messenger, &DAT_0050f808[0], NAME, rn, sq); }
            ram->_st1 = ram->_st1 + 1;
            ram->_st3 = 0;
            ram->_st2 = 0;
            return;
        case 1:
            { int rn = ram->_ramNo; beMessenger_SelectReceivers(self->_messenger, &DAT_0050f808[0], NAME, rn); }
            beMessenger_AppendString(self->_messenger, wk->_svSeqName);
            beMessenger_DispatchSelected(self->_messenger, &DAT_0050f830[0]);
            if (beMessenger_GetBool(self->_messenger, 0) == 0) {
                ram->_st0 = ram->_st0 + 1;
                ram->_st3 = 0;
                ram->_st2 = 0;
                ram->_st1 = 0;
                return;
            }
            break;
        }
        break;
    case 10:
        switch (ram->_st1) {
        case 0:
            { int rn = ram->_ramNo; beMessenger_SendNamed(self->_messenger, &DAT_0050f808[0], NAME, rn, &DAT_0050f8c0[0]); }
            ram->_st1 = ram->_st1 + 1;
            ram->_st3 = 0;
            ram->_st2 = 0;
            return;
        case 1:
            { int rn = ram->_ramNo; beMessenger_SelectReceivers(self->_messenger, &DAT_0050f808[0], NAME, rn); }
            beMessenger_AppendString(self->_messenger, &DAT_0050f8c0[0]);
            beMessenger_DispatchSelected(self->_messenger, &DAT_0050f830[0]);
            if (beMessenger_GetBool(self->_messenger, 0) == 0) {
                ram->_st0 = 1;
                ram->_st3 = 0;
                ram->_st2 = 0;
                ram->_st1 = 0;
                return;
            }
            break;
        }
        break;
    default:
        ram->_isRun = 0;
        {
            igObject *o = (igObject *)rd->_work;
            if (o != 0) {
                o->_refCount = o->_refCount - 1;
                if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o);
            }
        }
        rd->_work = 0;
        break;
    }
}
