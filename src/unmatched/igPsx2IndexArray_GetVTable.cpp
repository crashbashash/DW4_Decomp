extern "C" {
struct T { int word0; int references; };
void igObject_Destroy(T *);
extern int DAT_00526ad0[4];
extern int DAT_00526760[4];
extern void * DAT_00586dc8[4];
}
struct Obj {
    int *vt; int w0[1]; T *ref; char pad[16];
    inline void releaseRef() {
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
extern "C" int igObject_InitHeader(Obj *);
extern "C" int igPsx2IndexArray_GetVTable(void) {
    Obj obj;
    int r;

    igObject_InitHeader(&obj);
    obj.ref = 0;
    obj.vt = &DAT_00526760[0];
    obj.vt = &DAT_00526ad0[0];
    r = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = &DAT_00526760[0];
    obj.releaseRef();
    return r;
}
