#include "dw4/igSmartPointer.h"
#include "dw4/igobject_release.h"

class igResult {
public:
    int v;
    igResult() {}
    igResult(int x) : v(x) {}
    igResult(const igResult &o) : v(o.v) {}
    bool operator==(const igResult &o) const { return v == o.v; }
    inline bool isFailed(int &f) const;
    inline bool failed() const;
};
extern igResult DAT_004fb410;
extern igResult DAT_004fb418;
inline bool igResult::isFailed(int &f) const { f = DAT_004fb418.v; return *this == DAT_004fb418; }
inline bool igResult::failed() const { return v == DAT_004fb418.v; }

class Clock {
public:
  virtual void c0(); virtual void c1(); virtual void c2(); virtual void c3(); virtual void c4(); virtual void c5(); virtual void c6(); virtual void c7(); virtual void c8(); virtual void c9(); virtual void c10(); virtual void c11(); virtual void c12(); virtual void c13(); virtual void c14(); virtual void c15(); virtual void c16(); virtual void c17(); virtual void c18(); virtual void c19(); virtual void c20(); virtual void c21(); virtual void c22();
  virtual int now();
};
struct LogContext { char pad[56]; int f56; };
struct FieldOffsetInfo { char pad[8]; int f8; };
struct ReflectedRefObject { int vt; int rc; };
struct ReflectedNameObject { int vt; int rc; char *name; };
struct ReflectedNameList { int vt; int rc; int count; int cap; ReflectedNameObject **data; };
struct ReflectedValueList { int vt; int rc; int count; int cap; int *data; };
struct ReflectedRegistry { char p0[44]; ReflectedNameList *names; ReflectedValueList *values; };
struct IgbSectionBufferOwner;
class IgbSectionStream { public: virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3(); virtual void p4(); virtual void p5(); virtual void p6(); virtual void p7(); virtual void p8(); virtual void p9(); virtual void p10(); virtual void p11(); virtual void p12(); virtual void p13(); virtual void p14(); virtual void p15(); virtual void p16(); virtual void p17(); virtual void p18(); virtual void p19(); virtual void p20(); virtual void p21(); virtual void p22(); virtual void p23(); virtual void p24(); virtual int read(void *, int, int); };
class IgbSectionSwapper { public: virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3(); virtual void p4(); virtual void p5(); virtual void p6(); virtual void p7(); virtual void p8(); virtual void p9(); virtual void p10(); virtual void p11(); virtual void p12(); virtual void p13(); virtual void p14(); virtual void p15(); virtual void p16(); virtual void p17(); virtual void p18(); virtual void p19(); virtual void p20(); virtual void p21(); virtual void p22(); virtual void p23(); virtual void p24(); virtual void p25(); virtual void p26(); virtual void p27(); virtual void p28(); virtual void p29(); virtual void p30(); virtual void p31(); virtual void p32(); virtual void p33(); virtual void p34(); virtual void p35(); virtual void p36(); virtual void p37(); virtual void p38(); virtual void p39(); virtual void p40(); virtual void p41(); virtual void p42(); virtual void p43(); virtual void p44(); virtual void p45(); virtual void p46(); virtual void p47(); virtual void p48(); virtual void p49(); virtual void swap(void *, int); };
struct IGBReader34;
class SectionObject : public igVirtualObject {
public:
    virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7();
    virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15();
    virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20();
    virtual void setReferenceTarget(int target);
    virtual void d22(); virtual void d23();
    virtual SectionObject *resolve(IGBReader34 *file);
    virtual void setReferenceIndex(int index);
    virtual void d26();
    virtual void setMemoryPool(int pool);
    virtual int memoryPoolIndex();
    virtual void readFinished(IGBReader34 *file);
    int pad8;
    int index;
    char pad16[8];
    int referenceIndex;
};
struct SectionPoolTable : public igObject {
    int pad8[2];
    int *_data;
};

extern "C" {
extern int D_004fb418[4];
extern int DAT_004c2130[4];
extern int DAT_004c2138[4];
extern int DAT_004c2140[4];
extern char *DAT_004c22f0;
extern int DAT_004f7910[4];
extern int DAT_004f9a80[4];
extern int DAT_004f9ac8[4];
extern int DAT_004f9ad8[4];
extern int DAT_004f9af0[4];
extern int DAT_004f9b90[4];
extern int DAT_00585b70[4];
extern int DAT_00586140[4];
extern FieldOffsetInfo *DAT_00586280[4];
extern int DAT_00586710[4];
extern int DAT_00586730[4];
extern LogContext *DAT_00586dc8[4];
extern ReflectedRegistry *DAT_00586dd0;
extern char DAT_00586e20[64];
extern void *DAT_00586f20;
extern int DAT_00587198[4];
extern Clock *DAT_005871d8[4];
extern char GPR_00554c04;
extern unsigned char GPR_00554c08;
extern unsigned char GPR_00554c0c;
extern unsigned char g_useOwnerAllocator;

void *memset(void *, int, int);
int memcpy(...);
int strlen(...);
int strcpy(...);
int strcmp(...);
int sprintf(...);
int dpsub(...);
int FUN_00308240(...);
int FUN_00308320(...);
void *FUN_002eb010(int);
void *StringPool_Construct(void *);
char *StringPool_Intern(void *, const char *);
void StringChunk_ReleaseHeader(int, void *);
void *igIntMetaField_GetDefaultDescriptor(...);
void *igShortMetaField_GetDefaultDescriptor(...);
int igObject_IsKindOf(...);
int igObject_GetSerializedSize(...);
int igObject_WritePersistentFields(int, int, int, int, unsigned char);
void *FUN_002bd680(int);
void *FUN_002c72c0(int);
void *FUN_002c9130(int);
void *FUN_002caa70(...);
void *FUN_002d7e90(...);
void *thunk_FUN_002d7e90(...);
void *FUN_002fc250(...);
void FUN_002e31b0(void *, int);
int FUN_00306e50(int, int, void *, void *, int, int);
void List_Resize(void *, int, int);
void List_Reserve(void *, int, int);
void ObjectList_AppendRetained(...);
void ObjectList_ResizeRetained(void *, int);
igResult FUN_002e4f60(void *);
igResult FUN_002e63e0(void *);
igResult igIGBFile_GetSectionBuffer(IgbSectionBufferOwner *, int);
}

class DW4VC_208_2 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual int vX(int *, int); };
extern "C" int FUN_002e3a10(void *arg0, int arg1);

class MediaStream { public:
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual void s6();
    virtual void s7();
    virtual void s8();
    virtual void s9();
    virtual void s10();
    virtual void s11();
    virtual void s12();
    virtual void s13();
    virtual void s14();
    virtual void s15();
    virtual void s16();
    virtual void s17();
    virtual void s18();
    virtual void s19();
    virtual void s20();
    virtual igResult Open(int mode);
    virtual void Close();
    unsigned int _refCount;
};
struct StreamHolder { MediaStream *p; StreamHolder(MediaStream *v) { p = v; } ~StreamHolder(); };
struct MediaStreamOwner { char pad[104]; MediaStream *stream; char pad108[172]; void *source; };
extern "C" MediaStream *FUN_002c4ca0(void *);
extern "C" void FUN_002e30b0(MediaStream *, int);
inline StreamHolder::~StreamHolder() {
    IG_OBJECT_RELEASE(p);
}
static inline void assign(MediaStreamOwner *self, const StreamHolder &h) {
    MediaStream *v = h.p;
    MediaStream *old;
    if (v != 0) {
        v->_refCount = v->_refCount + 1;
    }
    old = self->stream;
    IG_OBJECT_RELEASE(old);
    self->stream = v;
}
extern "C" igResult FUN_002e3a60(MediaStreamOwner *self, int data, int mode);

