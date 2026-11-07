class igResult;
extern igResult DAT_004fb410;
extern igResult DAT_004fb418;
class igResult { public: int v; igResult(const igResult &o) : v(o.v) {}
    bool operator==(const igResult &o) const { return v == o.v; }
    inline bool isFailed(int &f) const; };
inline bool igResult::isFailed(int &f) const { f = DAT_004fb418.v; return *this == DAT_004fb418; }
class IgbSectionStream { public: virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3(); virtual void p4(); virtual void p5(); virtual void p6(); virtual void p7(); virtual void p8(); virtual void p9(); virtual void p10(); virtual void p11(); virtual void p12(); virtual void p13(); virtual void p14(); virtual void p15(); virtual void p16(); virtual void p17(); virtual void p18(); virtual void p19(); virtual void p20(); virtual void p21(); virtual void p22(); virtual void p23(); virtual void p24(); virtual int read(void *, int, int); };
class IgbSectionSwapper { public: virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3(); virtual void p4(); virtual void p5(); virtual void p6(); virtual void p7(); virtual void p8(); virtual void p9(); virtual void p10(); virtual void p11(); virtual void p12(); virtual void p13(); virtual void p14(); virtual void p15(); virtual void p16(); virtual void p17(); virtual void p18(); virtual void p19(); virtual void p20(); virtual void p21(); virtual void p22(); virtual void p23(); virtual void p24(); virtual void p25(); virtual void p26(); virtual void p27(); virtual void p28(); virtual void p29(); virtual void p30(); virtual void p31(); virtual void p32(); virtual void p33(); virtual void p34(); virtual void p35(); virtual void p36(); virtual void p37(); virtual void p38(); virtual void p39(); virtual void p40(); virtual void p41(); virtual void p42(); virtual void p43(); virtual void p44(); virtual void p45(); virtual void p46(); virtual void p47(); virtual void p48(); virtual void p49(); virtual void swap(void *, int); };
struct IgbSectionObject { int vt; int rc; };
struct IgbObjectSection { char p0[8]; int count; char p12[4]; IgbSectionObject **data; char p20[20]; int source; char p44[60];
  IgbSectionStream *stream; char p108[8]; int size; char p120[48]; unsigned char swapped; char p169[35]; IgbSectionSwapper *swapper; IgbSectionSwapper *swapper16; char p212[48]; int bufferCap; short *buffer; };
extern "C" {
igResult igIGBFile_GetSectionBuffer(IgbObjectSection *, int);
void ObjectList_ResizeRetained(IgbObjectSection *, int);
IgbSectionObject *thunk_FUN_002d7e90(int, int);
void igObject_Destroy(void *);
}
extern "C" void FUN_002e7640(int *out, IgbObjectSection *self) {
    int count = 0;
    int fail;
    int pos;
    int chunk;
    int words;
    int i;
    int base;
    self->stream->read(&self->size, 4, 1);
    self->stream->read(&count, 4, 1);
    if (self->swapped != 0) {
        self->swapper->swap(&self->size, 1);
        self->swapper->swap(&count, 1);
    }
    if (igIGBFile_GetSectionBuffer(self, 0x1000).isFailed(fail)) {
        *out = fail;
        return;
    }
    pos = 8;
    ObjectList_ResizeRetained(self, count);
    for (; pos < self->size; pos += chunk) {
        int rest = self->size - pos;
        chunk = self->bufferCap & ~1;
        if (chunk > rest) { chunk = rest; }
        words = chunk >> 1;
        self->stream->read(self->buffer, chunk, 1);
        if (self->swapped != 0) { self->swapper16->swap(self->buffer, words); }
        base = (unsigned int)(pos - 8) >> 1;
        for (i = 0; i < words; i++) {
            IgbSectionObject *o = thunk_FUN_002d7e90(self->source, self->buffer[i]);
            int index;
            IgbSectionObject *old;
            int n;
            if (o != 0) { o->rc = o->rc + 1; }
            index = i + base;
            old = self->data[index];
            if (old != 0) { old->rc = old->rc - 1; if (((unsigned long long)((long long)(int)old->rc << 0x29) >> 0x29) == 0) igObject_Destroy(old); }
            n = self->count;
            if (n != 0 && index >= 0 && n > index) { self->data[index] = o; }
        }
    }
    *out = DAT_004fb410.v;
}
