#include "dw4/reflected.h"
extern "C" {
void igObject_Destroy(igObject *);
igObject *beBaseInfoDataList_Create(int);
igObject *FUN_003bfc80(int);
int Memory_GetAllocatorBySelector(...);
int igObject_GetAllocator(...);
igIntList *FUN_002caa70(int);
void List_Reserve(...);
void List_Resize(...);
void memset(...);
int beMessenger_GetVec3Count(...);
int beMessenger_GetMatrixCount(...);
void igMatrix44f_SetIdentity(...);
void beMessenger_PushArgContext(...);
void beMessenger_PopArgContext(...);
void beMessenger_SelectGroup(...);
void beMessenger_SelectReceivers(...);
void beMessenger_AppendInt(...);
void beMessenger_AppendString(...);
void beMessenger_AppendMatrix(...);
void beMessenger_AppendFloat(int, float);
void beMessenger_DispatchSelected(...);
void beMessenger_GetMatrix(...);
void Matrix44_Copy(...);
int beMessenger_GetObject(...);
void beMessenger_SendNamed(...);
void beMessenger_SendDelayedNamed(...);
void FUN_00396740(...);
void StringChunk_ReleaseHeader(...);
int strcmp(...);
struct PropertyRecord { char p[20]; beNDMWMdlPlayerInfoWork *value; };
PropertyRecord *igProperty_FindByName(...);
struct IntRec { char p[12]; int f12; };
struct ByteRec { char p[12]; unsigned char f12; };
struct ArrRec { char p[12]; igIntList *f12; };
struct BArrRec { char p[12]; igUnsignedCharList *f12; };
struct SListRec { char p[12]; igStringObjList *f12; };
IntRec *igProperty_GetRecord(...);
ByteRec *igProperty_GetRecordByte(...);
ArrRec *FUN_003a9250(...);
BArrRec *igProperty_GetRecordArray(...);
SListRec *FUN_003a9310(...);
extern int DAT_004cc7b8[4];
extern int DAT_004cc7c0[4];
extern int DAT_004cc7d0[4];
extern int DAT_004cc7e0[4];
extern int DAT_004cc800[4];
extern int DAT_004e0858[4];
extern int DAT_00516038[4];
extern int DAT_00516110[4];
extern int DAT_00516260[4];
extern int DAT_00516368[4];
extern int DAT_00516378[4];
extern int DAT_00516388[4];
extern int DAT_00516390[4];
extern int DAT_005163a0[4];
extern int DAT_005163a8[4];
extern int DAT_005163b0[4];
extern int DAT_005163b8[4];
extern int DAT_005163c0[4];
extern int DAT_005163c8[4];
extern int DAT_005163d8[4];
extern int DAT_005163e0[4];
extern int DAT_005163f0[4];
extern int DAT_00516400[4];
extern int DAT_00516410[4];
extern int DAT_00516420[4];
extern int DAT_00516430[4];
extern int DAT_00516440[4];
extern int DAT_00516448[4];
extern int DAT_00516450[4];
extern int DAT_00516460[4];
extern int DAT_00516470[4];
extern int DAT_00516478[4];
extern int DAT_00516488[4];
extern int DAT_00516490[4];
extern int DAT_00516498[4];
extern int DAT_005164a0[4];
extern int DAT_00585be0[4];
extern int DAT_00587110[4];
extern unsigned char GPR_00554c14;
extern unsigned char GPR_005549e0;
}
struct ReleaseRefInline { static inline void go(igObject *object) {
    if (object) {
        --object->_refCount;
        if (((unsigned long long)(long long)object->_refCount & 0x7fffffULL) == 0)
            igObject_Destroy(object);
    }
} };
/* Owning stack reference to the slot's new data list; released on scope exit (reference count in
 * the low 23 bits of _refCount). */
