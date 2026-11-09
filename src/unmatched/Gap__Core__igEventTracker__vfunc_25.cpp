extern "C" {
int FUN_002d3a20(int);
int FUN_0030d050(int);
int List_Resize(...);
}
struct R { int a; };
class EventTrackerLock { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual R Unlock(); virtual void d30(); virtual R Acquire(int wait); };
class VE { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void v200(int); };
struct EventTrackerScopedLock {
    EventTrackerLock *l;
    EventTrackerScopedLock(EventTrackerLock *m) { l = m; if (l != 0) { l->Acquire(1); } }
    ~EventTrackerScopedLock() { if (l != 0) { l->Unlock(); } }
};
struct Lst { int w[2]; int _count; int _capacity; };
struct P3 { int w[3]; int f12; };
struct E : VE { int f4; EventTrackerLock *lock; int w3[7]; int f40; int w11[2]; int f52; int f56; int f60; int f64; int f68; int f72; int f76; Lst *f80; P3 *f84; };
extern "C" void Gap__Core__igEventTracker__vfunc_25(E *arg0);
void Gap__Core__igEventTracker__vfunc_25(E *arg0) {
    EventTrackerScopedLock guard(arg0->lock);
    arg0->f40 = 0;
    FUN_0030d050(arg0->f52);
    FUN_0030d050(arg0->f56);
    FUN_0030d050(arg0->f68);
    FUN_0030d050(arg0->f64);
    FUN_0030d050(arg0->f68);
    FUN_002d3a20(arg0->f72);
    Lst *l = arg0->f80;
    if (0 <= l->_capacity) {
        l->_count = 0;
    } else {
        List_Resize(l, 0, 1);
    }
    arg0->v200(arg0->f84->f12);
}
