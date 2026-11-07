extern "C" {
void igObject_Destroy(void *);
int strlen(const char *);
char *strcpy(char *, const char *);
}
class igResult;
extern igResult DAT_004fb410;
class igResult { public: int v; igResult(const igResult &o) : v(o.v) {} };
struct ReflectedNameEntry { int vt; int rc; char *name; };
struct ReflectedRefTarget { int vt; int rc; int count; int cap; ReflectedNameEntry **data; };
struct ReflectedNameRegistry { char p0[44]; ReflectedRefTarget *names; };
extern ReflectedNameRegistry *DAT_00586dd0;
extern char *DAT_004c22f0;
class Ref { public: ReflectedRefTarget *p; Ref(ReflectedRefTarget *o) : p(o) { if (p != 0) { p->rc = p->rc + 1; } }
 ~Ref() { ReflectedRefTarget *object = p; if (object) { --object->rc; if (((unsigned long long)(long long)object->rc & 0x7fffffULL) == 0) igObject_Destroy(object); } } };
class IgbNamePool { public: virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3(); virtual void p4(); virtual void p5(); virtual void p6(); virtual void p7(); virtual void p8(); virtual void p9(); virtual void p10(); virtual void p11(); virtual void p12(); virtual void p13(); virtual void p14(); virtual void p15(); virtual void p16(); virtual void p17(); virtual void p18(); virtual void p19(); virtual void p20(); virtual void p21(); virtual void p22(); virtual void p23(); virtual void p24(); virtual void p25(); virtual void p26(); virtual void p27(); virtual void p28(); virtual void p29(); virtual void p30(); virtual void p31(); virtual void p32(); virtual void p33(); virtual void p34(); virtual void p35(); virtual void p36(); virtual void p37(); virtual void p38(); virtual void p39(); virtual void p40(); virtual void p41(); virtual void p42(); virtual void p43(); virtual void p44(); virtual void p45(); virtual void p46(); virtual void p47(); virtual void p48(); virtual void p49(); virtual void p50(); virtual void p51(); virtual void p52(); virtual int *alloc(int, int); };
class IgbNameSwapper { public: virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3(); virtual void p4(); virtual void p5(); virtual void p6(); virtual void p7(); virtual void p8(); virtual void p9(); virtual void p10(); virtual void p11(); virtual void p12(); virtual void p13(); virtual void p14(); virtual void p15(); virtual void p16(); virtual void p17(); virtual void p18(); virtual void p19(); virtual void p20(); virtual void p21(); virtual void p22(); virtual void p23(); virtual void p24(); virtual void p25(); virtual void p26(); virtual void p27(); virtual void p28(); virtual void p29(); virtual void p30(); virtual void p31(); virtual void p32(); virtual void p33(); virtual void p34(); virtual void p35(); virtual void p36(); virtual void p37(); virtual void p38(); virtual void p39(); virtual void p40(); virtual void p41(); virtual void p42(); virtual void p43(); virtual void p44(); virtual void p45(); virtual void p46(); virtual void p47(); virtual void p48(); virtual void p49(); virtual void swap(void *, int); };
struct IgbNameWriter { char p0[168]; unsigned char swapped; char p169[35]; IgbNameSwapper *swapper; char p208[28]; int *block; int blockSize; char p244[4]; int count; char p252[28]; IgbNamePool *pool; };
static inline char *nameOf(const Ref &r, int i) {
    char *n = r.p->data[i]->name;
    n = (n == 0) ? DAT_004c22f0 : n;
    return n;
}
extern "C" igResult FUN_002e4a40(IgbNameWriter *self) {
    Ref names(DAT_00586dd0->names);
    int i;
    int *lengths;
    char *out;
    self->count = (names.p != 0) ? names.p->count : 0;
    i = 0;
    self->blockSize = self->count * 4 + 12;
    for (; i < self->count; i++) {
        self->blockSize += strlen(nameOf(names, i)) + 1;
    }
    self->block = self->pool->alloc(self->blockSize, 16);
    {
        int *b = self->block;
        lengths = b + 3;
        b[0] = self->blockSize;
        b[1] = 1;
        b[2] = self->count;
    }
    for (i = 0; i < self->count; i++) {
        lengths[i] = strlen(nameOf(names, i)) + 1;
    }
    out = (char *)(lengths + self->count);
    for (i = 0; i < self->count; i++) {
        strcpy(out, nameOf(names, i));
        out += lengths[i];
    }
    if (self->swapped != 0) { self->swapper->swap(self->block, self->count + 3); }
    return DAT_004fb410;
}
