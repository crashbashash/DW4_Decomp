/* Several spellings are kept on purpose for the register assignment: the per-call locals of the
 * four list appends (the inlined AppendBool/AppendInt bodies, the int one re-reading the count
 * through a volatile cast), and the first loop, which reads the element once into `have` and once
 * more inline (the second read keeps the data pointer load inside the loop and settles the
 * temporary registers). */
#include "dw4/reflected.h"

typedef struct RefObj { int w0; int ref; } RefObj;
class MsgReceiver;

/* matching construct: dummy-virtual class so r->Check / r->Send compile to vtable slots 34 / 33 (beBaseInfoManager vtable) */
class MsgReceiver {
public:
    virtual void vfunc_00();
    virtual void vfunc_01();
    virtual void vfunc_02();
    virtual void vfunc_03();
    virtual void vfunc_04();
    virtual void vfunc_05();
    virtual void vfunc_06();
    virtual void vfunc_07();
    virtual void vfunc_08();
    virtual void vfunc_09();
    virtual void vfunc_10();
    virtual void vfunc_11();
    virtual void vfunc_12();
    virtual void vfunc_13();
    virtual void vfunc_14();
    virtual void vfunc_15();
    virtual void vfunc_16();
    virtual void vfunc_17();
    virtual void vfunc_18();
    virtual void vfunc_19();
    virtual void vfunc_20();
    virtual void vfunc_21();
    virtual void vfunc_22();
    virtual void vfunc_23();
    virtual void vfunc_24();
    virtual void vfunc_25();
    virtual void vfunc_26();
    virtual void vfunc_27();
    virtual void vfunc_28();
    virtual void vfunc_29();
    virtual void vfunc_30();
    virtual void vfunc_31();
    virtual void vfunc_32();
    virtual void Send(beBaseInfoRam *obj, int name);
    virtual unsigned char Check(beBaseInfoRam *obj, beMessengerWork *work);
};

extern "C" {
int FUN_002eb010(int);
int StringPool_Construct(int);
int StringPool_Intern(int, int);
void StringChunk_ReleaseHeader(int, void *);
int igStrCmp(int, const void *);
void List_Resize(void *, int, int);
void ObjectList_AppendRetained(void *, void *);
void igObject_Destroy(void *);
extern int DAT_00586f20[4];
extern char DAT_0050ee10[], DAT_0050ee18[];
extern int DAT_004c8f88[4];
extern unsigned char GPR_005549d4, GPR_005549d8;
}

/* matching construct: RAII holder reproduces the retail inline retain/release and the emitted destructor at 0x0038e530 (its mangled name pins the class name ObjRef) */
class ObjRef {
public:
    RefObj *value;
    ObjRef(RefObj *p) : value(p) { if (value) ++value->ref; }
    void operator=(RefObj *p) {
        RefObj *object;
        if (p) ++p->ref;
        object = value;
        if (object) {
            --object->ref;
            if (((unsigned long long)(long long)object->ref & 0x7fffffULL) == 0) igObject_Destroy(object);
        }
        value = p;
    }
    ~ObjRef() {
        RefObj *object = value;
        if (object) {
            --object->ref;
            if (((unsigned long long)(long long)object->ref & 0x7fffffULL) == 0) igObject_Destroy(object);
        }
    }
};

extern "C"
void beMessenger_DispatchSelected(beMessenger *self, int name)
{
    int n;
    int alloc;
    igIntList *il;
    int *header;
    int i;
    int str;
    int i3;
    int count;
    igBoolList *bl;
    int i2;
    beMessengerWork *work;
    int old;
    int refs;
    int matches;

    work = (beMessengerWork *)((int *)((beMessengerWorkList *)self->_workStack)->_data)[0];
    if (DAT_00586f20[0] == 0) {
        alloc = FUN_002eb010(16);
        if (alloc) alloc = StringPool_Construct(alloc);
        DAT_00586f20[0] = alloc;
    }
    str = StringPool_Intern(DAT_00586f20[0], name);
    old = work->_message;
    if (old) {
        header = (int *)(old - 8);
        refs = *(int *)(old - 4) - 1;
        *(int *)(old - 4) = refs;
        if (!refs) StringChunk_ReleaseHeader(*header, header);
    }
    work->_message = str;
    igObjectList *fl = (igObjectList *)work->_findRamList;
    count = fl->_count;
    if (igStrCmp(name, DAT_0050ee10) == 0) {
        matches = 0;
        for (i = 0; i < count; i++) {
            igIntList *list = (igIntList *)work->_findRamNoList; int have = ((int *)list->_data)[i]; if (work->_ramNo == -1 || *(int *)(list->_data + i * 4) /* matching construct: byte-offset element read keeps the data load inside the loop */ == -1 || have == work->_ramNo) matches++;
        }
        {
            if (matches) {
                igBoolList *bla = (igBoolList *)((beMessengerArgData *)self->_argData)->_boolList;
                int na = bla->_count;
                if (na < bla->_capacity) bla->_count = na + 1; else List_Resize(bla, na + 1, 1);
                ((char *)bla->_data)[na] = GPR_005549d4;
                il = (igIntList *)((beMessengerArgData *)self->_argData)->_intList;
                n = il->_count;
                if (n < il->_capacity) il->_count = *(volatile int *)&il->_count /* matching construct: volatile re-read of the count */ + 1; else List_Resize(il, n + 1, 4);
                ((int *)il->_data)[n] = matches;
            } else {
                igBoolList *blc = (igBoolList *)((beMessengerArgData *)self->_argData)->_boolList;
                n = blc->_count;
                if (n < blc->_capacity) blc->_count = n + 1; else List_Resize(blc, n + 1, 1);
                ((char *)blc->_data)[n] = GPR_005549d8;
                il = (igIntList *)((beMessengerArgData *)self->_argData)->_intList;
                int nd = il->_count;
                if (nd < il->_capacity) il->_count = *(volatile int *)&il->_count /* matching construct: volatile re-read of the count */ + 1; else List_Resize(il, nd + 1, 4);
                ((int *)il->_data)[nd] = DAT_004c8f88[0];
            }
        }
    } else if (igStrCmp(name, DAT_0050ee18) == 0) {
        ObjRef held(0);
        for (i2 = 0; i2 < count; i2++) {
            igObjectList *list = (igObjectList *)work->_findRamList;
            beBaseInfoRam *obj = ((beBaseInfoRam **)list->_data)[i2];
            if (((beBaseInfoRam **)list->_data)[i2]->_isRun == 0) {
                held = (RefObj *)obj;
                break;
            }
        }
        if (held.value) ObjectList_AppendRetained((void *)((beMessengerArgData *)self->_argData)->_objectList, held.value);
    } else {
        for (i3 = 0; i3 < count; i3++) {
            int sid = work->_ramNo;
            beBaseInfoRam *obj = ((beBaseInfoRam **)((igObjectList *)work->_findRamList)->_data)[i3];
            MsgReceiver *r;
            if (sid == -2) {
                if (obj->_isRun != 0) continue;
            } else {
                int have = ((int *)((igIntList *)work->_findRamNoList)->_data)[i3];
                if (((beMessengerArgData *)self->_argData)->_isRunCheck == 1 && obj->_isRun == 0) continue;
                if (!(sid == -1 || have == -1 || have == sid)) continue;
            }
            r = (MsgReceiver *)obj->_parentManager;
            if (!(r->Check(obj, work) & 0xff)) r->Send(obj, name);
            if (work->_ramNo == -2) break;
        }
    }
}
