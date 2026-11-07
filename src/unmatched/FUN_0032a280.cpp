struct DumpResult { int w; DumpResult() {} DumpResult(const DumpResult &o) : w(o.w) {} };
struct DumpRegion { unsigned start; int size; char name[80]; char kind[4]; };
struct DumpObject { int vt; int refCount; int count; int flags; void **data; int mask; };
class DumpSnapshotFile { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void Begin(); virtual void End(); virtual void d23(); virtual void Add(void *entry, int flags); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual DumpResult Write(char *path); };
class DumpOwner { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void Describe(char *text); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void CollectA(DumpObject *list); virtual void CollectB(DumpObject *list); virtual void CollectC(DumpObject *list); virtual void CollectD(DumpObject *list); };
extern "C" {
extern int DAT_00587030;
extern char DAT_004ff9f0[];
extern char DAT_004ffa00[];
extern char DAT_004ffa10[];
extern char DAT_004ffa30[];
extern char DAT_004ffa38[];
extern char DAT_004fac08[];
extern char DAT_004ffa40[];
extern char DAT_004ffa50[];
extern char DAT_004ffa60[];
extern char DAT_004f95c8[];
void FUN_00304430(const char *, ...);
void FUN_00304680(void);
int FUN_002f88e0(int);
DumpObject *FUN_002c9130(int);
DumpObject *FUN_002c5780(int);
void FUN_002d6680(DumpObject *, int, int);
void FUN_002dcc40(DumpObject *, int);
void FUN_002e2190(void *, int, void *, long long, int, int, int, int, char *, int, int, char *);
void FUN_002e2300(void *, int);
void FUN_0032a130(DumpRegion *, int);
void igObject_Destroy(DumpObject *);
void FUN_0032a280(DumpOwner *self, char *title, char *path, int a, int b, int c, int d);
}
struct DumpObjectRef {
    DumpObject *obj;
    DumpObjectRef() {}
    ~DumpObjectRef() {
        DumpObject *object = obj;
        if (object) {
            --object->refCount;
            if (((unsigned long long)(long long)object->refCount & 0x7fffffULL) == 0) {
                igObject_Destroy(object);
            }
        }
    }
};
void FUN_0032a280(DumpOwner *self, char *title, char *path, int a, int b, int c, int d) {
    char text[84];
    char region[160];
    int i;
    int count;
    DumpObjectRef list;
    FUN_00304430(DAT_004ffa00, title == 0 ? DAT_004ff9f0 : title);
    FUN_00304680();
    self->Describe(text);
    list.obj = FUN_002c9130(FUN_002f88e0(DAT_00587030));
    if (list.obj->count <= 1024) {
        FUN_002d6680(list.obj, 1024, 4);
    }
    if (a != 0) {
        self->CollectA(list.obj);
    }
    if (b != 0) {
        self->CollectB(list.obj);
    }
    if (c != 0) {
        self->CollectC(list.obj);
    }
    if (d != 0) {
        self->CollectD(list.obj);
    }
    count = list.obj->count;
    if (path != 0 && count != 0) {
        DumpObjectRef file;
        file.obj = FUN_002c5780(FUN_002f88e0(DAT_00587030));
        FUN_002dcc40(file.obj, list.obj->count);
        file.obj->flags |= 0x10;
        file.obj->mask = -33;
        ((DumpSnapshotFile *)file.obj)->Begin();
        for (i = 0; i < count; i++) {
            DumpRegion *e = (DumpRegion *)list.obj->data[i];
            FUN_002e2190(region, 1, (void *)e->start, e->size, 0, 0, 0, 0, e->name, 0, 0, e->kind);
            ((DumpSnapshotFile *)file.obj)->Add(region, 0);
            FUN_002e2300(region, -1);
        }
        ((DumpSnapshotFile *)file.obj)->Write(path);
        ((DumpSnapshotFile *)file.obj)->End();
    }
    FUN_00304430(DAT_004ffa10, DAT_004ffa30, DAT_004ffa38, DAT_004fac08, DAT_004ffa40, DAT_004ffa50);
    FUN_00304680();
    for (i = 0; i < count; i++) {
        DumpRegion *e = (DumpRegion *)list.obj->data[i];
        FUN_00304430(DAT_004ffa60, e->start, e->start + e->size, e->size, e->kind, e->name);
        FUN_00304680();
        FUN_0032a130(e, 1);
    }
    FUN_00304430(DAT_004f95c8);
    FUN_00304680();
}
