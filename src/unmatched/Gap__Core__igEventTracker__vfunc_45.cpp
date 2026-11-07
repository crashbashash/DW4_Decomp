class igResult { public: int v; igResult(const igResult &o) : v(o.v) {} };
class TrackerCommandTable { public: virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3(); virtual void p4(); virtual void p5(); virtual void p6(); virtual void p7(); virtual void p8(); virtual void p9(); virtual void p10(); virtual void p11(); virtual void p12(); virtual void p13(); virtual void p14(); virtual void p15(); virtual void p16(); virtual void p17(); virtual void p18(); virtual void p19(); virtual void p20(); virtual int rowCount(); virtual void p22(); virtual int *rows(int); };
class EventTrackerRunner { public: virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3(); virtual void p4(); virtual void p5(); virtual void p6(); virtual void p7(); virtual void p8(); virtual void p9(); virtual void p10(); virtual void p11(); virtual void p12(); virtual void p13(); virtual void p14(); virtual void p15(); virtual void p16(); virtual void p17(); virtual void p18(); virtual void p19(); virtual void p20(); virtual void p21(); virtual void p22(); virtual void p23(); virtual void p24(); virtual void p25(); virtual void p26(); virtual void p27(); virtual void p28(); virtual void p29(); virtual void p30(); virtual void p31(); virtual void p32(); virtual void p33(); virtual void p34(); virtual void p35(); virtual void p36(); virtual void p37(); virtual igResult run(int, char *, int, int *, char *, int, int *);
  char q4[8]; int flags; char q16[56]; TrackerCommandTable *table; };
extern "C" void Gap__Core__igEventTracker__vfunc_45(EventTrackerRunner *self) {
    int a;
    int b;
    char bufA[256];
    char bufB[256];
    int count;
    int i;
    int *row;
    bool wasSet;
    count = self->table->rowCount();
    a = 0;
    b = 0;
    wasSet = (*(volatile int *)&self->flags & 2) != 0;
    self->flags |= 2;
    row = self->table->rows(0);
    if (row != 0) {
        for (i = 0; i < count; i++) {
            while (*row != 0) {
                self->run(*row, bufA, 255, &a, bufB, 255, &b);
                row++;
            }
            row++;
        }
        self->flags |= 4;
        { int f; if (wasSet) { f = self->flags | 2; } else { f = self->flags & ~2; } self->flags = f; }
    }
}