struct Ref3 { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19(); virtual void v20(); virtual void v21(); virtual void v22(); union { int w; struct { unsigned cnt:23; unsigned f:9; } b; } u; };
struct S3 { int pad[26]; Ref3 *ref; };
extern "C" void FUN_002e3cb0(S3 *self);

extern "C" void FUN_002e3d30(int *arg0);

struct Ref5 { int vt; unsigned int _refCount; };
struct RecordFile { char pad[104]; Ref5 *handle; char pad2[88]; int open; };
extern "C" igResult FUN_002e3e30(RecordFile *f, int mode);

/* The holder keeps its address taken through the release method while the release body reads the
 * field directly. */
struct T6 { int word0; int references; };
extern "C" T6 *FUN_002c8e10(int);
extern "C" int FUN_002fe600(T6 *, int);
extern "C" int FUN_002fe300(int, unsigned);
extern "C" int ObjectList_AppendUniqueRetained(T6 *, int);
extern "C" unsigned int igMetaObject_CountTree(int);
struct Holder {
    T6 *ref;
    inline void release() {
        T6 **self = &ref;
        if (self) {
            if (ref) {
                --ref->references;
                if (((unsigned long long)(long long)ref->references & 0x7fffffULL) == 0)
                    igObject_Destroy(ref);
            }
        }
    }
};
struct Owner { char p[192]; T6 *f192; char p2[84]; int f280; };
extern "C" igResult FUN_002e3f50(Owner *arg1);

class E7 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual int vX(void *); int pad[2]; int f12; };
struct L7 { char pad[8]; int count; char pad1[4]; E7 **data; };
extern "C" igResult FUN_002e4090(L7 *arg1);

extern "C" int FUN_002f8960(int);
struct S8;
class A8 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual int *v52(int); };
class B8 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void v50(int *, int); };
struct S8 { char p0[168]; unsigned char f168; char p1[35]; B8 *f204; char p2[72]; A8 *f280; char p3[12]; int f296; int *f300; };
extern "C" igResult FUN_002e4120(S8 *o);

class C156 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual int vX(void *); };
extern "C" igResult FUN_002e4240(igIGBFile *arg1);

struct MetaTableField { char p0[18]; short size; unsigned short offset; char p22[15]; unsigned char inherited; unsigned char persistent; };
struct MetaTableFieldList { char p0[8]; MetaTableField **data; int count; };
struct MetaTableType { char p0[16]; int a16; int a20; char p24[4]; char *name; char p32[8]; MetaTableFieldList *fields; char p44[12]; int parent; };
struct MetaTableTypeList { int vt; int rc; int count; int cap; MetaTableType **data; };
struct MetaTableWords { int vt; int rc; int count; int cap; int *data; };
struct MetaTableRecord { int nameSize; int a4; int a8; int fieldCount; int parent; int persistCount; };
class MetaTableSwapper { public: virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3(); virtual void p4(); virtual void p5(); virtual void p6(); virtual void p7(); virtual void p8(); virtual void p9(); virtual void p10(); virtual void p11(); virtual void p12(); virtual void p13(); virtual void p14(); virtual void p15(); virtual void p16(); virtual void p17(); virtual void p18(); virtual void p19(); virtual void p20(); virtual void p21(); virtual void p22(); virtual void p23(); virtual void p24(); virtual void p25(); virtual void p26(); virtual void p27(); virtual void p28(); virtual void p29(); virtual void p30(); virtual void p31(); virtual void p32(); virtual void p33(); virtual void p34(); virtual void p35(); virtual void p36(); virtual void p37(); virtual void p38(); virtual void p39(); virtual void p40(); virtual void p41(); virtual void p42(); virtual void p43(); virtual void p44(); virtual void p45(); virtual void p46(); virtual void p47(); virtual void p48(); virtual void p49(); virtual void swap(void *, int); };
class MetaTablePool { public: virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3(); virtual void p4(); virtual void p5(); virtual void p6(); virtual void p7(); virtual void p8(); virtual void p9(); virtual void p10(); virtual void p11(); virtual void p12(); virtual void p13(); virtual void p14(); virtual void p15(); virtual void p16(); virtual void p17(); virtual void p18(); virtual void p19(); virtual void p20(); virtual void p21(); virtual void p22(); virtual void p23(); virtual void p24(); virtual void p25(); virtual void p26(); virtual void p27(); virtual void p28(); virtual void p29(); virtual void p30(); virtual void p31(); virtual void p32(); virtual void p33(); virtual void p34(); virtual void p35(); virtual void p36(); virtual void p37(); virtual void p38(); virtual void p39(); virtual void p40(); virtual void p41(); virtual void p42(); virtual void p43(); virtual void p44(); virtual void p45(); virtual void p46(); virtual void p47(); virtual void p48(); virtual void p49(); virtual void p50(); virtual void p51(); virtual void p52(); virtual MetaTableRecord *alloc(int, int); };
struct MetaTableWriter { char p0[128]; int count; int size; char p136[32]; unsigned char swapped; char p169[3]; MetaTableRecord *block; char p176[16]; MetaTableTypeList *types; char p196[8]; MetaTableSwapper *swapper; char p208[72]; MetaTablePool *pool; };
extern "C" int igMetaObject_GetFieldCount(int);
extern "C" short igMetaField_GetTypeIndex(MetaTableField *);
class Ref10 { public: MetaTableWords *p; Ref10(MetaTableWords *o) : p(o) { }
 ~Ref10() { MetaTableWords *object = p; if (object) { --object->rc; if (((unsigned long long)(long long)object->rc & 0x7fffffULL) == 0) igObject_Destroy(object); } } };
static inline void bump(const Ref10 &r, int off) { int *c = (int *)((char *)r.p->data + off); *c = *c + 1; }
struct MetaTableKey { int v; };
static inline void fillWords(MetaTableWords *l, int c, int *value) {
    if (c >= 0) { if (c <= l->cap) { l->count = c; } else { List_Resize(l, c, 4); } }
}
static inline int indexOfParent(MetaTableTypeList *l, const MetaTableKey &key) {
    int n = l->count;
    int i;
    for (i = 0; i < n; i++) {
        if (key.v == ((int *)l->data)[i]) { return i; }
    }
    return -1;
}
extern "C" igResult FUN_002e42d0(MetaTableWriter *self);

struct R11 { char p0[16]; int f16; int f20; char p1[4]; int f28; };
class O11 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual R11 *vX(); };
struct T11 { char p[8]; O11 **data; int cnt; };
class W { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual int vX(int, int); };
class A11 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual int vX(int, int); };
struct S11 { char p0[136]; int f136; int f140; char p1[24]; unsigned char f168; char p2[15]; int f184; char p3[16]; W *f204; char p4[72]; A11 *f280; };
extern "C" igResult FUN_002e47f0(S11 *arg1);

class Ref12 { public: ReflectedNameList *p; Ref12(ReflectedNameList *o) : p(o) { if (p != 0) { p->rc = p->rc + 1; } }
 ~Ref12() { ReflectedNameList *object = p; if (object) { --object->rc; if (((unsigned long long)(long long)object->rc & 0x7fffffULL) == 0) igObject_Destroy(object); } } };
