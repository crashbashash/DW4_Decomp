struct Obj { int *vt; char pad[8]; char *m; };
extern "C" {
int igObject_InitHeader(struct Obj *);
int igObject_Destroy(char *);
extern int DAT_00538400[4];
extern int DAT_00538400[4];
extern void * DAT_00586dc8[4];
int beNumVerData_GetVTable(void);
}
int beNumVerData_GetVTable(void) {
    struct Obj obj;
    char *o;
    int t;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_00538400[0];
    obj.m = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = &DAT_00538400[0];
    if (&obj.m != 0) {
        o = obj.m;
        if (o != 0) {
            *(int *)(o + 4) = *(int *)(o + 4) - 1;
            if ((*(int *)(o + 4) & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
        }
    }
    return t;
}
