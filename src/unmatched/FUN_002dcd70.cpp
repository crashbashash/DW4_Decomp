struct LockStatus { int a; };
struct ScopedLockObject { virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual LockStatus unlock(); virtual void d30(); virtual LockStatus acquire(int); };
struct ScopedLock {
    ScopedLockObject *l;
    ScopedLock(ScopedLockObject *m) { l = m; if (l != 0) { l->acquire(1); } }
    ~ScopedLock() { if (l != 0) { l->unlock(); } }
};
struct W {
    char p0[8]; ScopedLockObject *lock; unsigned flags; char p1[40]; int h; char p2[9200]; char buf[256]; int res;
    bool isBusy() const { return flags & 2; }
};
extern "C" {
int strncpy(char *, int, int);
int FUN_0030d300(int, char *);
void FUN_002dcd70(W *arg0, int arg1) {
    ScopedLock guard(arg0->lock);
    if (arg0->isBusy() != false) {
        return;
    }
    arg0->flags = arg0->flags | 2;
    if (arg1 != 0) {
        strncpy(arg0->buf, arg1, 0xFF);
    } else {
        arg0->buf[0] = 0;
    }
    if (arg0->buf[0] != 0) {
        arg0->res = FUN_0030d300(arg0->h, arg0->buf);
    } else {
        arg0->res = -1;
    }
    arg0->flags = arg0->flags & ~2;
}
}
