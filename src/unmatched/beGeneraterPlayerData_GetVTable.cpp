extern "C" {
struct T { int word0; int references; };
void igObject_Destroy(T *);
int StringChunk_ReleaseHeader(int, int *);
extern int DAT_00535de0[4];
extern void * DAT_00586dc8[4];
}
struct Obj {
    int *vt; int w0; int w1; int w2; T *r3; T *r4; int w5; int w6;
    inline void rel3() {
        T **self = &r3;
        if (self) {
            T *object = *self;
            if (object) {
                --object->references;
                if (((unsigned long long)(long long)object->references & 0x7fffffULL) == 0)
                    igObject_Destroy(object);
            }
        }
    }
    inline void rel4() {
        T **self = &r4;
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
extern "C" int beGeneraterPlayerData_GetVTable(void) {
    Obj obj;
    int r;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_00535de0[0];
    obj.r3 = 0;
    obj.r4 = 0;
    r = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = &DAT_00535de0[0];
    obj.rel4();
    obj.rel3();
    return r;
}
