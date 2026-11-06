extern "C" {
struct T { int word0; int references; };
void igObject_Destroy(T *);
T *Memory_GetDefaultAllocator(...);
}
struct Rel { static inline void go(T *object) {
    if (object) {
        --object->references;
        if (((unsigned long long)(long long)object->references & 0x7fffffULL) == 0)
            igObject_Destroy(object);
    }
} };
struct Obj { char p[280]; T *m280; T *m284; T *m288; };
extern "C" void Gap__Core__igIGBFile__vfunc_13(Obj *arg0);
void Gap__Core__igIGBFile__vfunc_13(Obj *arg0) {
    T *s0;
    s0 = Memory_GetDefaultAllocator();
    if (s0) s0->references++;
    Rel::go(arg0->m280);
    arg0->m280 = s0;
    s0 = Memory_GetDefaultAllocator();
    if (s0) s0->references++;
    Rel::go(arg0->m284);
    arg0->m284 = s0;
    s0 = Memory_GetDefaultAllocator();
    if (s0) s0->references++;
    Rel::go(arg0->m288);
    arg0->m288 = s0;
}
