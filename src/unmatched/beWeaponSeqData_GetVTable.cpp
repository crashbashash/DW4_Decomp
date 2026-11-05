extern "C" {
struct T { int word0; int references; };
void igObject_Destroy(T *);
int StringChunk_ReleaseHeader(int, int *);
extern int DAT_00524950[4];
extern int DAT_00539c80[4];
extern void * DAT_00586dc8[4];
}
struct Obj {
    int *vt; int w0; int *r1; int *r2;
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
        int **self = &r2;
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
};
extern "C" int igObject_InitHeader(Obj *);
extern "C" int beWeaponSeqData_GetVTable(void) {
    Obj obj;
    int r;

    igObject_InitHeader(&obj);
    obj.r1 = 0;
    obj.vt = &DAT_00539c80[0];
    obj.r2 = 0;
    r = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = &DAT_00539c80[0];
    obj.rel2();
    obj.vt = &DAT_00524950[0];
    obj.rel1();
    return r;
}
