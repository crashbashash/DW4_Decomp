extern "C" {
struct T { int word0; int references; };
void igObject_Destroy(T *);
int StringChunk_ReleaseHeader(...);
extern int DAT_00524950[4];
extern int DAT_00537290[4];
extern void * DAT_00586dc8[4];
}
struct Obj {
    int *vt; char p4[4]; char *m8; char *m12; 
    inline void rel8() {
        char **self = &m8;
        if (self) {
            char *o = *self;
            if (o) {
                int *a1 = (int *)(o - 8);
                int v0 = *(int *)(o - 4) - 1;
                *(int *)(o - 4) = v0;
                if (v0 == 0) {
                    StringChunk_ReleaseHeader(*a1, a1);
                }
            }
        }
    }
    inline void rel12() {
        char **self = &m12;
        if (self) {
            char *o = *self;
            if (o) {
                int *a1 = (int *)(o - 8);
                int v0 = *(int *)(o - 4) - 1;
                *(int *)(o - 4) = v0;
                if (v0 == 0) {
                    StringChunk_ReleaseHeader(*a1, a1);
                }
            }
        }
    }
};
extern "C" int igObject_InitHeader(Obj *);
extern "C" int beModelCtrlLUACALL_GetVTable(void) {
    Obj obj;
    int r;

    igObject_InitHeader(&obj);
    obj.m8 = 0;
    obj.vt = &DAT_00537290[0];
    obj.m12 = 0;
    r = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = &DAT_00537290[0];
    obj.rel12();
    obj.vt = &DAT_00524950[0];
    obj.rel8();
    return r;
}
