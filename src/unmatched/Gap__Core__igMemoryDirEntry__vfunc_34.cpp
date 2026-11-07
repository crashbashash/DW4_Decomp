extern "C" int igObject_IsKindOf(void *, int);
extern int DAT_00585a60[4];
extern int DAT_00585b20[4];
struct MemoryDirReader;
class MemoryDirField { public: virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3(); virtual void p4(); virtual void p5(); virtual void p6(); virtual void p7(); virtual void p8(); virtual void p9(); virtual void p10(); virtual void p11(); virtual void p12(); virtual void p13(); virtual void p14(); virtual void p15(); virtual void p16(); virtual void p17(); virtual void p18(); virtual void p19(); virtual void p20(); virtual void p21(); virtual void p22(); virtual void p23(); virtual void p24(); virtual void p25(); virtual void p26(); virtual void p27(); virtual void p28(); virtual void p29(); virtual void p30(); virtual void p31(); virtual void p32(); virtual void p33(); virtual void p34(); virtual void p35(); virtual void p36(); virtual void p37(); virtual void p38(); virtual void p39(); virtual void p40(); virtual void p41(); virtual void p42(); virtual void p43(); virtual void p44(); virtual void p45(); virtual void p46(); virtual void p47(); virtual void p48(); virtual void fix(int, int, MemoryDirReader *, unsigned char); virtual void swapArray(int, int);
 char q4[16]; unsigned short elementSize; char q22[38]; unsigned char swapFlag; };
struct MemoryDirList { char p0[16]; MemoryDirField **data; };
struct MemoryDirReader { char p0[168]; unsigned char swapped; char p169[19]; MemoryDirList *fields; };
struct MemoryDirEntryView { char p0[24]; int base; int size; char p32[4]; MemoryDirField *field; int fieldIndex; char p44[8]; unsigned char swapFlag; };
extern "C" void Gap__Core__igMemoryDirEntry__vfunc_34(MemoryDirEntryView *self, MemoryDirReader *r) {
    MemoryDirField *f = r->fields->data[self->fieldIndex];
    self->field = f;
    if (((igObject_IsKindOf(f, DAT_00585a60[0]) != 0) ^ 1) && r->swapped != 0) {
        f->swapArray(self->base, self->size / f->elementSize);
    }
    if (igObject_IsKindOf(f, DAT_00585a60[0]) != 0) {
        int esize = f->elementSize;
        int count = self->size / esize;
        int base = self->base;
        unsigned char saved = 0;
        int isSwap = igObject_IsKindOf(f, DAT_00585b20[0]) & 0xff;
        int i;
        if (isSwap != 0) {
            saved = f->swapFlag;
            f->swapFlag = self->swapFlag;
        }
        for (i = 0; i < count; i++) {
            int p = base + i * esize;
            f->fix(p, p, r, r->swapped);
        }
        if (isSwap != 0) {
            f->swapFlag = saved;
        }
    }
}
