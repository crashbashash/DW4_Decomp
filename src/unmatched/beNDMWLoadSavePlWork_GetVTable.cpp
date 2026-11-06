struct O { int *vt; char post[60]; };
extern "C" {
int igObject_InitHeader(void *);
extern int DAT_0053ccd0[4];
extern char *DAT_00586dc8[4];
int beNDMWLoadSavePlWork_GetVTable(void);
}
int beNDMWLoadSavePlWork_GetVTable(void) {
    struct O o;

    igObject_InitHeader(&o.vt);
    o.vt = DAT_0053ccd0;
    return *(int *)((char *)&o.vt + *(int *)(DAT_00586dc8[0] + 916));
}
