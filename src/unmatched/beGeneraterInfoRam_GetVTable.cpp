extern "C" {
struct T { int word0; int references; };
void igObject_Destroy(T *);
int StringChunk_ReleaseHeader(...);
extern int DAT_00535ff0[4];
extern int DAT_00539e90[4];
extern void * DAT_00586dc8[4];
}
struct Obj {
    int *vt; char p4[36]; T *m40; T *m44; 
    inline void rel40() {
        T **self = &m40;
        if (self) {
            T *object = *self;
            if (object) {
                --object->references;
                if (((unsigned long long)(long long)object->references & 0x7fffffULL) == 0)
                    igObject_Destroy(object);
            }
        }
    }
    inline void rel44() {
        T **self = &m44;
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
extern "C" int beGeneraterInfoRam_GetVTable(void) {
    Obj obj;
    int r;

    igObject_InitHeader(&obj);
    obj.m40 = 0;
    obj.vt = &DAT_00535ff0[0];
    obj.m44 = 0;
    r = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = &DAT_00535ff0[0];
    obj.rel44();
    obj.vt = &DAT_00539e90[0];
    obj.rel40();
    return r;
}
