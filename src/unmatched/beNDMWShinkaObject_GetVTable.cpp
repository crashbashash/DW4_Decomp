/* C++ translation unit: the unit compiled with exceptions on and retail keeps this function's
 * exception index record, which only the C++ front end emits. */
struct Obj { int *vt; char pad[8]; char *m; char pad2[80]; };
extern "C" {
int igObject_InitHeader(struct Obj *);
int StringChunk_ReleaseHeader(int, int *);
extern int DAT_0053c5b0[4];
extern int DAT_0053c5b0[4];
extern void * DAT_00586dc8[4];
int beNDMWShinkaObject_GetVTable(void);
}
int beNDMWShinkaObject_GetVTable(void) {
    struct Obj obj;
    char *o;
    int *a1;
    int v0;
    int t;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_0053c5b0[0];
    obj.m = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = &DAT_0053c5b0[0];
    if (&obj.m != 0) {
        o = obj.m;
        if (o != 0) {
            a1 = (int *)(o - 8);
            v0 = *(int *)(o - 4) - 1;
            *(int *)(o - 4) = v0;
            if (v0 == 0) {
                StringChunk_ReleaseHeader(*a1, a1);
            }
        }
    }
    return t;
}
