struct S { int f0; int f4; int f8; int f12; };
struct P { int pad; struct C *head; };
struct C { int pad; struct C *next; };
typedef struct StringPool {
    int table;
    int chunks;
} StringPool;

class DW4VC_216_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual int vX(int); };
class DW4VC_264_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63(); virtual int vX(int); };

extern "C" {
void **Memory_GetAllocatorBySelector(...);
int Memory_GetDefaultAllocator(...);
int StringChunk_AllocateObject(...);
int StringChunk_Construct(...);
int StringChunk_Destroy(...);
int StringChunk_AllocateToken(int chunks, int size, int *out_a, int *out_b);
int StringTable_AllocateObject(...);
int StringTable_Construct(...);
void *StringTable_Destroy(...);
int StringTable_Find(int table, const char *name);
void StringTable_Register(int table, int a, int b, int copy);
int strlen(const char *s);
void *memcpy(void *dst, const void *src, int n);
void StringPool_DestroyChunks(struct P *arg0);
void FUN_002eb050(int arg0);
extern int DAT_00587048[4];
extern unsigned char GPR_00554c14;

struct S *StringPool_Construct(struct S *arg0) {
    int var_v0;
    int var_v0_2;
    int var_v0_3;

    arg0->f0 = 0;
    arg0->f4 = 0;
    arg0->f8 = 0x4000;
    arg0->f12 = 0;
    var_v0 = arg0->f12;
    var_v0 = GPR_00554c14 != 0 ? var_v0 : (int)Memory_GetAllocatorBySelector(DAT_00587048[0]);
    arg0->f12 = var_v0;
    if (arg0->f12 == 0) {
        arg0->f12 = Memory_GetDefaultAllocator();
    }
    var_v0_2 = StringTable_AllocateObject(0x18, arg0->f12);
    if (var_v0_2 != 0) {
        var_v0_2 = StringTable_Construct(var_v0_2, arg0, 0x400);
    }
    arg0->f0 = var_v0_2;
    var_v0_3 = StringChunk_AllocateObject(0x24, arg0->f12);
    if (var_v0_3 != 0) {
        var_v0_3 = StringChunk_Construct(var_v0_3, 0, arg0->f0, arg0->f8);
    }
    arg0->f4 = var_v0_3;
    return arg0;
}

int *StringPool_Destroy(int *self, long long delete_flag) {
    if (self != 0) {
        StringPool_DestroyChunks((struct P *)self);
        StringTable_Destroy((void *)*self, 1);
        if ((short)delete_flag > 0) {
            FUN_002eb050((int)self);
        }
    }
    return self;
}

void StringPool_DestroyChunks(struct P *arg0) {
    struct C *c = arg0->head;
    while (c != 0) {
        struct C *t = c;
        c = c->next;
        StringChunk_Destroy(t, 1);
    }
}

int StringPool_Intern(StringPool *pool, const char *name)
{
    int token, hash;
    int copy, size;

    if (name == 0) {
        return 0;
    }
    token = 0;
    copy = StringTable_Find(pool->table, name);
    if (copy == 0) {
        hash = 0;
        size = strlen(name) + 1;
        copy = StringChunk_AllocateToken(pool->chunks, size, &hash, &token);
        memcpy((void *)copy, name, size);
        StringTable_Register(pool->table, token, hash, copy);
    }
    return copy;
}

void FUN_002eb010(int arg0) {
    void **temp_v0;

    temp_v0 = (void **)(Memory_GetAllocatorBySelector(DAT_00587048[0]));
    ((DW4VC_216_1 *)(temp_v0))->vX((int)(arg0));
}

void FUN_002eb050(int arg0) {
    void **temp_v0;

    temp_v0 = (void **)(Memory_GetAllocatorBySelector(DAT_00587048[0]));
    ((DW4VC_264_1 *)(temp_v0))->vX((int)(arg0));
}
}
