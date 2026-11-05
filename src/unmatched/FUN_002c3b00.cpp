extern "C" {
struct T { int word0; int references; };
void igObject_Destroy(T *);
int StringChunk_ReleaseHeader(int, int *);
int thunk_FUN_002ed460__002ff810(void *);
extern int DAT_00530890[4];
}
struct R {
    T *ref;
    inline void release() {
        T **self = &ref;
        if (self) {
            T *object = ref;
            if (object) {
                --object->references;
                if (((unsigned long long)(long long)object->references & 0x7fffffULL) == 0)
                    igObject_Destroy(object);
            }
        }
    }
};
struct S {
    int *v;
    inline void release() {
        int **self = &v;
        if (self) {
            int *o = v;
            if (o) {
                int *h = o - 2;
                int c = o[-1] - 1;
                o[-1] = c;
                if (c == 0) StringChunk_ReleaseHeader(*h, h);
            }
        }
    }
};
struct Obj { int vt; char pad4[16]; S f14; R f18, f1c; char p20[8]; R f28, f2c; char p30[12]; R f3c; char p40[4]; R f44; };
extern "C" Obj *FUN_002c3b00(Obj *p, short n) {
    if (p) {
        p->vt = (int)&DAT_00530890[0];
        p->f44.release();
        p->f3c.release();
        p->f2c.release();
        p->f28.release();
        p->f1c.release();
        p->f18.release();
        p->f14.release();
        if (n > 0) thunk_FUN_002ed460__002ff810(p);
    }
    return p;
}