class IgbNamePool { public: virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3(); virtual void p4(); virtual void p5(); virtual void p6(); virtual void p7(); virtual void p8(); virtual void p9(); virtual void p10(); virtual void p11(); virtual void p12(); virtual void p13(); virtual void p14(); virtual void p15(); virtual void p16(); virtual void p17(); virtual void p18(); virtual void p19(); virtual void p20(); virtual void p21(); virtual void p22(); virtual void p23(); virtual void p24(); virtual void p25(); virtual void p26(); virtual void p27(); virtual void p28(); virtual void p29(); virtual void p30(); virtual void p31(); virtual void p32(); virtual void p33(); virtual void p34(); virtual void p35(); virtual void p36(); virtual void p37(); virtual void p38(); virtual void p39(); virtual void p40(); virtual void p41(); virtual void p42(); virtual void p43(); virtual void p44(); virtual void p45(); virtual void p46(); virtual void p47(); virtual void p48(); virtual void p49(); virtual void p50(); virtual void p51(); virtual void p52(); virtual int *alloc(int, int); };
class IgbNameSwapper { public: virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3(); virtual void p4(); virtual void p5(); virtual void p6(); virtual void p7(); virtual void p8(); virtual void p9(); virtual void p10(); virtual void p11(); virtual void p12(); virtual void p13(); virtual void p14(); virtual void p15(); virtual void p16(); virtual void p17(); virtual void p18(); virtual void p19(); virtual void p20(); virtual void p21(); virtual void p22(); virtual void p23(); virtual void p24(); virtual void p25(); virtual void p26(); virtual void p27(); virtual void p28(); virtual void p29(); virtual void p30(); virtual void p31(); virtual void p32(); virtual void p33(); virtual void p34(); virtual void p35(); virtual void p36(); virtual void p37(); virtual void p38(); virtual void p39(); virtual void p40(); virtual void p41(); virtual void p42(); virtual void p43(); virtual void p44(); virtual void p45(); virtual void p46(); virtual void p47(); virtual void p48(); virtual void p49(); virtual void swap(void *, int); };
struct IgbNameWriter { char p0[168]; unsigned char swapped; char p169[35]; IgbNameSwapper *swapper; char p208[28]; int *block; int blockSize; char p244[4]; int count; char p252[28]; IgbNamePool *pool; };
static inline char *nameOf(const Ref12 &r, int i) {
    char *n = r.p->data[i]->name;
    n = (n == 0) ? DAT_004c22f0 : n;
    return n;
}
extern "C" igResult FUN_002e4a40(IgbNameWriter *self);

class Alloc {
public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual void v16();
    virtual void v17();
    virtual void v18();
    virtual void v19();
    virtual void v20();
    virtual void v21();
    virtual void v22();
    virtual void v23();
    virtual void v24();
    virtual void v25();
    virtual void v26();
    virtual void v27();
    virtual void v28();
    virtual void v29();
    virtual void v30();
    virtual void v31();
    virtual void v32();
    virtual void v33();
    virtual void v34();
    virtual void v35();
    virtual void v36();
    virtual void v37();
    virtual void v38();
    virtual void v39();
    virtual void v40();
    virtual void v41();
    virtual void v42();
    virtual void v43();
    virtual void v44();
    virtual void v45();
    virtual void v46();
    virtual void v47();
    virtual void v48();
    virtual void v49();
    virtual void v50();
    virtual void v51();
    virtual void v52();
    virtual void *Alloc53(int size, int align);
};
class Sink {
public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual void v16();
    virtual void v17();
    virtual void v18();
    virtual void v19();
    virtual void v20();
    virtual void v21();
    virtual void v22();
    virtual void v23();
    virtual void v24();
    virtual void v25();
    virtual void v26();
    virtual void v27();
    virtual void v28();
    virtual void v29();
    virtual void v30();
    virtual void v31();
    virtual void v32();
    virtual void v33();
    virtual void v34();
    virtual void v35();
    virtual void v36();
    virtual void v37();
    virtual void v38();
    virtual void v39();
    virtual void v40();
    virtual void v41();
    virtual void v42();
    virtual void v43();
    virtual void v44();
    virtual void v45();
    virtual void v46();
    virtual void v47();
    virtual void v48();
    virtual void v49();
    virtual void Sink50(void *buf, int n);
};
struct Item { char p[20]; char *name; };
struct IList { int p0; int p4; int count; int p12; Item **data; };
struct Self {
    char p0[24]; IList *list;
    char p1[140]; unsigned char flag168;
    char p2[35]; Sink *sink204;
    char p3[5]; unsigned char b213;
    char p4[10]; int *buf224; int size228;
    char p5[48]; Alloc *alloc280;
};
extern "C" igResult FUN_002e4c90(Self *self);

class VC220 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual int vX(int, int); };
struct Lst { char pad8[8]; int n; };
struct Cx { char pad40[40]; Lst *f40; char pad44[68]; int f112; char pad116[8]; int f124; char pad128[40]; unsigned char f168; char pad169[3]; char pad172[4]; int f176; char pad180[12]; int f192; char pad196[84]; VC220 *f280; };
extern "C" igResult FUN_002e4e60(Cx *arg1);

struct IgbFixReader;
class IgbFixObject { public: virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3(); virtual void p4(); virtual void p5(); virtual void p6(); virtual void p7(); virtual void p8(); virtual void p9(); virtual void p10(); virtual void p11(); virtual void p12(); virtual void p13(); virtual void p14(); virtual void p15(); virtual void p16(); virtual void p17(); virtual void p18(); virtual void p19(); virtual void p20(); virtual void reset(int); virtual void p22(); virtual void p23(); virtual IgbFixObject *replacement(IgbFixReader *); virtual void attach(int); int rc; char q8[4]; int index; char q16[8]; int word; };
struct IgbFixWords { int vt; int rc; int count; int cap; int *data; };
struct IgbFixPlain { int vt; int rc; };
struct IgbFixRetain { IgbFixObject *p; IgbFixRetain(IgbFixObject *o) : p(o) { if (p != 0) { p->rc = p->rc + 1; } } };
struct IgbFixReader { char p0[8]; int count; char p12[4]; IgbFixObject **data; char p20[20]; IgbFixPlain *sorted; IgbFixWords *words; char p48[44]; IgbFixPlain *map; char p96[118]; unsigned char fixed; char p215[65]; int pool; };
extern "C" void List_InsertWords(IgbFixPlain *, int, int, IgbFixRetain *);
extern "C" int FUN_00142bb0(IgbFixPlain *, IgbFixRetain *);
#define RELEASE(old) if (old != 0) { old->rc = old->rc - 1; if (((unsigned long long)((long long)(int)old->rc << 0x29) >> 0x29) == 0) igObject_Destroy(old); }
extern "C" igResult FUN_002e5110(IgbFixReader *self);

class VC16 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual int v220(int, int); };
struct O16 {
    char pad0[8];
    int f8;
    char pad1[4];
    int *f16;
    char pad2[92];
    int f112;
    char pad3[8];
    int f124;
    char pad4[40];
    unsigned char f168;
    char pad5[7];
    int f176;
    char pad6[12];
    int f192;
    char pad7[84];
    VC16 *f280;
};
extern "C" igResult FUN_002e53f0(void *arg1) {
    O16 *o = (O16 *)arg1;
    int var_s0;
    int var_s1;
    o->f124 = 0;
    var_s0 = 0;
    o->f112 = o->f8;
    while (var_s0 < o->f112) {
        o->f124 = o->f124 + igObject_GetSerializedSize(o->f16[var_s0]);
        var_s0 += 1;
    }
    o->f176 = o->f280->v220(o->f124, 16);
    var_s1 = o->f176;
    var_s0 = 0;
    while (var_s0 < o->f112) {
        var_s1 += igObject_WritePersistentFields(o->f16[var_s0], var_s1, 0, o->f192, o->f168);
        var_s0 += 1;
    }
    return DAT_004fb410;
}

class A17 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual int a(int,int); };
class B17 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void b(void *); };
struct O17 { char pad[8]; int n; char pad2[136]; unsigned f148; char pad3[28]; int f180; char pad4[68]; int f252; char pad5[24]; A17 *f280; };
extern "C" igResult FUN_002e54e0(O17 *o);

