extern "C" {
void *FUN_002bfed0(int);
void FUN_002f8a80(int, void *);
void FUN_002f8b20(int);
void igObject_Destroy(void *);
int igObject_GetAllocator(int);
}
class igResult; extern igResult DAT_004fb418;
class igResult { public: int v; igResult(const igResult &o) : v(o.v) {} inline bool isFailed(int &f) const; bool operator==(const igResult &o) const { return v == o.v; } };
extern igResult DAT_004fb410;
extern igResult DAT_004fb418;
inline bool igResult::isFailed(int &f) const { f = DAT_004fb418.v; return *this == DAT_004fb418; }
struct igRefHead { int vt; int rc; };
class SlotReadTable { public: virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3(); virtual void p4(); virtual void p5(); virtual void p6(); virtual void p7(); virtual void p8(); virtual void p9(); virtual void p10(); virtual void p11(); virtual void p12(); virtual void p13(); virtual void p14(); virtual void p15(); virtual void p16(); virtual void p17(); virtual void p18(); virtual void p19(); virtual void p20(); virtual void p21(); virtual void p22(); virtual void p23(); virtual void p24(); virtual void p25(); virtual void p26(); virtual void p27(); virtual void p28(); virtual void p29(); virtual void p30(); virtual void p31(); virtual void p32(); virtual void p33(); virtual igResult readOne(int, igRefHead *);
};
extern "C" igResult FUN_002f2f40(SlotReadTable *self, int file) {
    igResult result = DAT_004fb410;
    int i;
    FUN_002f8b20(file);
    for (i = 0; i < 46; i++) {
        if (*(int *)((char *)self + i * 144 + 152) != 0) {
            igRefHead *o = (igRefHead *)FUN_002bfed0(igObject_GetAllocator(file));
            int fail;
            if (self->readOne(i, o).isFailed(fail)) {
                o->rc = o->rc - 1;
                result.v = fail;
                if (((unsigned long long)((long long)(int)o->rc << 0x29) >> 0x29) == 0) igObject_Destroy(o);
            } else {
                FUN_002f8a80(file, o);
            }
        }
    }
    return result;
}
