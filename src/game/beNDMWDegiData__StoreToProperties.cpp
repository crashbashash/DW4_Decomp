/* Copy a saved-record block (arg0->saved) into the property tree arg1.
 * Matching constructs: the held item/chunk objects are RAII holders (ChunkRef, ItemRef) so the unwind
 * table names the right destructors; the sp184 slot is volatile so each use reloads from the stack;
 * the list-empty test reads `count` through a volatile int so the loop-bound load stays separate. */
#include "dw4/reflected.h"
extern "C" {
struct Obj { int word0; int references; };
extern "C" void igObject_Destroy(Obj *);
struct H {
    static inline void Rel(Obj *o) {
        if (o) {
            --o->references;
            if (((unsigned long long)(long long)o->references & 0x7fffffULL) == 0)
                igObject_Destroy(o);
        }
    }
};
/* matching construct: one RAII releasing holder per retail destructor copy; the cleanup table at 0x544c5c names 0x3832d0 (chunk buffer) and 0x1363f0 (list element / created item) */
struct ChunkRef { Obj *p; ChunkRef(Obj *x) : p(x) {} ~ChunkRef() { Obj *o = p; if (o != 0) { --o->references; if (((unsigned long long)(long long)o->references & 0x7fffffULL) == 0) igObject_Destroy(o); } } };
struct ItemRef { Obj *p; ItemRef() {} ItemRef(Obj *x) : p(x) {} ~ItemRef() { Obj *o = p; if (o != 0) { --o->references; if (((unsigned long long)(long long)o->references & 0x7fffffULL) == 0) igObject_Destroy(o); } } };
struct Lst {
    static inline void ReleaseAll(igObjectList *l) {
        int n = l->_count;
        int i;
        for (i = 0; i < n; i++)
            H::Rel(((Obj **)l->_data)[i]);
    }
    static inline void ZeroAll(igObjectList *l) {
        int m = l->_count;
        int j;
        for (j = 0; j < m; j++)
            ((Obj **)l->_data)[j] = 0;
    }
    static inline void Clear(igObjectList *l) {
        if (*(volatile int *)&l->_count > 0) {
            ReleaseAll(l);
            ZeroAll(l);
            l->_count = 0;
        }
    }
};
struct Chunk { int word0; int references; int count; unsigned short *chars; };
struct RecByte { int w0, w1, w2; unsigned char value; };
struct RecInt { int w0, w1, w2; int value; };
struct RecStr { int w0, w1, w2; char *value; };
struct RecLst { int w0, w1, w2; igObjectList *value; };
struct RecArr8 { int w0, w1, w2; igUnsignedCharList *value; };
struct RecArr32 { int w0, w1, w2; igIntList *value; };
struct Saved {
    unsigned char b0; char pad1[3];
    int i4;
    char name[32];
    struct Str16 { unsigned short sel; unsigned short chars[15]; } nm;
    int i72, i76, i80, i84, i88, i92, i96;
    int l0[36];
    int l1[12];
    unsigned char a0[50]; char pad3[2];
    int l2[96];
    int i728;
    int l3[3];
    int l4[5];
    int i764;
    int l5[5];
    int i788;
    unsigned char a1[1024];
    unsigned char a2[12];
    int a3[16];
    unsigned char a4[16];
    int a5[16];
    int a6[16];
    int a7[144];
    int a8[176];
};
struct Host { int w0[7]; Saved *saved; int w1[5]; int dword52; };
void igObject_Destroy(Obj *);
int Memory_GetAllocatorBySelector(...);
int igObject_GetAllocator(...);
RecByte *igProperty_GetRecordByte(void *, int *);
RecInt *igProperty_GetRecord(void *, int *);
RecStr *FUN_003a92e0(void *, int *);
RecLst *igProperty_GetRecordFolder(void *, int *);
RecArr8 *igProperty_GetRecordArray(void *, int *);
RecArr32 *FUN_003a9250(void *, int *);
void *FUN_002eb010(int);
void *StringPool_Construct(void *);
char *StringPool_Intern(void *, char *);
void StringChunk_ReleaseHeader(int, void *);
Chunk *FUN_003614f0(int);
void beUnicodeObj_AllocateBuffer(Chunk *, int);
void FUN_00382eb0(void *, int, int);
int ObjectList_AppendRetained(...);
ItemRef FUN_003ef1e0(void *, int);
extern void *DAT_00586f20[4];
extern int DAT_00587108[4];
extern unsigned char GPR_00554c14;
extern int DAT_00517e58[4];
extern int DAT_00517e60[4];
extern int DAT_00517e68[4];
extern int DAT_00517e70[4];
extern int DAT_00517e78[4];
extern int DAT_00517e80[4];
extern int DAT_00517e88[4];
extern int DAT_00517e90[4];
extern int DAT_00517ea0[4];
extern int DAT_00517eb0[4];
extern int DAT_00517eb8[4];
extern int DAT_00517ec0[4];
extern int DAT_00517ed0[4];
extern int DAT_00517ee0[4];
extern int DAT_00517ef0[4];
extern int DAT_00517f00[4];
extern int DAT_00517f08[4];
extern int DAT_00517f18[4];
extern int DAT_00517f28[4];
extern int DAT_00517f38[4];
extern int DAT_00517f48[4];
extern int DAT_00517f50[4];
extern int DAT_00517f60[4];
extern int DAT_00517f70[4];
extern int DAT_00517f80[4];
extern int DAT_00517f90[4];
extern int DAT_00517fa0[4];
extern int DAT_00517fb0[4];
extern int DAT_00517fc0[4];
void beNDMWDegiData__StoreToProperties(Host *arg0, void *arg1, int arg2);
}
extern "C" void beNDMWDegiData__StoreToProperties(Host *arg0, void *arg1, int arg2) {
    Saved *s = arg0->saved;
    igProperty_GetRecordByte(arg1, DAT_00517e58)->value = s->b0;
    igProperty_GetRecord(arg1, DAT_00517e60)->value = s->i4;
    igProperty_GetRecord(arg1, DAT_00517e68)->value = s->i72;
    igProperty_GetRecord(arg1, DAT_00517e70)->value = s->i76;
    igProperty_GetRecord(arg1, DAT_00517e78)->value = s->i80;
    igProperty_GetRecord(arg1, DAT_00517e80)->value = s->i84;
    igProperty_GetRecord(arg1, DAT_00517e88)->value = s->i88;
    char *nm = s->name;
    RecStr *rs = FUN_003a92e0(arg1, DAT_00517ea0);
    if (DAT_00586f20[0] == 0) {
        void *p = FUN_002eb010(16);
        if (p != 0)
            p = StringPool_Construct(p);
        DAT_00586f20[0] = p;
    }
    char *interned = StringPool_Intern(DAT_00586f20[0], nm);
    char *old = rs->value;
    if (old != 0) {
        int *hdr = (int *)old - 2;
        int rc = hdr[1] - 1;
        hdr[1] = rc;
        if (rc == 0)
            StringChunk_ReleaseHeader(hdr[0], hdr);
    }
    rs->value = interned;
    igObjectList *l0 = igProperty_GetRecordFolder(arg1, DAT_00517e90)->value;
    Lst::Clear(l0);
    int alloc = igObject_GetAllocator(arg0);
    int a;
    if (GPR_00554c14 != 0)
        a = alloc;
    else
        a = Memory_GetAllocatorBySelector(DAT_00587108[0]);
    {
    ChunkRef sp188((Obj *)FUN_003614f0(a));
    Obj * volatile sp184;
    beUnicodeObj_AllocateBuffer((Chunk *)sp188.p, 8);
    unsigned short *dst = ((Chunk *)sp188.p)->chars;
    Saved::Str16 *q = &s->nm;
    if (q->sel != 0xffff) {
        FUN_00382eb0((void *)&sp184, arg2, arg0->dword52);
        unsigned short *src = ((Chunk *)sp184)->chars;
        int ia = 0;
        for (; ia < 8; ia++) {
            dst[ia] = src[ia];
            if (src[ia] == 0)
                break;
        }
        for (; ia < 8; ia++)
            dst[ia] = 0;
        { Obj *r = sp184; H::Rel(r); }
    } else {
        int ib = 0;
        for (; ib < 8; ib++) {
            dst[ib] = q->chars[ib];
            if (dst[ib] == 0)
                break;
        }
        for (; ib < 8; ib++)
            dst[ib] = 0;
    }
    ObjectList_AppendRetained(l0, sp188.p);
    }
    igProperty_GetRecord(arg1, DAT_00517eb0)->value = s->i92;
    igProperty_GetRecord(arg1, DAT_00517eb8)->value = s->i96;
    igObjectList *l1 = igProperty_GetRecordFolder(arg1, DAT_00517ec0)->value;
    Lst::Clear(l1);
    for (int i1 = 0; i1 < 36; i1++) {
        int id = s->l0[i1];
        if (id == -1)
            break;
        ItemRef sp180 = FUN_003ef1e0(arg0, id);
        ObjectList_AppendRetained(l1, sp180.p);
    }
    igObjectList *l2 = igProperty_GetRecordFolder(arg1, DAT_00517ed0)->value;
    Lst::Clear(l2);
    for (int i2 = 0; i2 < 12; i2++) {
        int id = s->l1[i2];
        if (id == -1)
            break;
        ItemRef sp176 = FUN_003ef1e0(arg0, id);
        ObjectList_AppendRetained(l2, sp176.p);
    }
    igUnsignedCharList *a0 = igProperty_GetRecordArray(arg1, DAT_00517ee0)->value;
    for (int i3 = 0; i3 < 50; i3++) {
        unsigned char v = s->a0[i3];
        if (a0->_count != 0 && i3 >= 0 && i3 < a0->_count)
            ((unsigned char *)a0->_data)[i3] = v;
    }
    igObjectList *l3 = igProperty_GetRecordFolder(arg1, DAT_00517ef0)->value;
    Lst::Clear(l3);
    for (int i4 = 0; i4 < 96; i4++) {
        int id = s->l2[i4];
        if (id == -1)
            break;
        ItemRef sp172 = FUN_003ef1e0(arg0, id);
        ObjectList_AppendRetained(l3, sp172.p);
    }
    igProperty_GetRecord(arg1, DAT_00517f00)->value = s->i728;
    igObjectList *l4 = igProperty_GetRecordFolder(arg1, DAT_00517f08)->value;
    Lst::Clear(l4);
    for (int i5 = 0; i5 < 3; i5++) {
        int id = s->l3[i5];
        if (id != -1) {
            ItemRef sp168(((Obj **)igProperty_GetRecordFolder(arg1, DAT_00517ec0)->value->_data)[id]);
            if (sp168.p)
                sp168.p->references++;
            ObjectList_AppendRetained(l4, sp168.p);
        } else {
            ObjectList_AppendRetained(l4, 0);
        }
    }
    igObjectList *l5 = igProperty_GetRecordFolder(arg1, DAT_00517f18)->value;
    Lst::Clear(l5);
    for (int i6 = 0; i6 < 5; i6++) {
        int id = s->l4[i6];
        if (id != -1) {
            ItemRef sp164(((Obj **)igProperty_GetRecordFolder(arg1, DAT_00517ec0)->value->_data)[id]);
            if (sp164.p)
                sp164.p->references++;
            ObjectList_AppendRetained(l5, sp164.p);
        } else {
            ObjectList_AppendRetained(l5, 0);
        }
    }
    igObjectList *l6 = igProperty_GetRecordFolder(arg1, DAT_00517f28)->value;
    Lst::Clear(l6);
    {
        int id = s->i764;
        if (id != -1) {
            ItemRef sp160(((Obj **)igProperty_GetRecordFolder(arg1, DAT_00517ec0)->value->_data)[id]);
            if (sp160.p)
                sp160.p->references++;
            ObjectList_AppendRetained(l6, sp160.p);
        } else {
            ObjectList_AppendRetained(l6, 0);
        }
    }
    igObjectList *l7 = igProperty_GetRecordFolder(arg1, DAT_00517f38)->value;
    Lst::Clear(l7);
    for (int i7 = 0; i7 < 5; i7++) {
        int id = s->l5[i7];
        if (id != -1) {
            ItemRef sp156(((Obj **)igProperty_GetRecordFolder(arg1, DAT_00517ec0)->value->_data)[id]);
            if (sp156.p)
                sp156.p->references++;
            ObjectList_AppendRetained(l7, sp156.p);
        } else {
            ObjectList_AppendRetained(l7, 0);
        }
    }
    igObjectList *l8 = igProperty_GetRecordFolder(arg1, DAT_00517f48)->value;
    int id8 = s->i788;
    Lst::Clear(l8);
    if (id8 != -1) {
        ItemRef sp152(((Obj **)igProperty_GetRecordFolder(arg1, DAT_00517ec0)->value->_data)[id8]);
        if (sp152.p)
            sp152.p->references++;
        ObjectList_AppendRetained(l8, sp152.p);
    } else {
        ObjectList_AppendRetained(l8, 0);
    }
    igUnsignedCharList *a1 = igProperty_GetRecordArray(arg1, DAT_00517f50)->value;
    for (int i8 = 0; i8 < 1024; i8++) {
        unsigned char v = s->a1[i8];
        if (a1->_count != 0 && i8 >= 0 && i8 < a1->_count)
            ((unsigned char *)a1->_data)[i8] = v;
    }
    igUnsignedCharList *a2 = igProperty_GetRecordArray(arg1, DAT_00517f60)->value;
    for (int i9 = 0; i9 < 12; i9++) {
        unsigned char v = s->a2[i9];
        if (a2->_count != 0 && i9 >= 0 && i9 < a2->_count)
            ((unsigned char *)a2->_data)[i9] = v;
    }
    igIntList *a3 = FUN_003a9250(arg1, DAT_00517f70)->value;
    for (int i10 = 0; i10 < 16; i10++) {
        int v = s->a3[i10];
        if (a3->_count != 0 && i10 >= 0 && i10 < a3->_count)
            ((int *)a3->_data)[i10] = v;
    }
    igUnsignedCharList *a4 = igProperty_GetRecordArray(arg1, DAT_00517f80)->value;
    for (int i11 = 0; i11 < 16; i11++) {
        unsigned char v = s->a4[i11];
        if (a4->_count != 0 && i11 >= 0 && i11 < a4->_count)
            ((unsigned char *)a4->_data)[i11] = v;
    }
    igIntList *a5 = FUN_003a9250(arg1, DAT_00517f90)->value;
    for (int i12 = 0; i12 < 16; i12++) {
        int v = s->a5[i12];
        if (a5->_count != 0 && i12 >= 0 && i12 < a5->_count)
            ((int *)a5->_data)[i12] = v;
    }
    igIntList *a6 = FUN_003a9250(arg1, DAT_00517fa0)->value;
    for (int i13 = 0; i13 < 16; i13++) {
        int v = s->a6[i13];
        if (a6->_count != 0 && i13 >= 0 && i13 < a6->_count)
            ((int *)a6->_data)[i13] = v;
    }
    igIntList *a7 = FUN_003a9250(arg1, DAT_00517fb0)->value;
    for (int i14 = 0; i14 < 144; i14++) {
        int v = s->a7[i14];
        if (a7->_count != 0 && i14 >= 0 && i14 < a7->_count)
            ((int *)a7->_data)[i14] = v;
    }
    igIntList *a8 = FUN_003a9250(arg1, DAT_00517fc0)->value;
    for (int i15 = 0; i15 < 176; i15++) {
        if (a8->_count != 0 && i15 >= 0 && i15 < a8->_count)
            ((int *)a8->_data)[i15] = s->a8[i15];
    }
}
