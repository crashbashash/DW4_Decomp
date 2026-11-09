struct igResult { int value; };
struct Lockable { virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual igResult unlock(); virtual void d30(); virtual igResult lock(int); };
struct ScopedLock {
    Lockable *lockable;
    ScopedLock(Lockable *l) : lockable(l) {
        Lockable *o = lockable;
        if (o != 0) { o->lock(1); }
    }
    ~ScopedLock() {
        Lockable *o = lockable;
        if (o != 0) { o->unlock(); }
    }
};
struct FileRequest {
    char p0[8];
    Lockable *mutex;
    unsigned flags;
    char p1[36];
    int handle;
    char p2[8944];
    char path[256];
    int result;
    bool busy() const { return flags & 2 ? true : false; }
};
extern "C" {
int strncpy(char *, int, int);
int FUN_0030d300(int, char *);
void FUN_002dcc60(FileRequest *request, int path) {
    ScopedLock guard(request->mutex);
    if (request->busy()) {
        return;
    }
    request->flags = request->flags | 2;
    if (path != 0) {
        strncpy(request->path, path, 0xFF);
    } else {
        request->path[0] = 0;
    }
    if (request->path[0] != 0) {
        request->result = FUN_0030d300(request->handle, request->path);
    } else {
        request->result = -1;
    }
    request->flags = request->flags & ~2;
}
}
