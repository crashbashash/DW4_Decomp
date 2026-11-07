class igResult;
extern igResult DAT_004fb410;
class igResult { public: int v; igResult(const igResult &o) : v(o.v) {}
    bool operator!=(const igResult &o) const { return v != o.v; } };
struct TrackerBuffer { char bytes[160]; };
extern "C" {
void FUN_002e2130(TrackerBuffer *);
void FUN_002e2300(TrackerBuffer *, int);
void FUN_00304430(char *);
void FUN_00304680();
int strlen(const char *);
}
class TrackerLockable { public: virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3(); virtual void p4(); virtual void p5(); virtual void p6(); virtual void p7(); virtual void p8(); virtual void p9(); virtual void p10(); virtual void p11(); virtual void p12(); virtual void p13(); virtual void p14(); virtual void p15(); virtual void p16(); virtual void p17(); virtual void p18(); virtual void p19(); virtual void p20(); virtual void p21(); virtual void p22(); virtual void p23(); virtual void p24(); virtual void p25(); virtual void p26(); virtual void p27(); virtual void p28(); virtual igResult unlock(); virtual void p30(); virtual igResult lock(int); };
class TrackerLockHold { public: TrackerLockable *m;
  TrackerLockHold(TrackerLockable *x) : m(x) { if (m != 0) { m->lock(1); } }
  ~TrackerLockHold() { if (m != 0) { m->unlock(); } } };
class EventTrackerText { public: virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3(); virtual void p4(); virtual void p5(); virtual void p6(); virtual void p7(); virtual void p8(); virtual void p9(); virtual void p10(); virtual void p11(); virtual void p12(); virtual void p13(); virtual void p14(); virtual void p15(); virtual void p16(); virtual void p17(); virtual void p18(); virtual void p19(); virtual void p20(); virtual void p21(); virtual void p22(); virtual void p23(); virtual void p24(); virtual igResult fill(int, TrackerBuffer *); virtual void p26(); virtual void p27(); virtual void p28(); virtual void p29(); virtual void p30(); virtual void p31(); virtual void p32(); virtual void p33(); virtual void p34(); virtual void p35(); virtual void format(TrackerBuffer *, char *, int);
  char q4[4]; TrackerLockable *lockable; char q12[792]; char text[1]; };
extern "C" void Gap__Core__igEventTracker__vfunc_41(EventTrackerText *self, int arg) {
    TrackerBuffer buf;
    FUN_002e2130(&buf);
    if (self->fill(arg, &buf) != DAT_004fb410) {
        FUN_002e2300(&buf, -1);
        return;
    }
    self->format(&buf, self->text, 0x2003);
    {
        TrackerLockHold hold(self->lockable);
        int len = strlen(self->text);
        int i;
        for (i = 0; i < len; i += 128) {
            char saved;
            char *at = (char *)self + 932 + i;
            saved = *at;
            *at = 0;
            FUN_00304430(self->text + i);
            FUN_00304680();
            *at = saved;
        }
    }
    FUN_002e2300(&buf, -1);
}
