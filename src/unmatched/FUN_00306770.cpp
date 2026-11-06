/* Stores a shared object reference into *arg3: the existing node's reference when FUN_00307c10
 * finds one, else a freshly built object held in a stack slot; returns whether a node existed;
 * alternate compiler -O3. */
extern "C" {
struct T { int word0; int references; };
void igObject_Destroy(T *);
struct Node { char p[12]; T *f12; };
Node *FUN_00307c10(int, int, int, int);
int igObject_GetAllocator(int);
T *FUN_002b9500(int);
int FUN_0030b3c0(T *, int);
int FUN_00307700(int, int, int, int);
}
struct Holder {
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
extern "C" int FUN_00306770(int arg0, int arg1, int arg2, T **arg3, int arg4, int arg5) {
    Node *node;
    T *t;
    T *old;
    Holder h;
    node = FUN_00307c10(arg0, arg1, arg2, 0);
    if (node != 0) {
        t = node->f12;
        if (t) {
            ++t->references;
        }
        old = *arg3;
        if (old) {
            --old->references;
            if (((unsigned long long)(long long)old->references & 0x7fffffULL) == 0)
                igObject_Destroy(old);
        }
        *arg3 = t;
    } else {
    h.ref = FUN_002b9500(igObject_GetAllocator(arg0));
    FUN_0030b3c0(h.ref, arg4);
    t = h.ref;
    if (t) {
        ++t->references;
    }
    old = *arg3;
    if (old) {
        --old->references;
        if (((unsigned long long)(long long)old->references & 0x7fffffULL) == 0)
            igObject_Destroy(old);
    }
    *arg3 = t;
    if (arg5 != 0) {
        FUN_00307700(arg0, arg1, arg2, arg4);
    }
    h.release();
    }
    return node != 0;
}
