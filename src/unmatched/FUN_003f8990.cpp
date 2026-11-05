#include "dw4/reflected.h"

extern "C" {
void *FUN_003c8c90(int);
int FUN_004482c0(void *, int, int, int);
int Memory_GetAllocatorBySelector(int);
int ObjectList_AppendRetained(void *, void *);
int beDataBase_GetRecordInt(void *, int, int);
void *beMessenger_GetObject(int, int);
int beMessenger_SendNamed(int, void *, void *, int, void *);
int igObject_Destroy(void *);
int igObject_GetAllocator(void *);
void *igProperty_GetRecord(int, void *);
void *igProperty_GetRecordFolder(int, void *);
extern int DAT_004cf120[4];
extern int DAT_00518848[4];
extern int DAT_00518a40[4];
extern int DAT_00519420[4];
extern int DAT_00519430[4];
extern int DAT_00519438[4];
extern int DAT_00587108[4];
extern unsigned char GPR_00554c14;
}
struct RC { int p0; unsigned refs; };
struct Rec { char p[12]; int f12; };
struct RecL { char p[12]; igObjectList *f12; };
struct RecoveryTarget { int word0; int references;
 static void release(RecoveryTarget *object) {
  if(object) {
   --object->references;
   if(((unsigned long long)(long long)object->references & 0x7fffffULL)==0)
    igObject_Destroy(object);
  }
 }
};
template<int I> class RecoveryRef { public:
 void *value;
 RecoveryRef(void *p, bool retain):value(p) { }
 ~RecoveryRef() { RecoveryTarget::release((RecoveryTarget *)value); }
};
extern "C" void FUN_003f8990(beNDMWGameRam *arg0, int arg1);
extern "C" void FUN_003f8990(beNDMWGameRam *arg0, int arg1) {
    igObjectList *l;
    int n;
    int al;
    void *hv;
    int j;
    RC *t;
    int i;
    int n3;
    RC *o;
    int *pt;
    int i3;
    int obj;
    int s6;
    obj = ((int *)((igObjectList *)arg0->_playerDataListList)->_data)[arg1];
    l = ((RecL *)igProperty_GetRecordFolder(obj, &DAT_00518a40[0]))->f12;
    s6 = ((Rec *)igProperty_GetRecord(obj, &DAT_00518848[0]))->f12;
    n = l->_count;
    i = 0;
    if (0 < n) {
        do {
            t = ((RC **)l->_data)[i];
            if (t != 0) {
                t->refs--;
                if (!(t->refs & 0x7fffff)) igObject_Destroy(t);
            }
            i += 1;
        } while (i < n);
    }
    n3 = l->_count;
    for (i3 = 0; i3 < n3; i3++) {
        ((int *)l->_data)[i3] = 0;
    }
    l->_count = 0;
    j = 0;
    pt = &DAT_004cf120[0];
    do {
        al = igObject_GetAllocator(arg0);
        al = (GPR_00554c14 != 0) ? al : Memory_GetAllocatorBySelector(DAT_00587108[0]);
        {
        RecoveryRef<1> sp8C(FUN_003c8c90(al), false);
        hv = sp8C.value;
        if (arg0->_dBShinka == 0) {
            beMessenger_SendNamed(arg0->_messenger, &DAT_00519438[0], &DAT_00519430[0], 0, &DAT_00519420[0]);
            o = (RC *)beMessenger_GetObject(arg0->_messenger, 0);
            if (o != 0) {
                o->refs++;
            }
            t = (RC *)arg0->_dBShinka;
            if (t != 0) {
                t->refs--;
                if (!(t->refs & 0x7fffff)) igObject_Destroy(t);
            }
            arg0->_dBShinka = (int)o;
        }
        FUN_004482c0(hv, beDataBase_GetRecordInt((void *)arg0->_dBShinka, s6, *pt), 0, 0);
        ObjectList_AppendRetained(l, sp8C.value);
        }
        j += 1;
        pt += 1;
    } while (j < 3);
}
