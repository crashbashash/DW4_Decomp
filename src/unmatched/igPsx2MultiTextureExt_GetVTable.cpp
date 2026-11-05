extern "C" {
struct T { int word0; int references; };
void igObject_Destroy(T *);
extern int DAT_00525510[4];
extern int DAT_00530a10[4];
extern void * DAT_00586dc8[4];
}
struct Obj {
    int *vt; int w0; T *r1; int w1; T *r2; int t[8];
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
extern "C" int igPsx2MultiTextureExt_GetVTable(void) {
    Obj obj;
    int r;

    igObject_InitHeader(&obj);
    obj.r1 = 0;
    obj.vt = &DAT_00530a10[0];
    obj.r2 = 0;
    obj.vt = &DAT_00525510[0];
    r = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = &DAT_00530a10[0];
    obj.rel(&obj.r2);
    obj.rel(&obj.r1);
    return r;
}
