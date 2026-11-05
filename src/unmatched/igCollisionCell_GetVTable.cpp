extern "C" {
struct T { int word0; int references; };
void igObject_Destroy(T *);
extern int DAT_0052d290[4];
extern void * DAT_00586dc8[4];
}
struct Obj {
    int *vt; int w0; T *r1; int w2; T *r3; int w4; int w5; int w6;
    inline void rel1() {
        T **self = &r1;
        if (self) {
            T *object = *self;
            if (object) {
                --object->references;
                if (((unsigned long long)(long long)object->references & 0x7fffffULL) == 0)
                    igObject_Destroy(object);
            }
        }
    }
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
};
extern "C" int igObject_InitHeader(Obj *);
extern "C" int igCollisionCell_GetVTable(void) {
    Obj obj;
    int r;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_0052d290[0];
    obj.r1 = 0;
    obj.r3 = 0;
    r = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = &DAT_0052d290[0];
    obj.rel3();
    obj.rel1();
    return r;
}
