extern "C" {
struct T { int word0; int references; };
void igObject_Destroy(T *);
extern int DAT_0053bc80[4];
extern int DAT_0053c070[4];
extern void * DAT_00586dc8[4];
}
struct Obj {
    int *vt; int w0[11]; T *r1; T *r2; T *r3; int pad;
    inline void rel(T **self) {
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
extern "C" int beSvEndApi_GetVTable(void) {
    Obj obj;
    int r;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_0053c070[0];
    obj.r1 = 0;
    obj.r2 = 0;
    obj.r3 = 0;
    obj.vt = &DAT_0053bc80[0];
    r = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = &DAT_0053c070[0];
    obj.rel(&obj.r3);
    obj.rel(&obj.r2);
    obj.rel(&obj.r1);
    return r;
}
