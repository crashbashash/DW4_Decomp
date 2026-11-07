class igResult;
extern igResult DAT_004fb410;
extern igResult DAT_004fb418;
class igResult { public: int v; igResult(const igResult &o) : v(o.v) {} igResult(int x) : v(x) {}
    bool operator==(const igResult &o) const { return v == o.v; }
    inline bool isFailed(int &f) const; };
inline bool igResult::isFailed(int &f) const { f = DAT_004fb418.v; return *this == DAT_004fb418; }
extern "C" {
void *FUN_002eb010(int);
void *StringPool_Construct(void *);
char *StringPool_Intern(void *, char *);
void StringChunk_ReleaseHeader(int, void *);
}
extern void *DAT_00586f20;
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
extern "C" {
IgbExternalDir *FUN_00309a50();
int FUN_00308fb0(IgbExternalDir *, char *);
void ObjectList_AppendRetained(int, int);
}
extern "C" igResult FUN_002e8e50(IgbExternalReader *self) {
    if (self->hasExternals != 0) {
        IgbExternalHeader hdr;
        int count;
        int *sizes;
        char *name;
        int i;
        IgbExternalDir *dir;
        if (self->stream->read(&hdr, 12, 1) != 1) { return DAT_004fb418; }
        if (self->swapped != 0) { self->swapper->swap(&hdr, 3); }
        self->bytes = hdr.size - 12;
        count = hdr.count;
        self->buffer = self->pool->alloc(self->bytes, 16);
        if (self->stream->read(self->buffer, self->bytes, 1) != 1) { return DAT_004fb418; }
        sizes = self->buffer;
        if (self->swapped != 0) { self->swapper->swap(sizes, count); }
        name = (char *)sizes + count * 4;
        if (self->dir == 0) { self->dir = FUN_00309a50(); }
        if (self->dir != 0) {
            setPooled(&self->savedPath, self->dir->path);
            { char *n; n = self->name; dir = self->dir; setPooled(&dir->path, n); }
        }
        for (i = 0; i < count; i++) {
            ObjectList_AppendRetained(self->list, FUN_00308fb0(self->dir, name));
            name += sizes[i];
        }
        self->pool->release(self->buffer);
        self->buffer = 0;
        dir = self->dir;
        if (dir != 0) {
            setPooled(&dir->path, self->savedPath);
            setPooled(&self->savedPath, 0);
        }
    }
    return DAT_004fb410;
}
