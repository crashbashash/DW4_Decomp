extern "C" {
struct T { int word0; int references; };
void igObject_Destroy(T *);
extern int DAT_0052de80[4];
extern void * DAT_00586dc8[4];
}
struct Obj {
    int *vt; int w0[36]; T *ref; int w1[2]; 
    inline void release() {
        T **self = &ref;
        if (self) {
            T *object = *self;
            if (object) {
                --object->references;
                if (((unsigned long long)(long long)object->references & 0x7fffffULL) == 0)
                    igObject_Destroy(object);
            }
        }
    }
};
extern "C" int igMemoryPool_Initialize(Obj *);
extern "C" int igStackMemoryPool_GetVTable(void) {
    Obj obj;
    int r;

    igMemoryPool_Initialize(&obj);
    obj.vt = &DAT_0052de80[0];
    obj.ref = 0;
    r = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = &DAT_0052de80[0];
    obj.release();
    return r;
}
