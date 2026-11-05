extern "C" {
struct T { int word0; int references; };
void igObject_Destroy(T *);
extern int DAT_00536440[4];
extern int DAT_00539e90[4];
extern void * DAT_00586dc8[4];
}
struct Obj {
    int *vt; int w0[9]; T *ref; char pad[4];
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
extern "C" int beHitLandModelInfoRam_GetVTable(void) {
    Obj obj;
    int r;

    igObject_InitHeader(&obj);
    obj.ref = 0;
    obj.vt = &DAT_00539e90[0];
    obj.vt = &DAT_00536440[0];
    r = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = &DAT_00539e90[0];
    obj.releaseRef();
    return r;
}

