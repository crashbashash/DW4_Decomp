extern "C" {
void *Memory_GetAllocatorByName(const char *name);
void *FUN_002ed2b0(int size, int alignment, void *allocator);
void FUN_00332e90(int stream, const char *name);
void FUN_00260de8(int stream, const char *name, int mode, void *buffer);
int FUN_002612c0(int stream);
void FUN_00332cf0(int);
int StringChunk_ReleaseHeader(int, int *);
extern unsigned char GPR_00554de8;
extern char DAT_004ffe68[];
extern void **DAT_005875f0[4];
extern int DAT_00587608[4];
}

class StringRef {
public:
    char *p;
    ~StringRef() { if (p) { int *h = (int *)p - 2; int r = ((int *)p)[-1] - 1; ((int *)p)[-1] = r; if (r == 0) StringChunk_ReleaseHeader(*h, h); } }
    operator char *() const { return p; }
};
extern "C" StringRef StringList_CopyRetained(int list, int index);

struct WaitResult { int code; };
class AdxThread {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5();
    virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11();
    virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17();
    virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22();
    virtual WaitResult sleep(int microseconds);
};
struct ThreadList { char pad[16]; AdxThread **data; };
struct ThreadManager { char pad[8]; ThreadList *threads; };
extern "C" ThreadManager *DAT_005871d0[4];

extern "C" int FUN_003332b0(int stream, const char *path, int mode, int length)
{
    int size;
    char *name;
    bool waiting;

    if (!GPR_00554de8) return 0;
    size = ((length + 1) * 2 + 282) & ~3;
    if (size > 0) {
        DAT_005875f0[0][stream] = FUN_002ed2b0(size, 16, Memory_GetAllocatorByName(DAT_004ffe68));
    }
    FUN_00332e90(stream, path);
    name = StringList_CopyRetained(DAT_00587608[0], stream).p;
    FUN_00260de8(stream, name, mode, DAT_005875f0[0][stream]);
    waiting = true;
    do {
        switch (FUN_002612c0(stream)) {
        case 3:
            waiting = false;
            break;
        case 4:
            return 0;
        default:
            FUN_00332cf0(0);
            break;
        }
        DAT_005871d0[0]->threads->data[0]->sleep(3333333);
    } while (waiting);
    return 1;
}
