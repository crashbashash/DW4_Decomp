class igResult;
extern igResult DAT_004fb410;
extern igResult DAT_004fb418;
class igResult { public: int v; igResult(const igResult &o) : v(o.v) {}
    bool operator==(const igResult &o) const { return v == o.v; }
    inline bool isFailed(int &f) const; };
inline bool igResult::isFailed(int &f) const { f = DAT_004fb418.v; return *this == DAT_004fb418; }
class IgbSectionStream { public: virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3(); virtual void p4(); virtual void p5(); virtual void p6(); virtual void p7(); virtual void p8(); virtual void p9(); virtual void p10(); virtual void p11(); virtual void p12(); virtual void p13(); virtual void p14(); virtual void p15(); virtual void p16(); virtual void p17(); virtual void p18(); virtual void p19(); virtual void p20(); virtual void p21(); virtual void p22(); virtual void p23(); virtual void p24(); virtual int read(void *, int, int); };
class IgbSectionSwapper { public: virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3(); virtual void p4(); virtual void p5(); virtual void p6(); virtual void p7(); virtual void p8(); virtual void p9(); virtual void p10(); virtual void p11(); virtual void p12(); virtual void p13(); virtual void p14(); virtual void p15(); virtual void p16(); virtual void p17(); virtual void p18(); virtual void p19(); virtual void p20(); virtual void p21(); virtual void p22(); virtual void p23(); virtual void p24(); virtual void p25(); virtual void p26(); virtual void p27(); virtual void p28(); virtual void p29(); virtual void p30(); virtual void p31(); virtual void p32(); virtual void p33(); virtual void p34(); virtual void p35(); virtual void p36(); virtual void p37(); virtual void p38(); virtual void p39(); virtual void p40(); virtual void p41(); virtual void p42(); virtual void p43(); virtual void p44(); virtual void p45(); virtual void p46(); virtual void p47(); virtual void p48(); virtual void p49(); virtual void swap(void *, int); };
struct IgbRegistryObject;
class IgbRegistryMeta { public: char p0[28]; char *name; };
class IgbRegistryType { public: virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3(); virtual void p4(); virtual void p5(); virtual void p6(); virtual void p7(); virtual void p8(); virtual void p9(); virtual void p10(); virtual void p11(); virtual void p12(); virtual void p13(); virtual void p14(); virtual void p15(); virtual void p16(); virtual void p17(); virtual void p18(); virtual void p19(); virtual IgbRegistryMeta *meta(); };
struct IgbRegistryTable { char p0[8]; IgbRegistryType **data; int count; };
struct IgbTypeRefList { int vt; int rc; int count; };
struct IgbMetaSection { char p0[104]; IgbSectionStream *stream; char p108[28]; int entries; int bytes; char p144[24]; unsigned char swapped; char p169[15]; int *buffer; IgbTypeRefList *types; char p192[12]; IgbSectionSwapper *swapper; char p208[56]; int *work; char p268[12]; int pool; };
extern "C" {
igResult igIGBFile_GetSectionBuffer(IgbMetaSection *, int);
IgbRegistryTable *FUN_002fc250();
IgbTypeRefList *FUN_002c8af0(int);
void List_Reserve(void *, int, int);
void ObjectList_AppendRetained(IgbTypeRefList *, IgbRegistryType *);
void igObject_Destroy(void *);
int igStrCmp(char *, char *);
}
extern "C" void FUN_002e7f20(int *out, IgbMetaSection *self) {
    int fail;
    IgbRegistryTable *table;
    int count;
    int *sizes;
    char *name;
    int i;
    if (igIGBFile_GetSectionBuffer(self, self->bytes).isFailed(fail)) {
        *out = fail;
        return;
    }
    self->buffer = self->work;
    self->stream->read(self->buffer, self->bytes, 1);
    table = FUN_002fc250();
    count = table->count;
    sizes = self->buffer;
    name = (char *)sizes + self->entries * 12;
    if (self->swapped != 0) { self->swapper->swap(sizes, self->entries * 3); }
    {
        IgbTypeRefList *v = FUN_002c8af0(self->pool);
        IgbTypeRefList *old;
        if (v != 0) { v->rc = v->rc + 1; }
        old = self->types;
        if (old != 0) { old->rc = old->rc - 1; if (((unsigned long long)((long long)(int)old->rc << 0x29) >> 0x29) == 0) igObject_Destroy(old); }
        self->types = v;
    }
    {
        IgbTypeRefList *l = self->types;
        int want = self->entries;
        if (want >= l->count) { List_Reserve(l, want, 4); }
    }
    for (i = 0; i < self->entries; i++) {
        bool found = false;
        IgbRegistryType *t = 0;
        int j;
        for (j = 0; j < count; j++) {
            t = table->data[j];
            if (igStrCmp(t->meta()->name, name) == 0) { found = true; break; }
        }
        if (!found) { t = 0; } else { t->meta(); }
        ObjectList_AppendRetained(self->types, t);
        name += sizes[i * 3];
    }
    self->buffer = 0;
    *out = DAT_004fb410.v;
}
