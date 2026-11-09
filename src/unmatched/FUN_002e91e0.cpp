extern "C" {
void igObject_Destroy(void *);
int List_Resize(void *, int, int);
int strlen(const char *);
int FUN_002f89e0(const char *);
}
struct IgbNameList { int vt; int rc; int count; int cap; int *data; int getCount() const { return count; } };
extern "C" IgbNameList *FUN_002caa70(int);
class igResult; 
extern igResult DAT_004fb410;
extern igResult DAT_004fb418;
extern int DAT_004c2140[4];
class igResult { public: int v; igResult(const igResult &o) : v(o.v) {} };
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
extern "C" igResult FUN_002e91e0(IgbNameReader *self) {
    NameHeader hdr;
    char *buf;
    char *name;
    int i;
    if (self->stream->read(&hdr, 8, 1) != 1) { return DAT_004fb418; }
    if (self->swapped != 0) { self->swapper->swap(&hdr, 2); }
    buf = self->pool->alloc(hdr.size);
    if (buf == 0) { return DAT_004fb418; }
    if (self->stream->read(buf, hdr.size - 8, 1) != 1) { self->pool->release(buf); return DAT_004fb418; }
    if (self->names != 0) {
        self->names->count = 0;
    } else {
        IgbNameList *old = self->names;
        IgbPool *pool = self->pool;
        if (old != 0) { old->rc = old->rc - 1; if (((unsigned long long)((long long)(int)old->rc << 0x29) >> 0x29) == 0) igObject_Destroy(old); }
        self->names = FUN_002caa70((int)pool);
    }
    name = buf;
    i = 0;
    while (hdr.count-- > 0) {
        addName(self->names, FUN_002f89e0(name));
        { int len = strlen(name) + 1; i++; name += len; }
    }
    for (; i < 46; i++) {
        int idx; IgbNameList *l; l = self->names; idx = l->count;
        if (l->cap > idx) { l->count = l->getCount() + 1; } else { List_Resize(l, idx + 1, 4); }
        l->data[idx] = DAT_004c2140[0];
    }
    self->pool->release(buf);
    return DAT_004fb410;
}
