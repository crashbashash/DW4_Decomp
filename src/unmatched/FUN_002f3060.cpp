class igResult;
extern igResult DAT_004fb410;
extern igResult DAT_004fb418;
class igResult { public: int v; igResult(const igResult &o) : v(o.v) {} igResult(int x) : v(x) {}
    bool operator==(const igResult &o) const { return v == o.v; }
    inline bool isFailed(int &f) const; };
inline bool igResult::isFailed(int &f) const { f = DAT_004fb418.v; return *this == DAT_004fb418; }
extern "C" {
int FUN_002f8a50(int);
void *FUN_002f8a60(int, int);
void *FUN_002c01f0(int);
int igObject_GetAllocator(void *);
void igObject_Destroy(void *);
}
struct DirSlotObject { int vt; int rc; };
struct DirSourceRecord { char p0[20]; int id; };
class DirSlotTable { public: virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3(); virtual void p4(); virtual void p5(); virtual void p6(); virtual void p7(); virtual void p8(); virtual void p9(); virtual void p10(); virtual void p11(); virtual void p12(); virtual void p13(); virtual void p14(); virtual void p15(); virtual void p16(); virtual void p17(); virtual void p18(); virtual void p19(); virtual void p20(); virtual void p21(); virtual void p22(); virtual void p23(); virtual void p24(); virtual void p25(); virtual void p26(); virtual void p27(); virtual int slotFor(int); virtual void p29(); virtual void p30(); virtual void p31(); virtual void p32(); virtual void p33(); virtual void p34(); virtual igResult fillSlot(int, DirSourceRecord *, int);
  char q4[12]; DirSlotObject *slots; };
extern "C" igResult FUN_002f3060(DirSlotTable *self, int file, int arg) {
    int count = FUN_002f8a50(file);
    igResult result = DAT_004fb410;
    int fail;
    int i;
    if (self->slots == 0) {
        int allocator = igObject_GetAllocator(self);
        DirSlotObject *old = self->slots;
        if (old != 0) { old->rc = old->rc - 1; if (((unsigned long long)((long long)(int)old->rc << 0x29) >> 0x29) == 0) igObject_Destroy(old); }
        self->slots = (DirSlotObject *)FUN_002c01f0(allocator);
    }
    for (i = 0; i < count; i++) {
        DirSourceRecord *r;
        if ((r = (DirSourceRecord *)FUN_002f8a60(file, i)) != 0) {
            if (self->fillSlot(self->slotFor(r->id), r, arg).isFailed(fail)) {
                result.v = fail;
            }
        }
    }
    return result;
}
