extern "C" {
struct T { int word0; int references; };
void igObject_Destroy(T *);
int StringChunk_ReleaseHeader(int, int *);
extern int DAT_00536be0[4];
extern int DAT_00539e90[4];
extern void * DAT_00586dc8[4];
}
struct Obj {
    int *vt; int w0; int w1; int w2; int w3; int w4; int w5; int w6; int w7; int w8; T *r9; T *r10;
    inline void rel9() {
        T **self = &r9;
        if (self) {
            T *object = *self;
            if (object) {
                --object->references;
                if (((unsigned long long)(long long)object->references & 0x7fffffULL) == 0)
                    igObject_Destroy(object);
            }
        }
    }
    inline void rel10() {
        T **self = &r10;
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
extern "C" int beMatCtrlInfoRam_GetVTable(void) {
    Obj obj;
    int r;

    igObject_InitHeader(&obj);
    obj.r9 = 0;
    obj.vt = &DAT_00536be0[0];
    obj.r10 = 0;
    r = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = &DAT_00536be0[0];
    obj.rel10();
    obj.vt = &DAT_00539e90[0];
    obj.rel9();
    return r;
}