class Mgr18 { public: virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3(); virtual void p4(); virtual void p5(); virtual void p6(); virtual void p7(); virtual void p8(); virtual void p9(); virtual void p10(); virtual void p11(); virtual void p12(); virtual void p13(); virtual void p14(); virtual void p15(); virtual void p16(); virtual void p17(); virtual void p18(); virtual void p19(); virtual void p20(); virtual void p21(); virtual void p22(); virtual void p23(); virtual void p24(); virtual void p25(); virtual void p26(); virtual void p27(); virtual void p28(); virtual void p29(); virtual void p30(); virtual void p31(); virtual void p32(); virtual void p33(); virtual void p34(); virtual void p35(); virtual void p36(); virtual void p37(); virtual void p38(); virtual void p39(); virtual void p40(); virtual void p41(); virtual void p42(); virtual void p43(); virtual void p44(); virtual void p45(); virtual void p46(); virtual void p47(); virtual void p48(); virtual void p49(); virtual void p50(); virtual void p51(); virtual void p52(); virtual void *alloc(int, int); virtual void p54(); virtual void p55(); virtual void p56(); virtual void p57(); virtual void p58(); virtual void p59(); virtual void p60(); virtual void p61(); virtual void p62(); virtual void p63(); virtual void rel(void *); };
class Z18 { public: virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3(); virtual void p4(); virtual void p5(); virtual void p6(); virtual void p7(); virtual void p8(); virtual void p9(); virtual void p10(); virtual void p11(); virtual void p12(); virtual void p13(); virtual void p14(); virtual void p15(); virtual void p16(); virtual void p17(); virtual void p18(); virtual void p19(); virtual void p20(); virtual void p21(); virtual void p22(); virtual void p23(); virtual void p24(); virtual void p25(); virtual void p26(); virtual void p27(); virtual void p28(); virtual void p29(); virtual void p30(); virtual void p31(); virtual void p32(); virtual void p33(); virtual void p34(); virtual void p35(); virtual void p36(); virtual void p37(); virtual void p38(); virtual void p39(); virtual void p40(); virtual void p41(); virtual void p42(); virtual void p43(); virtual void p44(); virtual void p45(); virtual void p46(); virtual void p47(); virtual void p48(); virtual void p49(); virtual void a(void *, int); };
class Q18 { public: virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3(); virtual void p4(); virtual void p5(); virtual void p6(); virtual void p7(); virtual void p8(); virtual void p9(); virtual void p10(); virtual void p11(); virtual void p12(); virtual void p13(); virtual void p14(); virtual void p15(); virtual void p16(); virtual void p17(); virtual void p18(); virtual void p19(); virtual void p20(); virtual void p21(); virtual void p22(); virtual void p23(); virtual void p24(); virtual void p25(); virtual void p26(); virtual void b(void *, int, int); };
struct O18 {
 char p0[36]; unsigned char b36; char p1[28]; unsigned char b65; char p2[30]; int f96; int f100; Q18 *f104; char p3[4]; int f112; char p4[8]; int f124; int f128; int f132; int f136; int f140; int f144; int f148; int f152; int f156; char p5[8]; unsigned char b168; char p6[35]; Z18 *f204; char p7[4]; unsigned char b212; unsigned char b213; char p8[66]; Mgr18 *mgr;
};
extern "C" igResult FUN_002e5590(O18 *o);

class Rd {
public:
    virtual void d0();
    virtual void d1();
    virtual void d2();
    virtual void d3();
    virtual void d4();
    virtual void d5();
    virtual void d6();
    virtual void d7();
    virtual void d8();
    virtual void d9();
    virtual void d10();
    virtual void d11();
    virtual void d12();
    virtual void d13();
    virtual void d14();
    virtual void d15();
    virtual void d16();
    virtual void d17();
    virtual void d18();
    virtual void d19();
    virtual void d20();
    virtual void d21();
    virtual void d22();
    virtual void d23();
    virtual void d24();
    virtual void d25();
    virtual void d26();
    virtual int v116(int, int, int);
};
class Al19 {
public:
    virtual void d0();
    virtual void d1();
    virtual void d2();
    virtual void d3();
    virtual void d4();
    virtual void d5();
    virtual void d6();
    virtual void d7();
    virtual void d8();
    virtual void d9();
    virtual void d10();
    virtual void d11();
    virtual void d12();
    virtual void d13();
    virtual void d14();
    virtual void d15();
    virtual void d16();
    virtual void d17();
    virtual void d18();
    virtual void d19();
    virtual void d20();
    virtual void d21();
    virtual void d22();
    virtual void d23();
    virtual void d24();
    virtual void d25();
    virtual void d26();
    virtual void d27();
    virtual void d28();
    virtual void d29();
    virtual void d30();
    virtual void d31();
    virtual void d32();
    virtual void d33();
    virtual void d34();
    virtual void d35();
    virtual void d36();
    virtual void d37();
    virtual void d38();
    virtual void d39();
    virtual void d40();
    virtual void d41();
    virtual void d42();
    virtual void d43();
    virtual void d44();
    virtual void d45();
    virtual void d46();
    virtual void d47();
    virtual void d48();
    virtual void d49();
    virtual void d50();
    virtual void d51();
    virtual void d52();
    virtual void d53();
    virtual void d54();
    virtual void d55();
    virtual void d56();
    virtual void d57();
    virtual void d58();
    virtual void d59();
    virtual void d60();
    virtual void d61();
    virtual void d62();
    virtual void d63();
    virtual void v264(int);
};
class Sk {
public:
    virtual void d0();
    virtual void d1();
    virtual void d2();
    virtual void d3();
    virtual void d4();
    virtual void d5();
    virtual void d6();
    virtual void d7();
    virtual void d8();
    virtual void d9();
    virtual void d10();
    virtual void d11();
    virtual void d12();
    virtual void d13();
    virtual void d14();
    virtual void d15();
    virtual void d16();
    virtual void d17();
    virtual void d18();
    virtual void d19();
    virtual void d20();
    virtual void d21();
    virtual void d22();
    virtual void d23();
    virtual void d24();
    virtual void d25();
    virtual void d26();
    virtual void d27();
    virtual void d28();
    virtual void d29();
    virtual void d30();
    virtual void d31();
    virtual void d32();
    virtual void d33();
    virtual void d34();
    virtual void d35();
    virtual void d36();
    virtual void d37();
    virtual void d38();
    virtual void d39();
    virtual void d40();
    virtual void d41();
    virtual void d42();
    virtual void d43();
    virtual void d44();
    virtual void d45();
    virtual void d46();
    virtual void d47();
    virtual void d48();
    virtual void d49();
    virtual void v208(int, int);
};
class Obj19 {
public:
    virtual void d0();
    virtual void d1();
    virtual void d2();
    virtual void d3();
    virtual void d4();
    virtual void d5();
    virtual void d6();
    virtual void d7();
    virtual void d8();
    virtual void d9();
    virtual void d10();
    virtual void d11();
    virtual void d12();
    virtual void d13();
    virtual void d14();
    virtual void d15();
    virtual void d16();
    virtual void d17();
    virtual void d18();
    virtual void d19();
    virtual void d20();
    virtual void d21();
    virtual void d22();
    virtual void d23();
    virtual void d24();
    virtual void d25();
    virtual void d26();
    virtual void d27();
    virtual void d28();
    virtual void d29();
    virtual void d30();
    virtual void d31();
    virtual int v136();
    char pad0[61];
    unsigned char f65;
    char pad1[38];
    Rd * f104;
    char pad2[8];
    int f116;
    int f120;
    int f124;
    char pad3[4];
    int f132;
    char pad4[4];
    int f140;
    char pad5[4];
    int f148;
    char pad6[16];
    unsigned char f168;
    char pad7[3];
    int f172;
    int f176;
    int f180;
    int f184;
    char pad8[16];
    Sk * f204;
    char pad9[12];
    int f220;
    int f224;
    int f228;
    char pad10[4];
    int f236;
    int f240;
    char pad11[36];
    Al19 * f280;
    char pad12[12];
    int f296;
    int f300;
};
extern "C" igResult FUN_002e56f0(Obj19 *arg1);


