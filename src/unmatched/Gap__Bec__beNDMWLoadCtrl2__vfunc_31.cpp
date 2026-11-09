#include "dw4/reflected.h"
struct S_ref;
struct Host;
extern "C" {
int FUN_00236f80(int, int);
int beLua__RunNamedChunk(int, int *, int);
int FUN_003ecc60(beNDMWLoadCtrl2CommonIntf *, int, int);
int FUN_003f1270(int, int, int);
int FUN_003f12f0(int, int, int);
int FUN_003f1380(int, int);
int FUN_003f13d0(int, int);
int Memory_GetAllocatorBySelector(int);
int beMessenger_AppendInt(int, int);
int beMessenger_AppendString(int, int *);
int beMessenger_DispatchSelected(int, int *);
int beMessenger_GetBool(int, int);
int beMessenger_GetObject(int, int);
int beMessenger_SelectGroup(int, int *);
int beMessenger_SelectReceivers(int, int *, int *, int);
int beMessenger_SendGroup(int, int *, int *);
int beMessenger_SendNamed(int, int *, int *, int, int *);
int igObject_Destroy(struct S_ref *);
int igObject_GetAllocator(struct Host *);
void *beBaseInfoDataList_Create(int);
void *igProperty_FindByName(struct S_ref *, int, int *);
void *igProperty_GetRecord(int, int *);
extern int DAT_00517a48[4];
extern int DAT_00517af8[4];
extern int DAT_00517fe0[4];
extern int DAT_00518130[4];
extern int DAT_00518138[4];
extern int DAT_00518148[4];
extern int DAT_00518158[4];
extern int DAT_00518160[4];
extern int DAT_00518170[4];
extern int DAT_00518178[4];
extern int DAT_00518188[4];
extern int DAT_00518198[4];
extern int DAT_005181a8[4];
extern int DAT_005181b8[4];
extern int DAT_005181c8[4];
extern int DAT_005181d0[4];
extern int DAT_005181e0[4];
extern int DAT_005181e8[4];
extern int DAT_005181f8[4];
extern int DAT_00518208[4];
extern int DAT_00518218[4];
extern int DAT_00518220[4];
extern int DAT_00518230[4];
extern int DAT_00518240[4];
extern int DAT_00518250[4];
extern int DAT_00518260[4];
extern int DAT_00518270[4];
extern int DAT_00518280[4];
extern int DAT_00585be0[4];
extern int DAT_00587110[4];
extern int DAT_00589208[4];
extern int DAT_0058a1e0[4];
extern unsigned char GPR_00554c14;

struct S_ref { char pad4[4]; int f4; };
struct Host { char pad40[40]; S_ref *f40; };
/* Owning stack reference to a freshly created property data list, released on scope exit
 * (reference count in the low 23 bits of f4). */
static inline int st1(const beNDMWLoadCtrl2CtrlData *data) { return data->_st1; }
class ListRef {
public:
    S_ref *p;
    ListRef(S_ref *o) : p(o) {}
    ~ListRef() { S_ref *o = p; if (o != 0) { --o->f4; if ((o->f4 & 0x7fffff) == 0) igObject_Destroy(o); } }
};

extern "C" void Gap__Bec__beNDMWLoadCtrl2__vfunc_31(beNDMWLoadCtrl2 *arg0, Host *arg1);
void Gap__Bec__beNDMWLoadCtrl2__vfunc_31(beNDMWLoadCtrl2 *arg0, Host *arg1) {
    beNDMWLoadCtrl2CtrlData *st;
    beNDMWLoadCtrl2CommonIntf *ci;
    int i;
    int cnt;
    unsigned char ok;
    int j;
    beNDMWLoadSavePlWorkList *fw;
    int kk;
    beNDMWLoadSavePlWorkList *fw2;

    if (arg1->f40 == 0) return;
    {
        if (arg1->f40 == 0) {
            S_ref *o;
            S_ref *old;
            int base = igObject_GetAllocator(arg1);
            int a;
            if (GPR_00554c14 != 0) { a = base; } else { a = Memory_GetAllocatorBySelector(DAT_00587110[0]); }
            ListRef list((S_ref *)beBaseInfoDataList_Create(a));
            o = list.p;
            if (o != 0) o->f4 = (int)((int) (o->f4 + 1));
            old = arg1->f40;
            if (old != 0) {
                old->f4 = (int)((int) (old->f4 - 1));
                if (((unsigned long long) ((long long) old->f4 << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(old);
                }
            }
            arg1->f40 = o;
        }
        st = (beNDMWLoadCtrl2CtrlData *)igProperty_FindByName(arg1->f40, DAT_00585be0[0], &DAT_00518130[0]);
        if (arg1->f40 == 0) {
            S_ref *o;
            S_ref *old;
            int base = igObject_GetAllocator(arg1);
            int a;
            if (GPR_00554c14 != 0) { a = base; } else { a = Memory_GetAllocatorBySelector(DAT_00587110[0]); }
            ListRef list((S_ref *)beBaseInfoDataList_Create(a));
            o = list.p;
            if (o != 0) o->f4 = (int)((int) (o->f4 + 1));
            old = arg1->f40;
            if (old != 0) {
                old->f4 = (int)((int) (old->f4 - 1));
                if (((unsigned long long) ((long long) old->f4 << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(old);
                }
            }
            arg1->f40 = o;
        }
        ci = (beNDMWLoadCtrl2CommonIntf *)igProperty_FindByName(arg1->f40, DAT_00585be0[0], &DAT_00518138[0]);
        switch (st->_st0) {
        case 0:
            break;
        case 1:
            switch (st->_st1) {
            case 0:
                FUN_003f1270(ci->_mcUtilCtrl, 3, 2);
                st->_st1 = (int)((int) (st->_st1 + 1));
                st->_st3 = 0;
                st->_st2 = 0;
                break;
            case 1:
                if ((FUN_003f12f0(ci->_mcUtilCtrl, 3, 2) & 0xFF) == 1) {
                    st->_st0 = 2;
                    st->_st3 = 0;
                    st->_st2 = 0;
                    st->_st1 = 0;
                }
                break;
            }
            break;
        case 2:
            switch (st1(st)) {
            case 0:
                beMessenger_SendNamed(arg0->_messenger, &DAT_00517a48[0], &DAT_00518148[0], 0, &DAT_00517fe0[0]);
                beMessenger_SendNamed(arg0->_messenger, &DAT_00517a48[0], &DAT_00518148[0], 0, &DAT_00518158[0]);
                st->_st1 = (int)((int) (st->_st1 + 1));
                st->_st3 = 0;
                st->_st2 = 0;
                break;
            case 1:
                switch (st->_st2) {
                case 0:
                    beMessenger_SelectReceivers(arg0->_messenger, &DAT_00517a48[0], &DAT_00518148[0], 0);
                    beMessenger_AppendString(arg0->_messenger, &DAT_00518158[0]);
                    beMessenger_DispatchSelected(arg0->_messenger, &DAT_00517af8[0]);
                    if (!(beMessenger_GetBool(arg0->_messenger, 0) & 0xFF)) {
                        if (st->_isTitle == 1) {
                            st->_st2 = (int)((int) (st->_st2 + 1));
                            st->_st3 = 0;
                        } else {
                            st->_st1 = (int)((int) (st->_st1 + 1));
                            st->_st3 = 0;
                            st->_st2 = 0;
                        }
                    }
                    break;
                case 1:
                    beMessenger_SendNamed(arg0->_messenger, &DAT_00517a48[0], &DAT_00518160[0], 0, &DAT_00518170[0]);
                    if ((beMessenger_GetBool(arg0->_messenger, 0) & 0xFF) == 1) {
                        beMessenger_SendNamed(arg0->_messenger, &DAT_00517a48[0], &DAT_00518160[0], 0, &DAT_00518178[0]);
                    }
                    st->_st2 = (int)((int) (st->_st2 + 1));
                    st->_st3 = 0;
                    break;
                case 2:
                    beMessenger_SendNamed(arg0->_messenger, &DAT_00517a48[0], &DAT_00518160[0], 0, &DAT_00518170[0]);
                    if (!(beMessenger_GetBool(arg0->_messenger, 0) & 0xFF)) {
                        st->_st1 = (int)((int) (st->_st1 + 1));
                        st->_st3 = 0;
                        st->_st2 = 0;
                    }
                    break;
                }
                break;
            case 2:
                beMessenger_SendNamed(arg0->_messenger, &DAT_00518188[0], 0, -1, &DAT_00517fe0[0]);
                st->_st1 = (int)((int) (st->_st1 + 1));
                st->_st3 = 0;
                st->_st2 = 0;
                break;
            case 3:
                switch (ci->_intfStat) {
                case 0:
                    FUN_003ecc60(ci, 3, 2);
                    break;
                case 2:
                    break;
                case 3:
                    st->_st1 = (int)((int) (st->_st1 + 1));
                    st->_st3 = 0;
                    st->_st2 = 0;
                    break;
                }
                break;
            case 4:
                switch (*(int *)&st->_st2) {
                case 0:
                    i = 0;
                    do {
                        beNDMWLoadSavePlWork *u;
                        ((beNDMWLoadSavePlWork **)((beNDMWLoadSavePlWorkList *)ci->_flagWork)->_data)[i]->_isClose = 0;
                        u = ((beNDMWLoadSavePlWork **)((beNDMWLoadSavePlWorkList *)ci->_flagWork)->_data)[i];
                        i++;
                        u->_sysStat0 = 2;
                        u->_sysStat3 = 0;
                        u->_sysStat2 = 0;
                        u->_sysStat1 = 0;
                    } while (i < 4);
                    st->_st2 = (int)((int) (st->_st2 + 1));
                    st->_st3 = 0;
                    break;
                case 1:
                    ok = 1;
                    j = 0;
                    fw = (beNDMWLoadSavePlWorkList *)ci->_flagWork;
                    do {
                        if (((beNDMWLoadSavePlWork **)fw->_data)[j]->_isClose != 1) { ok = 0; break; }
                        j++;
                        fw = (beNDMWLoadSavePlWorkList *)ci->_flagWork;
                    } while (j < 4);
                    if ((ok & 0xFF) == 1) {
                        st->_st2 = (int)((int) (st->_st2 + 1));
                        st->_st3 = 0;
                    }
                    break;
                case 2:
                    beMessenger_SendNamed(arg0->_messenger, &DAT_00517a48[0], &DAT_00518160[0], 0, &DAT_00517fe0[0]);
                    beMessenger_SendNamed(arg0->_messenger, &DAT_00517a48[0], &DAT_00518160[0], 0, &DAT_00518198[0]);
                    beMessenger_SendNamed(arg0->_messenger, &DAT_00517a48[0], &DAT_00518148[0], 0, &DAT_005181a8[0]);
                    st->_st2 = (int)((int) (st->_st2 + 1));
                    st->_st3 = 0;
                    break;
                case 3:
                    beMessenger_SendNamed(arg0->_messenger, &DAT_00517a48[0], &DAT_00518148[0], 0, &DAT_00518170[0]);
                    if (!(beMessenger_GetBool(arg0->_messenger, 0) & 0xFF)) {
                        st->_st2 = (int)((int) (st->_st2 + 1));
                        st->_st3 = 0;
                    }
                    break;
                case 4: {
                    int obj;
                    int t1, t2, t3;
                    beMessenger_SendNamed(arg0->_messenger, &DAT_00518188[0], 0, -1, &DAT_005181b8[0]);
                    {
                    cnt = 0;
                    kk = 0;
                    goto cnt_pre;
                cnt_body:
                    if (((beNDMWLoadSavePlWork **)fw2->_data)[kk]->_isRdy == 1) cnt++;
                    kk++;
                cnt_test:
                    if (kk < 4) goto cnt_body;
                    }
                    beMessenger_SendGroup(arg0->_messenger, &DAT_005181c8[0], &DAT_005181d0[0]);
                    obj = beMessenger_GetObject(arg0->_messenger, 0);
                    *(int *)((char *)igProperty_GetRecord(obj, &DAT_005181e0[0]) + 12) = cnt;
                    if (st->_isTitle == 1) {
                        t1 = ci->_difficultMode;
                        *(int *)((char *)igProperty_GetRecord(obj, &DAT_005181e8[0]) + 12) = t1;
                        t2 = arg0->_cameraMode;
                        *(int *)((char *)igProperty_GetRecord(obj, &DAT_005181f8[0]) + 12) = t2;
                        t3 = arg0->_lightMode;
                        *(int *)((char *)igProperty_GetRecord(obj, &DAT_00518208[0]) + 12) = t3;
                        beMessenger_SendGroup(arg0->_messenger, &DAT_00518218[0], &DAT_00518220[0]);
                    }
                    st->_st0 = 3;
                    st->_st3 = 0;
                    st->_st2 = 0;
                    st->_st1 = 0;
                    break;
                }
                }
                break;
            }
            break;
        case 3:
            switch (st->_st1) {
            case 0:
                FUN_003f1380(ci->_mcUtilCtrl, 3);
                st->_st1 = (int)((int) (st->_st1 + 1));
                st->_st3 = 0;
                st->_st2 = 0;
                break;
            case 1:
                if ((FUN_003f13d0(ci->_mcUtilCtrl, 3) & 0xFF) == 1) {
                    if (st->_isTitle == 0) {
                        beMessenger_SelectReceivers(arg0->_messenger, &DAT_00518230[0], 0, -1);
                        beMessenger_AppendInt(arg0->_messenger, 4);
                        beMessenger_DispatchSelected(arg0->_messenger, &DAT_00518240[0]);
                    } else {
                        DAT_0058a1e0[0] = 0;
                        beLua__RunNamedChunk(FUN_00236f80(arg0->_insight, DAT_00589208[0]), &DAT_00518250[0], 0);
                        beMessenger_SelectReceivers(arg0->_messenger, &DAT_00518230[0], 0, -1);
                        beMessenger_AppendInt(arg0->_messenger, 0);
                        beMessenger_DispatchSelected(arg0->_messenger, &DAT_00518240[0]);
                    }
                    beMessenger_SelectGroup(arg0->_messenger, &DAT_00518260[0]);
                    beMessenger_AppendString(arg0->_messenger, &DAT_00518270[0]);
                    beMessenger_DispatchSelected(arg0->_messenger, &DAT_00518280[0]);
                    st->_st0 = (int)((int) (st->_st0 + 1));
                    st->_st3 = 0;
                    st->_st2 = 0;
                    st->_st1 = 0;
                }
                break;
            }
            break;
        }
    }
    return;
cnt_pre:
    fw2 = (beNDMWLoadSavePlWorkList *)ci->_flagWork;
    goto cnt_test;
}
}
