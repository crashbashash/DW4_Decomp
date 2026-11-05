extern "C" {
struct T { int word0; int references; };
void igObject_Destroy(T *);
int StringChunk_ReleaseHeader(int, int *);
extern int DAT_00524950[4];
extern int DAT_0053aa60[4];
extern int DAT_0052d660[4];
extern void * DAT_00586dc8[4];
}
struct Obj {
    int *vt; int w0; int *r1; int w1; T *r2;
    inline void rel1() {
        int **self = &r1;
        if (self) {
            int *p = *self;
            if (p) {
                int *a1 = p - 2;
                int v0 = p[-1] - 1;
                p[-1] = v0;
                if (v0 == 0)
                    StringChunk_ReleaseHeader(*a1, a1);
            }
        }
    }
    inline void rel2() {
        T **self = &r2;
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
extern "C" int beLuaState_GetVTable(void) {
    Obj obj;
    int r;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_0052d660[0];
    obj.r1 = 0;
    obj.r2 = 0;
    obj.vt = &DAT_0053aa60[0];
    r = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = &DAT_0052d660[0];
    obj.rel2();
    obj.vt = &DAT_00524950[0];
    obj.rel1();
    return r;
}
