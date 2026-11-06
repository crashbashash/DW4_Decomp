/* stack-object GetVTable accessor with a string member released through a helper.py. */
typedef struct { int *vt; int w[7]; int s; } Obj;
int igObject_InitHeader(void *);
int FUN_0013bfe0(void *, int);
int FUN_00195a90(void *, int);
extern int DAT_005294b0[4];
extern void * DAT_00586dc8[4];
int igAttrSet_GetVTable(void) {
    Obj o;
    int r;

    igObject_InitHeader(&o);
    o.w[1] = 0;
    o.w[2] = 0;
    o.w[3] = 0;
    o.w[6] = 0;
    o.vt = &DAT_005294b0[0];
    o.s = 0;
    r = *(int *)((char *)&o + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    o.vt = &DAT_005294b0[0];
    FUN_0013bfe0(&o.s, -1);
    FUN_00195a90(&o, 0);
    return r;
}
