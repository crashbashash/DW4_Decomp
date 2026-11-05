typedef struct Obj { int w0; int references; } Obj;
typedef struct S { char p0[48]; Obj *f48; Obj *f52; Obj **f56; unsigned int f60; char p64[8]; void *f72; } S;
int Memory_FreeBuffer();
int igObject_Destroy();

void FUN_0017a180(S *arg0) {
    /* matching construct: variant search — decl order [3, 2, 1, 0]; the unit compiler (combat build -O3 -Iinclude) assigns stack slots and registers in declaration order, the reverse of the 2001 default */
    int r;
    Obj *o;
    Obj **slot;
    unsigned int i;
    o = arg0->f52;
    if (o != 0) {
        o->references = o->references - 1;
        if (((unsigned long long)((long long)o->references << 0x29) >> 0x29) == 0) {
            igObject_Destroy(o);
        }
    }
    arg0->f52 = 0;
    o = arg0->f48;
    if (o != 0) {
        o->references = o->references - 1;
        if (((unsigned long long)((long long)o->references << 0x29) >> 0x29) == 0) {
            igObject_Destroy(o);
        }
    }
    arg0->f48 = 0;
    i = 0;
    if (arg0->f56 != 0) {
        for (; i < arg0->f60; i++) {
            slot = arg0->f56 + i;
            o = *slot;
            if (o != 0) {
                r = o->references - 1;
                o->references = r;
                r = o->references;
                if (((unsigned long long)((long long)r << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(o);
                }
            }
            *slot = 0;
        }
        Memory_FreeBuffer(arg0->f56);
    }
    if (arg0->f72 != 0) {
        Memory_FreeBuffer(arg0->f72);
    }
    arg0->f60 = 0;
}
