class igResult;
extern igResult DAT_004fb410;
class igResult { public: int v; igResult(const igResult &o) : v(o.v) {} };
extern "C" void igObject_Destroy(void *);
struct IgbFixReader;
class IgbFixObject { public: virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3(); virtual void p4(); virtual void p5(); virtual void p6(); virtual void p7(); virtual void p8(); virtual void p9(); virtual void p10(); virtual void p11(); virtual void p12(); virtual void p13(); virtual void p14(); virtual void p15(); virtual void p16(); virtual void p17(); virtual void p18(); virtual void p19(); virtual void p20(); virtual void reset(int); virtual void p22(); virtual void p23(); virtual IgbFixObject *replacement(IgbFixReader *); virtual void attach(int); int rc; char q8[4]; int index; char q16[8]; int word; };
struct IgbFixWords { int vt; int rc; int count; int cap; int *data; };
struct IgbFixPlain { int vt; int rc; };
struct IgbFixRetain { IgbFixObject *p; IgbFixRetain(IgbFixObject *o) : p(o) { if (p != 0) { p->rc = p->rc + 1; } } };
struct IgbFixReader { char p0[8]; int count; char p12[4]; IgbFixObject **data; char p20[20]; IgbFixPlain *sorted; IgbFixWords *words; char p48[44]; IgbFixPlain *map; char p96[118]; unsigned char fixed; char p215[65]; int pool; };
extern "C" {
IgbFixWords *FUN_002c9130(int);
IgbFixPlain *FUN_002bd680(int);
IgbFixPlain *FUN_002c72c0(int);
void List_Resize(void *, int, int);
void List_InsertWords(IgbFixPlain *, int, int, IgbFixRetain *);
int FUN_00142bb0(IgbFixPlain *, IgbFixRetain *);
}
#define RELEASE(old) if (old != 0) { old->rc = old->rc - 1; if (((unsigned long long)((long long)(int)old->rc << 0x29) >> 0x29) == 0) igObject_Destroy(old); }
extern "C" igResult FUN_002e5110(IgbFixReader *self) {
    int n;
    int i;
    if (self->fixed != 0) { return DAT_004fb410; }
    {
        IgbFixWords *old = self->words;
        int pool = self->pool;
        RELEASE(old)
        self->words = FUN_002c9130(pool);
    }
    {
        int c = self->count;
        IgbFixWords *l = self->words;
        if (c >= 0) { if (c <= l->cap) { l->count = c; } else { List_Resize(l, c, 4); } }
    }
    {
        IgbFixPlain *old = self->map;
        int pool = self->pool;
        RELEASE(old)
        self->map = FUN_002bd680(pool);
    }
    {
        IgbFixPlain *old = self->sorted;
        int pool = self->pool;
        RELEASE(old)
        self->sorted = FUN_002c72c0(pool);
    }
    n = self->count;
    for (i = 0; i < n; i++) {
        IgbFixObject *o = self->data[i];
        IgbFixObject *r;
        IgbFixObject *old;
        int c;
        if (o == o->replacement(self)) {
            IgbFixPlain *list = self->sorted;
            IgbFixRetain keep(o);
            List_InsertWords(list, FUN_00142bb0(list, &keep), 1, &keep);
        }
        {
            int word;
            IgbFixWords *w = self->words;
            word = o->word;
            int k = w->count;
            if (k != 0 && i >= 0 && k > i) { w->data[i] = word; }
        }
        o->attach(o->word);
        o->reset(0);
        o->index = i;
        r = o->replacement(self);
        if (r != 0) { r->rc = r->rc + 1; }
        old = self->data[i];
        RELEASE(old)
        c = self->count;
        if (c != 0 && i >= 0 && c > i) { self->data[i] = r; }
    }
    self->fixed = 1;
    return DAT_004fb410;
}
