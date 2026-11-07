class igResult;
extern igResult DAT_004fb410;
class igResult { public: int v; igResult(const igResult &o) : v(o.v) {} };
extern "C" void igObject_Destroy(void *);
extern int DAT_004c2130[4];
extern int DAT_004c2138[4];
extern int DAT_00587198[4];
struct MetaTableField { char p0[18]; short size; unsigned short offset; char p22[15]; unsigned char inherited; unsigned char persistent; };
struct MetaTableFieldList { char p0[8]; MetaTableField **data; int count; };
struct MetaTableType { char p0[16]; int a16; int a20; char p24[4]; char *name; char p32[8]; MetaTableFieldList *fields; char p44[12]; int parent; };
struct MetaTableTypeList { int vt; int rc; int count; int cap; MetaTableType **data; };
struct MetaTableWords { int vt; int rc; int count; int cap; int *data; };
struct MetaTableRecord { int nameSize; int a4; int a8; int fieldCount; int parent; int persistCount; };
class MetaTableSwapper { public: virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3(); virtual void p4(); virtual void p5(); virtual void p6(); virtual void p7(); virtual void p8(); virtual void p9(); virtual void p10(); virtual void p11(); virtual void p12(); virtual void p13(); virtual void p14(); virtual void p15(); virtual void p16(); virtual void p17(); virtual void p18(); virtual void p19(); virtual void p20(); virtual void p21(); virtual void p22(); virtual void p23(); virtual void p24(); virtual void p25(); virtual void p26(); virtual void p27(); virtual void p28(); virtual void p29(); virtual void p30(); virtual void p31(); virtual void p32(); virtual void p33(); virtual void p34(); virtual void p35(); virtual void p36(); virtual void p37(); virtual void p38(); virtual void p39(); virtual void p40(); virtual void p41(); virtual void p42(); virtual void p43(); virtual void p44(); virtual void p45(); virtual void p46(); virtual void p47(); virtual void p48(); virtual void p49(); virtual void swap(void *, int); };
class MetaTablePool { public: virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3(); virtual void p4(); virtual void p5(); virtual void p6(); virtual void p7(); virtual void p8(); virtual void p9(); virtual void p10(); virtual void p11(); virtual void p12(); virtual void p13(); virtual void p14(); virtual void p15(); virtual void p16(); virtual void p17(); virtual void p18(); virtual void p19(); virtual void p20(); virtual void p21(); virtual void p22(); virtual void p23(); virtual void p24(); virtual void p25(); virtual void p26(); virtual void p27(); virtual void p28(); virtual void p29(); virtual void p30(); virtual void p31(); virtual void p32(); virtual void p33(); virtual void p34(); virtual void p35(); virtual void p36(); virtual void p37(); virtual void p38(); virtual void p39(); virtual void p40(); virtual void p41(); virtual void p42(); virtual void p43(); virtual void p44(); virtual void p45(); virtual void p46(); virtual void p47(); virtual void p48(); virtual void p49(); virtual void p50(); virtual void p51(); virtual void p52(); virtual MetaTableRecord *alloc(int, int); };
struct MetaTableWriter { char p0[128]; int count; int size; char p136[32]; unsigned char swapped; char p169[3]; MetaTableRecord *block; char p176[16]; MetaTableTypeList *types; char p196[8]; MetaTableSwapper *swapper; char p208[72]; MetaTablePool *pool; };
extern "C" {
MetaTableWords *FUN_002caa70(MetaTablePool *);
void List_Resize(void *, int, int);
int igMetaObject_GetFieldCount(int);
MetaTableSwapper *igShortMetaField_GetDefaultDescriptor();
short igMetaField_GetTypeIndex(MetaTableField *);
int strlen(const char *);
char *strcpy(char *, const char *);
}
class Ref { public: MetaTableWords *p; Ref(MetaTableWords *o) : p(o) { }
 ~Ref() { MetaTableWords *object = p; if (object) { --object->rc; if (((unsigned long long)(long long)object->rc & 0x7fffffULL) == 0) igObject_Destroy(object); } } };
static inline void bump(const Ref &r, int off) { int *c = (int *)((char *)r.p->data + off); *c = *c + 1; }
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
extern "C" igResult FUN_002e42d0(MetaTableWriter *self) {
    int base;
    int i;
    self->count = self->types->count;
    self->size = self->count * 24;
    {
    Ref inherited(FUN_002caa70(self->pool));
    fillWords(inherited.p, self->count, 0);
    {
        int n = inherited.p->count;
        int *d = inherited.p->data;
        int k;
        for (k = 0; k < n; k++) { d[k] = DAT_004c2130[0]; }
    }
    {
    Ref persistent(FUN_002caa70(self->pool));
    fillWords(persistent.p, self->count, 0);
    {
        int n = persistent.p->count;
        int *d = persistent.p->data;
        int k;
        for (k = 0; k < n; k++) { d[k] = DAT_004c2138[0]; }
    }
    base = igMetaObject_GetFieldCount(DAT_00587198[0]);
    for (i = 0; i < self->count; i++) {
        int j;
        MetaTableFieldList *fields;
        int n;
        MetaTableType *t;
        int off;
        off = i * 4;
        t = *(MetaTableType **)((char *)self->types->data + off);
        fields = t->fields;
        n = fields->count;
        for (j = base; j < n; j++) {
            MetaTableField *f = fields->data[j];
            if (f->inherited == 0) {
                if (f->persistent != 0) {
                    self->size = self->size + 6;
                    bump(inherited, off);
                }
                bump(persistent, off);
            }
        }
        self->size = self->size + (strlen(t->name) + 1);
        self->size = (self->size + 1) & ~1;
    }
    self->block = self->pool->alloc(self->size, 16);
    {
        MetaTableType *t;
        int off;
        int k;
        MetaTableRecord *rec = self->block;
        for (k = 0; k < self->count; k++) {
            MetaTableKey key;
            int len;
            off = k * 4;
            t = *(MetaTableType **)((char *)self->types->data + off);
            len = strlen(t->name) + 1;
            rec->nameSize = (len + 1) & ~1;
            rec->a4 = t->a16;
            rec->a8 = t->a20;
            rec->fieldCount = *(int *)((char *)inherited.p->data + off);
            {
                MetaTableTypeList *l = self->types;
                *(int *)&key = t->parent;
                rec->parent = indexOfParent(l, key);
            }
            rec->persistCount = base + *(int *)((char *)persistent.p->data + off);
            rec++;
        }
    }
    {
        char *out = (char *)(self->block + self->count);
        MetaTableSwapper *desc;
        short *p;
        MetaTableField *f;
        int k;
        int j;
        int n;
        int off;
        MetaTableType *t;
        MetaTableFieldList *fields;
        desc = igShortMetaField_GetDefaultDescriptor();
        for (k = 0; k < self->count; k++) {
            off = k * 4;
            t = *(MetaTableType **)((char *)self->types->data + off);
            strcpy(out, t->name);
            fields = t->fields;
            j = base;
            n = fields->count;
            out += self->block[k].nameSize;
            p = (short *)out;
            for (; j < n; j++) {
                f = fields->data[j];
                if (f->persistent != 0 && f->inherited == 0) {
                    p[0] = igMetaField_GetTypeIndex(f);
                    p[1] = f->size;
                    p[2] = f->offset;
                    p += 3;
                }
            }
            if (self->swapped != 0) {
                desc->swap(out, *(int *)((char *)inherited.p->data + off) * 3);
            }
            out = (char *)p;
        }
    }
    if (self->swapped != 0) { self->swapper->swap(self->block, self->count * 6); }
    return DAT_004fb410;
    }
    }
}