extern "C" igResult FUN_002e5950(void *arg1);

class Mgr21 { public: virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3(); virtual void p4(); virtual void p5(); virtual void p6(); virtual void p7(); virtual void p8(); virtual void p9(); virtual void p10(); virtual void p11(); virtual void p12(); virtual void p13(); virtual void p14(); virtual void p15(); virtual void p16(); virtual void p17(); virtual void p18(); virtual void p19(); virtual void p20(); virtual void p21(); virtual void p22(); virtual void p23(); virtual void p24(); virtual void p25(); virtual void p26(); virtual void p27(); virtual void p28(); virtual void p29(); virtual void p30(); virtual void p31(); virtual void p32(); virtual void p33(); virtual void p34(); virtual void p35(); virtual void p36(); virtual void p37(); virtual void p38(); virtual void p39(); virtual void p40(); virtual void p41(); virtual void p42(); virtual void p43(); virtual void p44(); virtual void p45(); virtual void p46(); virtual void p47(); virtual void p48(); virtual void p49(); virtual void p50(); virtual void p51(); virtual void p52(); virtual void p53(); virtual void p54(); virtual void p55(); virtual void p56(); virtual void p57(); virtual void p58(); virtual void p59(); virtual void p60(); virtual void p61(); virtual void p62(); virtual void p63(); virtual void rel(int); };
struct Rc { int p; int f4; };
struct T21 {
    char pad0[120]; int f120; char pad1[48]; int f172; int f176; int f180; int f184; char pad2[48]; int f236;
    char pad3[40]; Mgr21 *mgr; char pad4[12]; int f296; int f300; Rc *f304;
};
extern "C" igResult FUN_002e5990(T21 *o);

extern "C" int FUN_002d8620(...);
extern "C" igResult FUN_002e5ac0(void *arg1);

struct Rel23 { int p; int rc; };
class C23 { public:
virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual igResult v128();
 char pad[4]; int f8; char pad2[24]; unsigned char f36; char pad3[167]; Rel23 *f204; Rel23 *f208; char pad4[66]; unsigned char f278; };
extern "C" int FUN_00302540(C23 *, int);
#define REL23(p) if (p != 0) { p->rc = p->rc - 1; if (((unsigned long long)((long long)p->rc << 0x29) >> 0x29) == 0) igObject_Destroy(p); }
extern "C" int Gap__Core__igIGBFile__vfunc_28(C23 *arg0, int arg1);

struct Obj24 { char p0[4]; int refs; };
struct T24 { char p0[104]; Obj24 *f104; char p108[88]; int f196; };
extern "C" igResult FUN_002e5f70(T24 *arg1, int arg2);

struct H { int f0, f4, f8, f12, f16, f20, f24, f28, f32, f36, f40, f44; };
class Dev { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual int v27(void *, int, int); };
class Obj25 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual int v52(H *, int); int rc; };
struct S25 {
    char p0[96]; int f96; int f100; Dev *f104; char p1[4];
    int f112; char p2[8]; int f124; int f128; int f132; int f136; int f140; int f144; int f148; int f152; int f156;
    char p3[8]; char f168; char p4[35]; Obj25 *f204; Obj25 *f208;
    char f212, f213, f214; unsigned char f215; int f216; char p5[44]; H *f264; char p6[24]; char f292;
};
extern "C" igResult igIGBFile_ReadHeader(S25 *arg1);

class DW4VC_108_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual int vX(int, int, int); };
struct P26 { char pad[104]; DW4VC_108_1 *f104; };
struct Q26 { char pad[132]; int f132; char pad2[36]; int f172; char pad3[88]; int f264; };
extern "C" igResult FUN_002e6330(Q26 *arg1);

class VC27 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual int vX(int); };
extern "C" igResult FUN_002e6f50(int *arg1);


extern "C" void FUN_002e7000(void);

class V { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual int vX(int, int, int); };
struct Z29 { char pad0[80]; int f80; int f84; int f88; char pad1[12]; V *f104; char pad2[152]; int f260; int f264; };
extern "C" igResult FUN_002e7030(Z29 *arg1);

struct T30 : public igObject {
    
    void release() {
        _refCount = _refCount - 1;
        if ((_refCount & 0x7FFFFF) == 0) {
            igObject_Destroy(this);
        }
    }
};
struct C30 { char p0[80]; int f80; int f84; char p88[12]; int f100; char p104[64]; unsigned char f168; char p169[23]; int f192; char p196[20]; int f216; char p220[40]; int f260; int f264; char p268[12]; int f280; };
extern "C" int FUN_002fff90(T30*, int*, C30*, int, unsigned char);
extern "C" int FUN_00300250(T30*, int*, C30*, int, unsigned char);
extern "C" int igObject_RegisterInstance(...);
class MF {
public:
  virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9();
  virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19();
  virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29();
  virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39();
  virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49();
  virtual int vX(int *, int);
};
extern "C" void *igMetaObject_CreateInstanceWithPool(...);
static inline T30 *castToKind(T30 *object) {
    if (object != 0 && igObject_IsKindOf(object, DAT_00586710[0]) != 0) {
        return object;
    }
    return 0;
}

typedef igSmartPointer<SectionObject> SectionObjectRef;

extern "C" SectionObjectRef igIGBFile_ReadObject(C30 *file);

struct IGBReader31 {
    char pad0[40];
    igObjectList *objects;
    char pad44[21];
    unsigned char remapPools;
    char pad66[14];
    int position;
    int consumed;
    int bufferEnd;
    char pad92[20];
    int objectCount;
    char pad116[8];
    int sectionSize;
    char pad128[132];
    int bufferSize;
    char pad264[12];
    unsigned char failed;
    char pad277[3];
    int pool;
    char pad284[20];
    SectionPoolTable *poolTable;
};

extern "C" igResult igIGBFile_ReadObjectSection(IGBReader31 *file);

struct IgbSectionObject { int vt; int rc; };
struct IgbObjectSection { char p0[8]; int count; char p12[4]; IgbSectionObject **data; char p20[20]; int source; char p44[60];
  IgbSectionStream *stream; char p108[8]; int size; char p120[48]; unsigned char swapped; char p169[35]; IgbSectionSwapper *swapper; IgbSectionSwapper *swapper16; char p212[48]; int bufferCap; short *buffer; };
extern "C" igResult FUN_002e7640(IgbObjectSection *self);

struct O33;
class E33 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void vX(O33 *); };
struct T33 { int word0; int references; int n; int cap; };
struct O33 { int p0; int p1; int n; char pad[32]; T33 *list; char pad2[232]; int f280; };
extern "C" igResult FUN_002e78b0(O33 *arg1);

struct IGBReader34;
struct IndexList : public igObject {
    int _count;
    int _capacity;
    int *_data;
};
struct IGBReader34 : public igObject {
    int _count;
    int _capacity;
    SectionObject **_data;
    char pad20[16];
    unsigned char oldReferences;
    char pad37[7];
    IndexList *referenceIndices;
    char pad48[17];
    unsigned char remapPools;
    char pad66[14];
    int position;
    int consumed;
    int bufferEnd;
    igObject *resolved;
    char pad96[16];
    int objectCount;
    char pad116[8];
    int sectionSize;
    char pad128[132];
    int bufferSize;
    char pad264[12];
    unsigned char failed;
    char pad277[3];
    int pool;
    char pad284[20];
    SectionPoolTable *poolTable;