template <class T> class igSmartPointer {
public:
    T *p;
    igSmartPointer(T *o) : p(o) {}
    ~igSmartPointer() { T *o = p; if (o != 0) { --o->_refCount; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
};
/* Owning stack reference to the new player info work; released on scope exit. */
class InfoWorkRef {
public:
    igObject *p;
    InfoWorkRef(igObject *o) : p(o) {}
    ~InfoWorkRef() { igObject *o = p; if (o != 0) { --o->_refCount; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
};
/* Owning stack reference to the new turn-attack timer list; released on scope exit. */
class IntListRef {
public:
    igIntList *p;
    IntListRef(igIntList *l) : p(l) {}
    ~IntListRef() { igIntList *o = p; if (o != 0) { --o->_refCount; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy((igObject *)o); } }
};
/* Owning stack reference to a pooled string token (reference count at p[-1], chunk header at
 * p[-2]); releases the token on scope exit. */
class StringRef {
public:
    int *p;
    StringRef(int *s) : p(s) {}
    ~StringRef() { if (p) { int *h = (int *)p - 2; int r = ((int *)p)[-1] - 1; ((int *)p)[-1] = r; if (r == 0) StringChunk_ReleaseHeader(*h, h); } }
};
/* The retained copy of a list entry is returned through a hidden return pointer. */
extern "C" StringRef StringList_CopyRetained(igStringObjList *, int);
struct Slot { static inline void setDataList(beBaseInfoRam *ram, const igSmartPointer<igObject> &r) {
    igObject *t = r.p;
    if (t != 0) t->_refCount = t->_refCount + 1;
    ReleaseRefInline::go((igObject *)ram->_dataList);
    ram->_dataList = (int)t;
} };
struct ParentInfoRef { char header[8]; int *name; };
struct SystemObjectView { char p[56]; int f56; };
extern "C" void Gap__Bec__beNDMWMdlPlayer__vfunc_36(beNDMWMdlPlayer *arg0, beBaseInfoRam *arg1);
void Gap__Bec__beNDMWMdlPlayer__vfunc_36(beNDMWMdlPlayer *arg0, beBaseInfoRam *arg1) {
    float spC0[16];
    float sp80[16];
    ParentInfoRef *s6;
    PropertyRecord *s3;
    beNDMWMdlPlayerInfoWork *s5;
    igObject *s0o;
    igIntList *l0;
    s6 = (ParentInfoRef *)arg1->_parentInfo;
    if (arg1->_dataList == 0) {
        int alloc = igObject_GetAllocator(arg1);
        int a;
        if (GPR_00554c14 != 0) {
            a = alloc;
        } else {
            a = Memory_GetAllocatorBySelector(DAT_00587110[0]);
        }
        igObject *created = beBaseInfoDataList_Create(a);
        /* matching construct: the new list is a temporary bound to the setter's reference parameter (it
         * takes the stack slot below the named references, as retail's +0x100 does) */
        Slot::setDataList(arg1, igSmartPointer<igObject>(created));
    }
    s3 = igProperty_FindByName((void *)arg1->_dataList, DAT_00585be0[0], DAT_00516110);
    {
        int alloc = igObject_GetAllocator(arg0);
        int a;
        if (GPR_00554c14 != 0) {
            a = alloc;
        } else {
            a = Memory_GetAllocatorBySelector(DAT_00587110[0]);
        }
        InfoWorkRef work(FUN_003bfc80(a));
        s0o = work.p;
        if (s0o != 0) {
            s0o->_refCount++;
        }
        ReleaseRefInline::go((igObject *)s3->value);
        s3->value = (beNDMWMdlPlayerInfoWork *)s0o;
        s5 = (beNDMWMdlPlayerInfoWork *)work.p;
        s5->_isPlayer = 1;
        s5->_directionLimiter[0] = 0.0f;
        s5->_directionLimiter[1] = 7.0f;
        s5->_directionLimiter[2] = 0.0f;
        {
            int alloc = igObject_GetAllocator(arg0);
            int a;
            if (GPR_00554c14 != 0) {
                a = alloc;
            } else {
                a = Memory_GetAllocatorBySelector(DAT_00587110[0]);
            }
            IntListRef timer(FUN_002caa70(a));
            {
                igIntList *t = timer.p;
                if (t->_count < 9) {
                    List_Reserve(t, 8, 4);
                }
            }
            {
                igIntList *t = timer.p;
                if (t->_capacity >= 8) {
                    t->_count = 8;
                } else {
                    List_Resize(t, 8, 4);
                }
            }
            l0 = timer.p;
            if (l0->_count != 0) {
                memset(l0->_data, 0, l0->_count * 4);
            }
            l0 = timer.p;
            if (l0 != 0) {
                l0->_refCount++;
            }
            ReleaseRefInline::go((igObject *)s5->_turnAtkTimer);
            s5->_turnAtkTimer = (int)l0;
        }
    }
    if (beMessenger_GetVec3Count(arg0->_messenger) == 0 && beMessenger_GetMatrixCount(arg0->_messenger) == 0) {
        igMatrix44f_SetIdentity(spC0);
        beMessenger_PushArgContext(arg0->_messenger);
        beMessenger_SelectGroup(arg0->_messenger, DAT_00516368);
        beMessenger_AppendInt(arg0->_messenger, 0);
        beMessenger_AppendInt(arg0->_messenger, arg1->_ramNo);
        beMessenger_DispatchSelected(arg0->_messenger, DAT_00516378);
        if (beMessenger_GetMatrixCount(arg0->_messenger) != 0) {
            beMessenger_GetMatrix(sp80, arg0->_messenger, 0);
            Matrix44_Copy(spC0, sp80);
        }
        beMessenger_PopArgContext(arg0->_messenger);
        beMessenger_AppendMatrix(arg0->_messenger, spC0);
    }
    FUN_00396740(arg0, arg1);
    beMessenger_SelectGroup(arg0->_messenger, DAT_00516388);
    beMessenger_AppendInt(arg0->_messenger, arg1->_ramNo);
    beMessenger_DispatchSelected(arg0->_messenger, DAT_00516390);
    int obj = beMessenger_GetObject(arg0->_messenger, 0);
    {
        IntRec *r3 = igProperty_GetRecord(obj, DAT_005163a0);
        if (r3 != 0) ((igObject *)r3)->_refCount++;
        ReleaseRefInline::go((igObject *)s5->_hp);
        s5->_hp = (int)r3;
    }
    {
        IntRec *r3 = igProperty_GetRecord(obj, DAT_005163a8);
        if (r3 != 0) ((igObject *)r3)->_refCount++;
        ReleaseRefInline::go((igObject *)s5->_mHp);
        s5->_mHp = (int)r3;
    }
    if (((IntRec *)s5->_hp)->f12 == 0) {
        int t = igProperty_GetRecord(obj, DAT_005163a8)->f12;
        igProperty_GetRecord(obj, DAT_005163a0)->f12 = t;
        t = igProperty_GetRecord(obj, DAT_005163b0)->f12;
        igProperty_GetRecord(obj, DAT_005163b8)->f12 = t;
    }
    {
        int i = 0, off = 0;
        do {
            igIntList *v = FUN_003a9250(obj, DAT_005163c0)->f12;
            if (v->_count != 0 && i >= 0 && i < v->_count) {
                *(int *)(v->_data + off) /* matching construct: byte-offset element write; indexing by i or off/4 changes the induction variable */ = DAT_004cc7b8[0];
            }
            i += 1;
            off += 4;
        } while (i < 7);
    }
    {
        int i = 0, off = 0;
        do {
            igIntList *v = FUN_003a9250(obj, DAT_005163c8)->f12;
            if (v->_count != 0 && i >= 0 && i < v->_count) {
                *(int *)(v->_data + off) /* matching construct: byte-offset element write; indexing by i or off/4 changes the induction variable */ = DAT_004cc7c0[0];
            }
            i += 1;
            off += 4;
        } while (i < 6);
    }
    if (igProperty_GetRecordByte(obj, DAT_005163d8)->f12 == 0) {
        int *a1;
        beMessenger_SelectGroup(arg0->_messenger, DAT_00516388);
        beMessenger_AppendInt(arg0->_messenger, arg1->_ramNo);
        a1 = s6->name;
        a1 = a1 ? a1 : DAT_004e0858;
        beMessenger_AppendString(arg0->_messenger, a1);
        beMessenger_AppendString(arg0->_messenger, DAT_004cc7d0[arg1->_ramNo]);
        beMessenger_DispatchSelected(arg0->_messenger, DAT_005163e0);
        igUnsignedCharList *bv = igProperty_GetRecordArray(obj, DAT_005163f0)->f12;
        int n = bv->_count;
        unsigned char *d = (unsigned char *)bv->_data;
        for (int i = 0; i < n; i++) {
            d[i] = GPR_005549e0;
        }
    }
    if (FUN_003a9310(obj, DAT_00516400)->f12->_count != 0) {
        StringRef name = StringList_CopyRetained(FUN_003a9310(obj, DAT_00516400)->f12, 0);
        beMessenger_SendDelayedNamed(arg0->_messenger, DAT_00516410, name.p, arg1->_ramNo, DAT_00516260, 1);
    }
    beMessenger_SelectGroup(arg0->_messenger, DAT_00516388);
    beMessenger_AppendInt(arg0->_messenger, arg1->_ramNo);
    beMessenger_DispatchSelected(arg0->_messenger, DAT_00516420);
    beMessenger_SelectReceivers(arg0->_messenger, DAT_00516430, DAT_00516440, arg1->_ramNo);
    beMessenger_AppendInt(arg0->_messenger, igProperty_GetRecord(obj, DAT_00516448)->f12);
    beMessenger_DispatchSelected(arg0->_messenger, DAT_00516450);
    beMessenger_SelectReceivers(arg0->_messenger, DAT_00516460, DAT_00516470, arg1->_ramNo);
    {
        int d = igProperty_GetRecord(obj, DAT_005163a8)->f12;
        beMessenger_AppendFloat(arg0->_messenger, (100.0f * (float)igProperty_GetRecord(obj, DAT_005163a0)->f12) / (float)d);
    }
    beMessenger_DispatchSelected(arg0->_messenger, DAT_00516478);
    beMessenger_SelectReceivers(arg0->_messenger, DAT_00516430, DAT_00516488, arg1->_ramNo);
    beMessenger_AppendInt(arg0->_messenger, igProperty_GetRecord(obj, DAT_005163a0)->f12);
    beMessenger_DispatchSelected(arg0->_messenger, DAT_00516450);
    beMessenger_SelectReceivers(arg0->_messenger, DAT_00516460, DAT_00516490, arg1->_ramNo);
    {
        int n = igProperty_GetRecord(obj, DAT_005163b8)->f12;
        IntRec *r = igProperty_GetRecord(obj, DAT_005163b0);
        beMessenger_AppendFloat(arg0->_messenger, (float)(n * 100 / r->f12));
    }
    beMessenger_DispatchSelected(arg0->_messenger, DAT_00516478);
    beMessenger_SelectReceivers(arg0->_messenger, DAT_00516430, DAT_00516498, arg1->_ramNo);
    beMessenger_AppendInt(arg0->_messenger, igProperty_GetRecord(obj, DAT_005163b8)->f12);
    beMessenger_DispatchSelected(arg0->_messenger, DAT_00516450);
    int s4 = ((SystemObjectView *)arg0->_system)->f56;
    for (int j = 0; j < 5; j++) {
        if (strcmp(((int *)DAT_004cc7e0)[j], s4) == 0) {
            beMessenger_SendNamed(arg0->_messenger, DAT_00516038, 0, arg1->_ramNo, DAT_005164a0);
            break;
        }
    }
    for (int k = 0; k < 4; k++) {
        if (strcmp(((int *)DAT_004cc800)[k], s4) == 0) {
            s5->_isMainLobby = 1;
            break;
        }
    }
}
