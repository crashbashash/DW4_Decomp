extern "C" {
void igObject_Destroy(void *);
int strcmp(char *, char *);
void List_Reserve(void *, int, int);
void List_Resize(void *, int, int);
}
class igResult;
extern igResult DAT_004fb410;
extern igResult DAT_004fb418;
class igResult { public: int v; igResult(const igResult &o) : v(o.v) {} };
struct ReflectedRefObject { int vt; int rc; };
struct ReflectedNameObject { int vt; int rc; char *name; };
struct ReflectedNameList { int vt; int rc; int count; int cap; ReflectedNameObject **data; };
struct ReflectedValueList { int vt; int rc; int count; int cap; int *data; };
struct ReflectedTypeList { int vt; int rc; int count; int cap; int *data; };
struct ReflectedRegistry { char p0[44]; ReflectedNameList *names; ReflectedValueList *values; };
extern ReflectedRegistry *DAT_00586dd0;
extern char *DAT_004c22f0;
extern "C" ReflectedTypeList *FUN_002caa70(int);
class Ref { public: ReflectedRefObject *p; Ref(void *o) : p((ReflectedRefObject *)o) { if (p != 0) { p->rc = p->rc + 1; } }
 ~Ref() { ReflectedRefObject *object = p; if (object) { --object->rc; if (((unsigned long long)(long long)object->rc & 0x7fffffULL) == 0) igObject_Destroy(object); } } };
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
    if (l->cap > idx) { ++*(volatile int *)&l->count; } else { List_Resize(l, idx + 1, 4); }
    l->data[idx] = v;
}
extern "C" igResult FUN_002e82a0(IgbTypeReader *self) {
    IgbTypeHeader hdr;
    int *sizes;
    char *name;
    int value;
    int nameCount;
    int i;
    if (self->stream->read(&hdr, 12, 1) != 1) { return DAT_004fb418; }
    if (self->swapped != 0) { self->swapper->swap(&hdr, 3); }
    self->bufferSize = hdr.size - 12;
    self->typeCount = hdr.count;
    if (self->typeCount <= 0) { return DAT_004fb410; }
    self->buffer = self->work;
    if (self->stream->read(self->buffer, self->bufferSize, 1) != 1) { return DAT_004fb418; }
    sizes = self->buffer;
    if (self->swapped != 0) { self->swapper->swap(sizes, self->typeCount); }
    name = (char *)sizes + self->typeCount * 4;
    {
    Ref names(DAT_00586dd0->names);
    Ref values(DAT_00586dd0->values);
    nameCount = 0;
    if (names.p != 0) { nameCount = ((ReflectedNameList *)names.p)->count; }
    {
        TypeListHolder h(FUN_002caa70(self->pool));
        assignTypes(self, h);
    }
    {
        ReflectedTypeList *l = self->types;
        int want = self->typeCount;
        if (want >= l->count) { List_Reserve(l, want, 4); }
    }
    for (i = 0; i < self->typeCount; i++) {
        bool found = false;
        value = 16;
        int j;
        for (j = 0; j < nameCount; j++) {
            char *n = ((ReflectedNameList *)names.p)->data[j]->name;
            n = (n == 0) ? DAT_004c22f0 : n;
            if (strcmp(n, name) == 0) { found = true; break; }
        }
        if (found) { value = ((ReflectedValueList *)values.p)->data[j]; }
        addType(self->types, value);
        name += sizes[i];
    }
    self->buffer = 0;
    return DAT_004fb410;
    }
}