    void set(int i, const igSmartPointer<SectionObject> &held) {
        SectionObject *entry = held.p;
        if (entry != 0) entry->_refCount = entry->_refCount + 1;
        igVirtualObject *old = _data[i];
        if (old != 0) {
            old->_refCount = old->_refCount - 1;
            if ((old->_refCount & 0x7FFFFF) == 0) igObject_Destroy(old);
        }
        if (_count != 0 && i >= 0 && i < _count) {
            _data[i] = entry;
        }
    }
    void setRaw(int i, SectionObject *entry) {
        if (entry != 0) entry->_refCount = entry->_refCount + 1;
        igVirtualObject *old = _data[i];
        if (old != 0) {
            old->_refCount = old->_refCount - 1;
            if ((old->_refCount & 0x7FFFFF) == 0) igObject_Destroy(old);
        }
        if (_count != 0 && i >= 0 && i < _count) {
            _data[i] = entry;
        }
    }
};

extern "C" igResult igIGBFile_ReadObjectSectionOld(IGBReader34 *file);

extern "C" int Gap__Core__igIGBFile__vfunc_27(void *arg0);

struct IgbBlockStream { char p0[20]; int mode; };
struct IgbBlockCursor { char p0[80]; int offset; int done; int total; char p92[12]; IgbBlockStream *stream; char p108[108]; int pending; char p220[32]; int mark; char p256[4]; int cap; int base; };
extern "C" void Gap__Core__igIGBFile__vfunc_26(IgbBlockCursor *self, int at);

class VC264 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63(); virtual int vX(int); };
struct S37 { char p0[200]; int f200; char p1[76]; VC264 *f280; };
extern "C" igResult FUN_002e7ed0(S37 *arg1);

struct IgbRegistryObject;
class IgbRegistryMeta { public: char p0[28]; char *name; };
class IgbRegistryType { public: virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3(); virtual void p4(); virtual void p5(); virtual void p6(); virtual void p7(); virtual void p8(); virtual void p9(); virtual void p10(); virtual void p11(); virtual void p12(); virtual void p13(); virtual void p14(); virtual void p15(); virtual void p16(); virtual void p17(); virtual void p18(); virtual void p19(); virtual IgbRegistryMeta *meta(); };
struct IgbRegistryTable { char p0[8]; IgbRegistryType **data; int count; };
struct IgbTypeRefList { int vt; int rc; int count; };
struct IgbMetaSection { char p0[104]; IgbSectionStream *stream; char p108[28]; int entries; int bytes; char p144[24]; unsigned char swapped; char p169[15]; int *buffer; IgbTypeRefList *types; char p192[12]; IgbSectionSwapper *swapper; char p208[56]; int *work; char p268[12]; int pool; };
extern "C" IgbTypeRefList *FUN_002c8af0(int);
extern "C" igResult FUN_002e7f20(IgbMetaSection *self);

struct T39 { int word0; int references; };
extern "C" T39 *Memory_GetDefaultAllocator(...);
struct Rel39 { static inline void go(T39 *object) {
    if (object) {
        --object->references;
        if (((unsigned long long)(long long)object->references & 0x7fffffULL) == 0)
            igObject_Destroy(object);
    }
} };
struct Obj39 { char p[280]; T39 *m280; T39 *m284; T39 *m288; };
extern "C" void Gap__Core__igIGBFile__vfunc_13(Obj39 *arg0);

struct ReflectedTypeList { int vt; int rc; int count; int cap; int *data; int getCount() const { return count; } };
class Ref40 { public: ReflectedRefObject *p; Ref40(void *o) : p((ReflectedRefObject *)o) { if (p != 0) { p->rc = p->rc + 1; } }
 ~Ref40() { ReflectedRefObject *object = p; if (object) { --object->rc; if (((unsigned long long)(long long)object->rc & 0x7fffffULL) == 0) igObject_Destroy(object); } } };
class TypeListHolder { public: ReflectedTypeList *p; TypeListHolder(ReflectedTypeList *v) { p = v; }
 ~TypeListHolder() { if (p != 0) { p->rc = p->rc - 1; if (((unsigned long long)((long long)(int)p->rc << 0x29) >> 0x29) == 0) { igObject_Destroy(p); } } } };
class IgbStreamReader { public: virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3(); virtual void p4(); virtual void p5(); virtual void p6(); virtual void p7(); virtual void p8(); virtual void p9(); virtual void p10(); virtual void p11(); virtual void p12(); virtual void p13(); virtual void p14(); virtual void p15(); virtual void p16(); virtual void p17(); virtual void p18(); virtual void p19(); virtual void p20(); virtual void p21(); virtual void p22(); virtual void p23(); virtual void p24(); virtual int read(void *, int, int); };
class IgbWordSwapper { public: virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3(); virtual void p4(); virtual void p5(); virtual void p6(); virtual void p7(); virtual void p8(); virtual void p9(); virtual void p10(); virtual void p11(); virtual void p12(); virtual void p13(); virtual void p14(); virtual void p15(); virtual void p16(); virtual void p17(); virtual void p18(); virtual void p19(); virtual void p20(); virtual void p21(); virtual void p22(); virtual void p23(); virtual void p24(); virtual void p25(); virtual void p26(); virtual void p27(); virtual void p28(); virtual void p29(); virtual void p30(); virtual void p31(); virtual void p32(); virtual void p33(); virtual void p34(); virtual void p35(); virtual void p36(); virtual void p37(); virtual void p38(); virtual void p39(); virtual void p40(); virtual void p41(); virtual void p42(); virtual void p43(); virtual void p44(); virtual void p45(); virtual void p46(); virtual void p47(); virtual void p48(); virtual void p49(); virtual void swap(void *, int); };
struct IgbTypeReader { char p0[104]; IgbStreamReader *stream; char p108[60]; unsigned char swapped; char p169[35]; IgbWordSwapper *swapper; char p208[28];
  int *buffer; int bufferSize; ReflectedTypeList *types; int typeCount; char p252[12]; int *work; char p268[12]; int pool; };
struct IgbTypeHeader { int size; int pad; int count; };
static inline void assignTypes(IgbTypeReader *self, const TypeListHolder &h) {
    ReflectedTypeList *v = h.p;
    ReflectedTypeList *old;
    if (v != 0) { v->rc = v->rc + 1; }
    old = self->types;
    if (old != 0) { old->rc = old->rc - 1; if (((unsigned long long)((long long)(int)old->rc << 0x29) >> 0x29) == 0) igObject_Destroy(old); }
    self->types = v;
}
static inline void addType(ReflectedTypeList *l, int v) {
    int idx;
    idx = l->count;
    if (l->cap > idx) { l->count = l->getCount() + 1; } else { List_Resize(l, idx + 1, 4); }
    l->data[idx] = v;
}
extern "C" igResult FUN_002e82a0(IgbTypeReader *self);

struct T41 { char p0[8]; int count; char p12[4]; void **data; char p20[60]; int f80; int f84; int f88; char p92[8]; int f100; char p104[44]; int f148; char p152[28]; int f180; char p184[68]; int f252; char p256[4]; int f260; };
class E41 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void v128(T41 *); virtual void v132(T41 *); virtual void v136(T41 *); };
class EE : public E41 { public: int refs; };
struct Ref41 {
    EE *p;
    Ref41(EE *o) : p(o) { if (p != 0) { p->refs = p->refs + 1; } }
    ~Ref41() {
        EE *object = p;
        if (object) {
            --object->refs;
            if (((unsigned long long)(long long)object->refs & 0x7fffffULL) == 0)
                igObject_Destroy(object);
        }
    }
};
inline int load(T41 *t, int *fail) {
    igResult r = FUN_002e7030((Z29 *)t);
    int *pp;
    pp = (int *)((int)&r + 0);
    *fail = D_004fb418[0];
    return *pp;
}
extern "C" igResult FUN_002e8670(T41 *arg1);

struct L42;
class O42 {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29();
    virtual void v30(L42 *);
    virtual void v31(L42 *);
    virtual void v32(L42 *);
};
struct L42 { int p0, p4; int n; int p12; void **arr; char pad[80]; int f100; };
extern "C" igResult FUN_002e8880(L42 *arg1);


extern "C" void FUN_002e8a10(void *arg0);

struct R44 { int vt; int rc; };
struct Al44 { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19(); virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23(); virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27(); virtual void v28(); virtual void v29(); virtual void v30(); virtual void v31(); virtual void v32(); virtual void v33(); virtual void v34(); virtual void v35(); virtual void v36(); virtual void v37(); virtual void v38(); virtual void v39(); virtual void v40(); virtual void v41(); virtual void v42(); virtual void v43(); virtual void v44(); virtual void v45(); virtual void v46(); virtual void v47(); virtual void v48(); virtual void v49(); virtual void v50(); virtual void v51(); virtual void v52(); virtual void v53(); virtual void v54(); virtual void v55(); virtual void v56(); virtual void v57(); virtual void v58(); virtual void v59(); virtual void v60(); virtual void v61(); virtual void v62(); virtual void v63(); virtual void v64(int); };
struct T44 {
  char p0[40]; R44 *f40; char p1[16]; R44 *f60; char p2[28]; R44 *f92; char p3[24]; int f120; char p4[48]; int f172; int f176; int f180; int f184; R44 *f188; R44 *f192; char p5[68]; int f264; char p6[12]; Al44 *f280; char p7[12]; int f296; int f300; R44 *f304;
};
#define REL44(p) do { R44 *t_ = (p); if (t_ != 0) { t_->rc = t_->rc - 1; if (((unsigned long long)((long long)t_->rc << 0x29) >> 0x29) == 0) { igObject_Destroy(t_); } } } while (0)
extern "C" void FUN_002e8a40(T44 *a);

typedef struct S_ref { char p0[4]; int references; } S_ref;
typedef struct S_list { char p0[8]; int f8; char p1[4]; int *f16; } S_list;
class IObj { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25();  virtual int vX(int); };
typedef struct S_arg0 { char p0[16]; IObj **f16; char p1[24]; S_list *f44; } S_arg0;
extern "C" int Gap__Core__igObject__vfunc_02(...);
extern "C" void Gap__Core__igIGBFile__vfunc_04(S_arg0 *arg0);

class VC_108_3 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual int vX(int, int, int); };
class VC_208_2 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual int vX(int, int); };
struct R46 { char pad[4]; int f4; };
struct Q46 { char pad[24]; R46 *f24; };
struct A46 { char pad[28]; R46 *f28; char pad2[72]; VC_108_3 *f104; char pad3[60]; unsigned char f168; char pad4[35]; VC_208_2 *f204; char pad5[4]; unsigned char f212; char pad6[7]; int f220; };
extern "C" igResult FUN_002e8d40(A46 *arg1);

struct PooledStringHead { int chunk; int refs; };
static inline void *stringPool() {
    if (DAT_00586f20 == 0) {
        void *p = FUN_002eb010(16);
        if (p != 0) { p = StringPool_Construct(p); }
        DAT_00586f20 = p;
    }
    return DAT_00586f20;
}
static inline void setPooled(char **dst, char *src) {
    char *v = StringPool_Intern(stringPool(), src);
    char *old = *dst;
    if (old != 0) {
        PooledStringHead *h = (PooledStringHead *)(old - 8);
        int n = h->refs - 1;
        h->refs = n;
        if (n == 0) { StringChunk_ReleaseHeader(h->chunk, h); }
    }
    *dst = v;
}
struct IgbExternalDir { char p0[20]; char *path; };
class IgbExternalStream { public: virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3(); virtual void p4(); virtual void p5(); virtual void p6(); virtual void p7(); virtual void p8(); virtual void p9(); virtual void p10(); virtual void p11(); virtual void p12(); virtual void p13(); virtual void p14(); virtual void p15(); virtual void p16(); virtual void p17(); virtual void p18(); virtual void p19(); virtual void p20(); virtual void p21(); virtual void p22(); virtual void p23(); virtual void p24(); virtual int read(void *, int, int); };
class IgbExternalSwapper { public: virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3(); virtual void p4(); virtual void p5(); virtual void p6(); virtual void p7(); virtual void p8(); virtual void p9(); virtual void p10(); virtual void p11(); virtual void p12(); virtual void p13(); virtual void p14(); virtual void p15(); virtual void p16(); virtual void p17(); virtual void p18(); virtual void p19(); virtual void p20(); virtual void p21(); virtual void p22(); virtual void p23(); virtual void p24(); virtual void p25(); virtual void p26(); virtual void p27(); virtual void p28(); virtual void p29(); virtual void p30(); virtual void p31(); virtual void p32(); virtual void p33(); virtual void p34(); virtual void p35(); virtual void p36(); virtual void p37(); virtual void p38(); virtual void p39(); virtual void p40(); virtual void p41(); virtual void p42(); virtual void p43(); virtual void p44(); virtual void p45(); virtual void p46(); virtual void p47(); virtual void p48(); virtual void p49(); virtual void swap(void *, int); };
class IgbExternalPool { public: virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3(); virtual void p4(); virtual void p5(); virtual void p6(); virtual void p7(); virtual void p8(); virtual void p9(); virtual void p10(); virtual void p11(); virtual void p12(); virtual void p13(); virtual void p14(); virtual void p15(); virtual void p16(); virtual void p17(); virtual void p18(); virtual void p19(); virtual void p20(); virtual void p21(); virtual void p22(); virtual void p23(); virtual void p24(); virtual void p25(); virtual void p26(); virtual void p27(); virtual void p28(); virtual void p29(); virtual void p30(); virtual void p31(); virtual void p32(); virtual void p33(); virtual void p34(); virtual void p35(); virtual void p36(); virtual void p37(); virtual void p38(); virtual void p39(); virtual void p40(); virtual void p41(); virtual void p42(); virtual void p43(); virtual void p44(); virtual void p45(); virtual void p46(); virtual void p47(); virtual void p48(); virtual void p49(); virtual void p50(); virtual void p51(); virtual void p52(); virtual int *alloc(int, int); virtual void p54(); virtual void p55(); virtual void p56(); virtual void p57(); virtual void p58(); virtual void p59(); virtual void p60(); virtual void p61(); virtual void p62(); virtual void p63(); virtual void release(int *); };
struct IgbExternalHeader { int size; int pad; int count; };
struct IgbExternalReader { char p0[24]; int list; char p28[4]; IgbExternalDir *dir; char p36[68]; IgbExternalStream *stream; char p108[60]; unsigned char swapped; char p169[31]; char *name; IgbExternalSwapper *swapper; char p208[5]; unsigned char hasExternals; char p214[10]; int *buffer; int bytes; char *savedPath; char p236[44]; IgbExternalPool *pool; };
extern "C" IgbExternalDir *FUN_00309a50();
extern "C" int FUN_00308fb0(IgbExternalDir *, char *);
extern "C" igResult FUN_002e8e50(IgbExternalReader *self);

extern "C" int FUN_002f89e0(const char *);
struct IgbNameList { int vt; int rc; int count; int cap; int *data; int getCount() const { return count; } };
class IgbStream { public: virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3(); virtual void p4(); virtual void p5(); virtual void p6(); virtual void p7(); virtual void p8(); virtual void p9(); virtual void p10(); virtual void p11(); virtual void p12(); virtual void p13(); virtual void p14(); virtual void p15(); virtual void p16(); virtual void p17(); virtual void p18(); virtual void p19(); virtual void p20(); virtual void p21(); virtual void p22(); virtual void p23(); virtual void p24(); virtual int read(void *, int, int); };
class IgbSwapper { public: virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3(); virtual void p4(); virtual void p5(); virtual void p6(); virtual void p7(); virtual void p8(); virtual void p9(); virtual void p10(); virtual void p11(); virtual void p12(); virtual void p13(); virtual void p14(); virtual void p15(); virtual void p16(); virtual void p17(); virtual void p18(); virtual void p19(); virtual void p20(); virtual void p21(); virtual void p22(); virtual void p23(); virtual void p24(); virtual void p25(); virtual void p26(); virtual void p27(); virtual void p28(); virtual void p29(); virtual void p30(); virtual void p31(); virtual void p32(); virtual void p33(); virtual void p34(); virtual void p35(); virtual void p36(); virtual void p37(); virtual void p38(); virtual void p39(); virtual void p40(); virtual void p41(); virtual void p42(); virtual void p43(); virtual void p44(); virtual void p45(); virtual void p46(); virtual void p47(); virtual void p48(); virtual void p49(); virtual void swap(void *, int); };
class IgbPool { public: virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3(); virtual void p4(); virtual void p5(); virtual void p6(); virtual void p7(); virtual void p8(); virtual void p9(); virtual void p10(); virtual void p11(); virtual void p12(); virtual void p13(); virtual void p14(); virtual void p15(); virtual void p16(); virtual void p17(); virtual void p18(); virtual void p19(); virtual void p20(); virtual void p21(); virtual void p22(); virtual void p23(); virtual void p24(); virtual void p25(); virtual void p26(); virtual void p27(); virtual void p28(); virtual void p29(); virtual void p30(); virtual void p31(); virtual void p32(); virtual void p33(); virtual void p34(); virtual void p35(); virtual void p36(); virtual void p37(); virtual void p38(); virtual void p39(); virtual void p40(); virtual void p41(); virtual void p42(); virtual void p43(); virtual void p44(); virtual void p45(); virtual void p46(); virtual void p47(); virtual void p48(); virtual void p49(); virtual void p50(); virtual void p51(); virtual char *alloc(int); virtual void p53(); virtual void p54(); virtual void p55(); virtual void p56(); virtual void p57(); virtual void p58(); virtual void p59(); virtual void p60(); virtual void p61(); virtual void p62(); virtual void p63(); virtual void release(char *); };
struct NameHeader { int size; int count; };
struct IgbNameReader { char p0[104]; IgbStream *stream; char p108[60]; unsigned char swapped; char p169[35]; IgbSwapper *swapper; char p208[72]; IgbPool *pool; char p284[20]; IgbNameList *names; };
static inline void addName(IgbNameList *l, const int &v) {
    int idx = l->count;
    if (l->cap > idx) { l->count = l->getCount() + 1; } else { List_Resize(l, idx + 1, 4); }
    l->data[idx] = v;
}
extern "C" igResult FUN_002e91e0(IgbNameReader *self);


extern "C" int FUN_002e9470(void *arg0);

class E50 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void vX(int); };
struct O50 { int p0; int p1; int n; char pad[44]; unsigned char f56; };
extern "C" igResult FUN_002e94b0(O50 *arg1);

class DW4VC_148 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual int vX(void *); };
extern "C" igResult FUN_002e9560(void *arg1);

/* ReadFile(path): the Alchemy .igb loader driver. Logs "readFile(%s)", notes the clock, then runs
 * the section readers in file order (header, then the version-dependent tables, then the object
 * sections). A reader that fails sends the loader to its error path FUN_002e9470. After the last
 * reader the load time is reported once through the assert/log hook; an old-format file that still
 * has external references is reported once through the same hook. Each reader result is an unnamed
 * temporary with its own stack word. */

struct Device { int pad[3]; int name; };   /* name at +12 is what the old-format report prints */

struct File {
  virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27();
  virtual igResult v30();             /* +120 */
  virtual void v31();
  virtual void v32();
  virtual igResult readTail();        /* +132 */
  int pad4;
  int result;                         /* +8, returned on success */
  char pad12[36];
  unsigned char loading;              /* +48 */
  unsigned char loaded;               /* +49 */
  char pad50[6];
  unsigned char f56;
  char pad57[43];
  int version;                        /* +100, igb format version (the header reader caps it at 7) */
  Device *device;                     /* +104 */
  char pad108[105];
  unsigned char hasExternalRefs;      /* +213 */
  unsigned char f214;                 /* +214, selects the sectioned object reader */
  char pad215[62];
  unsigned char f277;
  char pad278[14];
  unsigned char f292;
};

extern "C" int igIGBFile_ReadFile(File *self, int path);

extern "C" int FUN_002d8f20(...);
extern "C" void Gap__Core__igIGBFile__vfunc_32(int *arg0, void *arg1);

struct S54 { char pad0[20]; int f20; char pad1[8]; int f32; char pad2[243]; unsigned char f279; };
extern "C" int FUN_0030a260(...);

extern "C" void Gap__Core__igIGBFile__vfunc_30(int *arg0, struct S54 *arg1);

class IgbInfoBase { public: virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3(); virtual void p4(); virtual void p5(); virtual void p6(); virtual void p7(); virtual void p8(); virtual void p9(); virtual void p10(); virtual void p11(); virtual void p12(); virtual void p13(); virtual void p14(); virtual void p15(); virtual void p16(); virtual void p17(); virtual void p18(); virtual void p19(); virtual void p20(); virtual void p21(); virtual void p22(); virtual void p23(); virtual void p24(); virtual void p25(); virtual void p26(); virtual void p27(); virtual void p28(); virtual igResult check(); };
class IgbInfoObject : public IgbInfoBase { public: int rc; };
struct IgbInfoList { int vt; int rc; int count; int cap; IgbInfoObject **data; };
class Ref55 { public: IgbInfoObject *p; Ref55(IgbInfoObject *o) : p(o) { if (p != 0) { p->rc = p->rc + 1; } }
 ~Ref55() { IgbInfoObject *object = p; if (object) { --object->rc; if (((unsigned long long)(long long)object->rc & 0x7fffffULL) == 0) igObject_Destroy(object); } } };
static inline IgbInfoObject *castInfo(IgbInfoObject *o) { if (o != 0 && igObject_IsKindOf(o, DAT_00586140[0]) != 0) { return o; } return 0; }
class IgbFileInfoView { public: virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3(); virtual void p4(); virtual void p5(); virtual void p6(); virtual void p7(); virtual void p8(); virtual void p9(); virtual void p10(); virtual void p11(); virtual void p12(); virtual void p13(); virtual void p14(); virtual void p15(); virtual void p16(); virtual void p17(); virtual void p18(); virtual void p19(); virtual void p20(); virtual void p21(); virtual void p22(); virtual void p23(); virtual void p24(); virtual void p25(); virtual void p26(); virtual void p27(); virtual igResult finish(); char pad[20]; IgbInfoList *list; };
extern "C" igResult Gap__Core__igIGBFile__vfunc_31(IgbFileInfoView *self);

struct IGB;
class VCa { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual int v220(int, int); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63(); virtual int v264(int); };
class VCb { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual int v164(void *); };
struct HDR { char pad32[32]; int f32; unsigned short f36; };
struct IGB { char pad8[8]; int f8; char pad12[92]; HDR *f104; char pad108[48]; int f156; char pad160[4]; int f164; char pad168[88]; int f256; int f260; int f264; int f268; int f272; char pad276[4]; VCa *f280; };
extern "C" int Gap__Core__igIGBFile__vfunc_34(IGB *o);

class P57 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual int vB(int, unsigned short); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63(); virtual void vA(int); };
struct Inf { char p0[28]; int f28; char p1[4]; unsigned short f36; };
struct IgbSectionBufferOwner { char p0[104]; Inf *f104; char p1[56]; int f164; char p2[92]; int f260; int f264; char p3[12]; P57 *f280; };
extern "C" igResult igIGBFile_GetSectionBuffer(IgbSectionBufferOwner *arg1, int arg2);

class VC58 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual int vX(void *); };
struct S58 { char pad8[8]; int cnt; char pad[244]; int f100; char pad2[8]; int f10c; int f110; };
extern "C" void Gap__Core__igIGBFile__vfunc_33(int *arg0, S58 *arg1);
